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

#define C_LUCY_NATIVELOCK
#include "Lucy/Util/ToolSet.h"

#include "Lucy/Store/NativeLock.h"
#include "Lucy/Store/FileHandle.h"
#include "Lucy/Store/Folder.h"

static bool
S_open_fh(NativeLock *self, uint32_t flags);

// __attribute__((noinline))
static FileHandle*
S_handle_error(NativeLockIVARS *ivars, uint32_t flags);

NativeLock*
NativeLock_new(Folder *folder, String *name, int32_t timeout,
               int32_t interval) {
    NativeLock *self = (NativeLock*)Class_Make_Obj(NATIVELOCK);
    return NativeLock_init(self, folder, name, timeout, interval);
}

NativeLock*
NativeLock_init(NativeLock *self, Folder *folder, String *name,
                int32_t timeout, int32_t interval) {
    NativeLockIVARS *const ivars = NativeLock_IVARS(self);
    ivars->lock_path = Str_newf("locks/%o.nlock", name);
    return (NativeLock*)Lock_init((Lock*)self, folder, name, timeout,
                                  interval);
}
bool
NativeLock_Request_Shared_IMP(NativeLock *self) {
    return S_open_fh(self, FH_CREATE | FH_READ_ONLY | FH_LOCK_SHARED);
}

bool
NativeLock_Request_Exclusive_IMP(NativeLock *self) {
    return S_open_fh(self, FH_CREATE | FH_READ_ONLY | FH_LOCK_EXCLUSIVE);
}

void
NativeLock_Release_IMP(NativeLock *self) {
    NativeLockIVARS *const ivars = NativeLock_IVARS(self);

    if (!ivars->fh) {
        THROW(ERR, "Lock not acquired");
    }

    DECREF(ivars->fh);
    ivars->fh = NULL;
}

void
NativeLock_Destroy_IMP(NativeLock *self) {
    NativeLockIVARS *const ivars = NativeLock_IVARS(self);
    DECREF(ivars->lock_path);
    DECREF(ivars->fh);
    SUPER_DESTROY(self, NATIVELOCK);
}

static bool
S_open_fh(NativeLock *self, uint32_t flags) {
    NativeLockIVARS *const ivars = NativeLock_IVARS(self);

    if (ivars->fh) {
        THROW(ERR, "Lock already acquired");
    }

    // TODO: Store "locks" folder in ivar and call Local_Open_FileHandle.
    FileHandle *fh = Folder_Open_FileHandle(ivars->folder, ivars->lock_path,
                                            flags);
    if (!fh) {
        fh = S_handle_error(ivars, flags);
        if (!fh) { return false; }
    }

    ivars->fh = fh;
    return true;
}

static FileHandle*
S_handle_error(NativeLockIVARS *ivars, uint32_t flags) {
    // Don't retry in case of LockErr.
    if (Err_is_a(Err_get_error(), LOCKERR)) { return false; }

    // Might have failed because the lock subdirectory doesn't exist yet.
    // Create the "locks" subdirectory if necessary and retry.
    if (!Folder_Exists(ivars->folder, SSTR_WRAP_C("locks"))) {
        if (!Lock_make_lock_dir(ivars->folder)) {
            return false;
        }
    }

    return Folder_Open_FileHandle(ivars->folder, ivars->lock_path, flags);
}

