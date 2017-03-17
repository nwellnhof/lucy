/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define TESTLUCY_USE_SHORT_NAMES
#include "Lucy/Util/ToolSet.h"

#include "charmony.h"

// rmdir
#ifdef CHY_HAS_DIRECT_H
  #include <direct.h>
#endif
#ifdef CHY_HAS_UNISTD_H
  #include <unistd.h>
#endif

#include "Lucy/Test/Index/TestIndexer.h"
#include "Clownfish/TestHarness/TestBatchRunner.h"
#include "Lucy/Document/Doc.h"
#include "Lucy/Index/Indexer.h"
#include "Lucy/Index/IndexManager.h"
#include "Lucy/Index/PolyReader.h"
#include "Lucy/Index/Snapshot.h"
#include "Lucy/Store/Lock.h"
#include "Lucy/Store/FSFolder.h"
#include "Lucy/Test.h"
#include "Lucy/Test/TestSchema.h"
#include "Lucy/Test/Index/NoMergeManager.h"
#include "Lucy/Util/IndexFileNames.h"
#include "Lucy/Util/Json.h"
#include "Lucy/Util/ProcessID.h"

TestIndexer*
TestIndexer_new() {
    return (TestIndexer*)Class_Make_Obj(TESTINDEXER);
}

static void
S_add_doc(Indexer *indexer, const char *content) {
    Doc    *doc   = Doc_new(NULL, 0);
    String *field = SSTR_WRAP_C("content");
    String *value = SSTR_WRAP_C(content);
    Doc_Store(doc, field, (Obj*)value);
    Indexer_Add_Doc(indexer, doc, 1.0f);
    DECREF(doc);
}

static void
S_delete_doc(Indexer *indexer, const char *content) {
    String *field = SSTR_WRAP_C("content");
    String *term  = SSTR_WRAP_C(content);
    Indexer_Delete_By_Term(indexer, field, (Obj*)term);
}

static int
S_count_entries(Folder *folder, const char *suffix) {
    Vector *entries = Folder_List_R(folder, NULL);
    size_t suffix_len = strlen(suffix);
    int count = 0;

    for (size_t i = 0, max = Vec_Get_Size(entries); i < max; i++) {
        String *entry = (String*)Vec_Fetch(entries, i);
        if (Str_Ends_With_Utf8(entry, suffix, suffix_len)) { count++; }
    }

    DECREF(entries);
    return count;
}

typedef struct {
    Folder *folder;
    Snapshot *snapshot;
    IndexManager *manager;
} poly_reader_open_context;

static void
S_try_poly_reader_open(void *vctx) {
    poly_reader_open_context *ctx = (poly_reader_open_context*)vctx;
    PolyReader_open((Obj*)ctx->folder, ctx->snapshot, ctx->manager);
}

static void
test_read_locking(TestBatchRunner *runner, IndexManager *manager,
                  IndexManager *no_merge_manager,
                  IndexManager *other_manager) {
    Folder *root       = (Folder*)FSFolder_new(SSTR_WRAP_C("_test"));
    Schema *schema     = (Schema*)TestSchema_new(false);
    String *index_path = SSTR_WRAP_C("index");

    Folder_Initialize(root);
    Folder_MkDir(root, index_path);
    Folder *folder = Folder_Find_Folder(root, index_path);

    {
        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        S_add_doc(indexer, "a");
        S_add_doc(indexer, "b");
        S_add_doc(indexer, "c");
        Indexer_Commit(indexer);
        DECREF(indexer);
    }

    {
        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        S_delete_doc(indexer, "a");
        S_delete_doc(indexer, "b");
        S_delete_doc(indexer, "c");
        S_add_doc(indexer, "x");

        // Request snapshot lock before commit.
        String *snapshot_path = SSTR_WRAP_C("snapshot_1.json");
        Lock   *snapshot_lock = IxManager_Make_Snapshot_Lock(manager,
                                                             snapshot_path);
        TEST_TRUE(runner, Lock_Request_Exclusive(snapshot_lock),
                  "Request snapshot lock");

        Indexer_Commit(indexer);
        DECREF(indexer);

        TEST_INT_EQ(runner, S_count_entries(folder, "documents.dat"), 2,
                    "Indexer doesn't process deletions when it can't get"
                    " snapshot lock");
        TEST_TRUE(runner,
                  Folder_Exists(folder, SSTR_WRAP_C("snapshot_1.json")),
                  "didn't zap the old snap file");

        Snapshot *snapshot = Snapshot_new();
        Snapshot_Read_File(snapshot, folder, snapshot_path);

        poly_reader_open_context ctx = { folder, snapshot, other_manager };
        Err *error = Err_trap(S_try_poly_reader_open, &ctx);
        TEST_TRUE(runner, error && Err_is_a(error, LOCKERR),
                  "PolyReader_open fails if it can't get snapshot lock");

        DECREF(error);
        DECREF(snapshot);
        DECREF(snapshot_lock);
    }

    {
        // Close the CompoundFileReader for seg_1, so seg_1/cf.dat will be
        // closed. Otherwise, renaming seg_1 will fail on Windows.
        Folder_Close(Folder_Find_Folder(folder, SSTR_WRAP_C("seg_1")));

        int32_t num_prev_passes = PolyReader_debug1_num_passes;
        String *latest_snapshot_file = IxFileNames_latest_snapshot(folder);
        Folder_Rename(folder, latest_snapshot_file, SSTR_WRAP_C("temp"));
        Folder_Rename(folder, SSTR_WRAP_C("seg_1"),
                      SSTR_WRAP_C("seg_1.hidden"));
        PolyReader_race_condition_debug1 = latest_snapshot_file;

        PolyReader *poly_reader = PolyReader_open((Obj*)folder, NULL,
                                                  other_manager);
        TEST_INT_EQ(runner, PolyReader_Doc_Count(poly_reader), 1,
                    "reader overcomes race condition of index update after"
                    " read lock");
        TEST_INT_EQ(runner, PolyReader_debug1_num_passes, num_prev_passes + 2,
                    "reader retried before succeeding");

        // Clean up our artificial mess.
        Folder_Rename(folder, SSTR_WRAP_C("seg_1.hidden"),
                      SSTR_WRAP_C("seg_1"));
        PolyReader_race_condition_debug1 = NULL;

        DECREF(poly_reader);
        DECREF(latest_snapshot_file);
    }

    Folder_Delete_Tree(root, index_path);
    Folder_MkDir(root, index_path);

    {
        // Start over with one segment.
        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        S_add_doc(indexer, "a");
        S_add_doc(indexer, "b");
        S_add_doc(indexer, "c");
        S_add_doc(indexer, "x");
        Indexer_Commit(indexer);
        DECREF(indexer);
    }

    {
        // Add a second segment and delete one doc from existing segment.
        Indexer *indexer
            = Indexer_new(schema, (Obj*)folder, no_merge_manager, 0);
        S_add_doc(indexer, "foo");
        S_add_doc(indexer, "bar");
        S_delete_doc(indexer, "x");
        Indexer_Commit(indexer);
        DECREF(indexer);
    }

    {
        // Delete a doc from the second seg and increase del gen on first seg.
        Indexer *indexer
            = Indexer_new(schema, (Obj*)folder, no_merge_manager, 0);
        S_delete_doc(indexer, "a");
        S_delete_doc(indexer, "foo");
        Indexer_Commit(indexer);
        DECREF(indexer);
    }

    {
        // Establish read lock.
        PolyReader *poly_reader
            = PolyReader_open((Obj*)folder, NULL, other_manager);

        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        S_delete_doc(indexer, "a");
        Indexer_Optimize(indexer);
        Indexer_Commit(indexer);
        DECREF(indexer);

        DECREF(poly_reader);
    }

    TEST_TRUE(runner,
              Folder_Exists(folder, SSTR_WRAP_C("snapshot_3.json")),
              "lock preserved last snapshot file");
    TEST_INT_EQ(runner, S_count_entries(folder, "deletions-seg_1.bv"), 2,
                "outdated but locked del files survive");
    TEST_TRUE(runner,
              Folder_Exists(folder, SSTR_WRAP_C("seg_3/deletions-seg_1.bv")),
              "first correct old del file");
    TEST_TRUE(runner,
              Folder_Exists(folder, SSTR_WRAP_C("seg_3/deletions-seg_2.bv")),
              "second correct old del file");
    TEST_TRUE(runner, S_count_entries(folder, "documents.dat") > 1,
              "segment data files preserved");

    {
        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        Indexer_Optimize(indexer);
        Indexer_Commit(indexer);
        DECREF(indexer);
    }

    Vector *entries = Folder_List_R(folder, NULL);
    int num_deletions = 0;
    int num_snapshots = 0;
    int num_documents = 0;

    for (size_t i = 0, max = Vec_Get_Size(entries); i < max; i++) {
        String *entry = (String*)Vec_Fetch(entries, i);
        if (Str_Contains_Utf8(entry, "deletions", 9)) {
            num_deletions += 1;
        }
        if (Str_Contains_Utf8(entry, "snapshot_", 9)
            && Str_Ends_With_Utf8(entry, ".json", 5)
           ) {
            num_snapshots += 1;
        }
        if (Str_Ends_With_Utf8(entry, "documents.dat", 13)) {
            num_documents += 1;
        }
    }

    DECREF(entries);

    TEST_INT_EQ(runner, num_deletions, 0,
                "lock freed, del files optimized away");
    TEST_INT_EQ(runner, num_snapshots, 1,
                "lock freed, now only one snapshot file");
    TEST_INT_EQ(runner, num_documents, 1,
                "lock freed, now only one ds file");

    Folder_Delete_Tree(root, index_path);

    rmdir("_test");

    DECREF(schema);
    DECREF(root);
}

typedef struct {
    Schema *schema;
    Folder *folder;
    IndexManager *manager;
} indexer_new_context;

static void
S_try_indexer_new(void *vctx) {
    indexer_new_context *ctx = (indexer_new_context*)vctx;
    Indexer_new(ctx->schema, (Obj*)ctx->folder, ctx->manager, 0);
}

static void
test_write_locking(TestBatchRunner *runner, IndexManager *manager,
                   IndexManager *other_manager) {
    Folder *root       = (Folder*)FSFolder_new(SSTR_WRAP_C("_test"));
    Schema *schema     = (Schema*)TestSchema_new(false);
    String *index_path = SSTR_WRAP_C("index");

    Folder_Initialize(root);
    Folder_MkDir(root, index_path);
    Folder *folder = Folder_Find_Folder(root, index_path);

    {
        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        S_add_doc(indexer, "foo");
        // Don't commit.
        DECREF(indexer);
    }

    IxManager_Set_Write_Lock_Timeout(other_manager, 0);

    {
        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        S_add_doc(indexer, "foo");

        indexer_new_context ctx;
        ctx.schema = schema;
        ctx.folder = folder;
        ctx.manager = other_manager;
        Err *error = Err_trap(S_try_indexer_new, &ctx);
        TEST_TRUE(runner, error != NULL,
                  "failed to get lock with competing host");
        TEST_TRUE(runner, Err_is_a(error, LOCKERR),
                  "Indexer throws a LockErr");
        DECREF(error);

        Indexer_Commit(indexer);
        DECREF(indexer);
    }

    if (Str_Equals_Utf8(IxManager_Get_Lock_Type(manager), "portable", 8)) {
        String *lock_file = SSTR_WRAP_C("locks/write.lock");

        // Fake a write lock.
        Hash    *hash = Hash_new(0);
        String  *host = IxManager_Get_Host(other_manager);
        int64_t  pid  = (int64_t)PID_getpid();
        Hash_Store_Utf8(hash, "host", 4, INCREF(host));
        Hash_Store_Utf8(hash, "pid",  3, (Obj*)Str_newf("%i64", pid));
        Hash_Store_Utf8(hash, "name", 4, (Obj*)Str_newf("write"));
        Json_spew_json((Obj*)hash, folder, lock_file);

        indexer_new_context ctx;
        ctx.schema = schema;
        ctx.folder = folder;
        ctx.manager = other_manager;
        Err *error = Err_trap(S_try_indexer_new, &ctx);
        TEST_TRUE(runner, error != NULL,
                  "failed to get lock with competing host");
        TEST_TRUE(runner, Err_is_a(error, LOCKERR),
                  "Indexer throws a LockErr");
        DECREF(error);

        Folder_Delete(folder, lock_file);
        Hash_Store_Utf8(hash, "pid", 3, (Obj*)Str_newf("12345678"));
        Json_spew_json((Obj*)hash, folder, lock_file);

        Indexer *indexer = Indexer_new(schema, (Obj*)folder, other_manager, 0);
        TEST_TRUE(runner, indexer != NULL,
                  "clobbered lock from same host with inactive pid");
        DECREF(indexer);

        DECREF(hash);
    }

    IxManager_Set_Write_Lock_Timeout(other_manager, 1000);

    Folder_Delete_Tree(root, index_path);
    rmdir("_test");

    DECREF(schema);
    DECREF(root);
}

static void
test_lock_type_mismatch(TestBatchRunner *runner, IndexManager *manager,
                        IndexManager *other_manager) {
    Folder *root       = (Folder*)FSFolder_new(SSTR_WRAP_C("_test"));
    Schema *schema     = (Schema*)TestSchema_new(false);
    String *index_path = SSTR_WRAP_C("index");

    Folder_Initialize(root);
    Folder_MkDir(root, index_path);
    Folder *folder = Folder_Find_Folder(root, index_path);

    {
        Indexer *indexer = Indexer_new(schema, (Obj*)folder, manager, 0);
        S_add_doc(indexer, "foo");
        Indexer_Commit(indexer);
        DECREF(indexer);
    }

    {
        indexer_new_context ctx;
        ctx.schema = schema;
        ctx.folder = folder;
        ctx.manager = other_manager;
        Err *error = Err_trap(S_try_indexer_new, &ctx);
        TEST_TRUE(runner, error != NULL,
                  "failed to get lock with wrong type");
        DECREF(error);
    }

    Folder_Delete_Tree(root, index_path);
    rmdir("_test");

    DECREF(schema);
    DECREF(root);
}

static void
test_locking(TestBatchRunner *runner) {
    IndexManager *manager          = IxManager_new(NULL);
    IndexManager *no_merge_manager = (IndexManager*)NoMergeManager_new();
    IndexManager *other_manager    = IxManager_new(NULL);

    String *host1 = SSTR_WRAP_C("host1");
    String *host2 = SSTR_WRAP_C("host2");
    IxManager_Use_Portable_Locks(manager, host1);
    IxManager_Use_Portable_Locks(no_merge_manager, host1);
    IxManager_Use_Portable_Locks(other_manager, host2);
    test_read_locking(runner, manager, no_merge_manager, other_manager);
    test_write_locking(runner, manager, other_manager);

    IxManager_Use_Native_Locks(manager);
    IxManager_Use_Native_Locks(no_merge_manager);
    IxManager_Use_Native_Locks(other_manager);
    test_read_locking(runner, manager, no_merge_manager, other_manager);
    test_write_locking(runner, manager, other_manager);

    IxManager_Use_Native_Locks(manager);
    IxManager_Use_Portable_Locks(other_manager, host2);
    test_lock_type_mismatch(runner, manager, other_manager);
    test_lock_type_mismatch(runner, other_manager, manager);

    DECREF(other_manager);
    DECREF(no_merge_manager);
    DECREF(manager);
}

void
TestIndexer_Run_IMP(TestIndexer *self, TestBatchRunner *runner) {
    TestBatchRunner_Plan(runner, (TestBatch*)self, 37);
    test_locking(runner);
}

