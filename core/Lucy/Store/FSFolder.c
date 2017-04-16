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

#define C_LUCY_FSFOLDER
#include "Lucy/Util/ToolSet.h"

#include "charmony.h"

#include "Clownfish/CharBuf.h"
#include "Lucy/Store/ErrorMessage.h"
#include "Lucy/Store/FSFolder.h"
#include "Lucy/Store/CompoundFileReader.h"
#include "Lucy/Store/CompoundFileWriter.h"
#include "Lucy/Store/FSDirHandle.h"
#include "Lucy/Store/FSFileHandle.h"
#include "Lucy/Store/InStream.h"
#include "Lucy/Store/OutStream.h"
#include "Lucy/Util/IndexFileNames.h"

// Return a String containing a platform-specific absolute filepath.
static String*
S_fullpath(FSFolder *self, String *path);

// Return a String containing a platform-specific absolute filepath.
static char*
S_fullpath_ptr(FSFolder *self, String *path);

// Return true if the supplied path is a directory.
static bool
S_dir_ok(String *path);

// Create a directory, or set the global error object and return false.
static bool
S_create_dir(String *path);

// Return true if the supplied path exists.
static bool
S_exists(const char *path);

// Return true unless the supplied path contains a slash.
static bool
S_is_local_entry(String *path);

// Return true if the supplied path is absolute.
static bool
S_is_absolute(String *path);

// Transform a possibly relative path into an absolute path.
static String*
S_absolutify(String *path);

// Rename a directory or file.
static bool
S_rename(const char *from_path, const char *to_path);

// Create a hard link.
static bool
S_hard_link(const char *from_path, const char *to_path);

// Delete a directory or file.
static bool
S_delete(const char *path);

FSFolder*
FSFolder_new(String *path) {
    FSFolder *self = (FSFolder*)Class_Make_Obj(FSFOLDER);
    return FSFolder_init(self, path);
}

FSFolder*
FSFolder_init(FSFolder *self, String *path) {
    String *abs_path = S_absolutify(path);
    Folder_init((Folder*)self, abs_path);
    DECREF(abs_path);
    return self;
}

void
FSFolder_Initialize_IMP(FSFolder *self) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    if (!S_dir_ok(ivars->path)) {
        if (!S_create_dir(ivars->path)) {
            RETHROW(INCREF(Err_get_error()));
        }
    }
}

bool
FSFolder_Check_IMP(FSFolder *self) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    return S_dir_ok(ivars->path);
}

bool
FSFolder_Supports_Locks_IMP(FSFolder *self) {
    UNUSED_VAR(self);
    return FSFH_supports_locks;
}

FileHandle*
FSFolder_Local_Open_FileHandle_IMP(FSFolder *self, String *name,
                                   uint32_t flags) {
    String       *fullpath = S_fullpath(self, name);
    FSFileHandle *fh = FSFH_open(fullpath, flags);
    if (!fh) { ERR_ADD_FRAME(Err_get_error()); }
    DECREF(fullpath);
    return (FileHandle*)fh;
}

bool
FSFolder_Local_MkDir_IMP(FSFolder *self, String *name) {
    String *dir = S_fullpath(self, name);
    bool result = S_create_dir(dir);
    if (!result) { ERR_ADD_FRAME(Err_get_error()); }
    DECREF(dir);
    return result;
}

DirHandle*
FSFolder_Local_Open_Dir_IMP(FSFolder *self) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    DirHandle *dh = (DirHandle*)FSDH_open(ivars->path);
    if (!dh) { ERR_ADD_FRAME(Err_get_error()); }
    return dh;
}

bool
FSFolder_Local_Exists_IMP(FSFolder *self, String *name) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    if (Hash_Fetch(ivars->entries, name)) {
        return true;
    }
    else if (!S_is_local_entry(name)) {
        return false;
    }
    else {
        char *fullpath_ptr = S_fullpath_ptr(self, name);
        bool retval = S_exists(fullpath_ptr);
        FREEMEM(fullpath_ptr);
        return retval;
    }
}

bool
FSFolder_Local_Is_Directory_IMP(FSFolder *self, String *name) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);

    // Check for a cached object, then fall back to a system call.
    Obj *elem = Hash_Fetch(ivars->entries, name);
    if (elem && Obj_is_a(elem, FOLDER)) {
        return true;
    }
    else {
        String *fullpath = S_fullpath(self, name);
        bool result = S_dir_ok(fullpath);
        DECREF(fullpath);
        return result;
    }
}

bool
FSFolder_Rename_IMP(FSFolder *self, String* from, String *to) {
    // TODO: Update Folder entries.
    char *from_path = S_fullpath_ptr(self, from);
    char *to_path   = S_fullpath_ptr(self, to);
    bool retval = S_rename(from_path, to_path);
    FREEMEM(from_path);
    FREEMEM(to_path);
    return retval;
}

bool
FSFolder_Hard_Link_IMP(FSFolder *self, String *from,
                       String *to) {
    // TODO: Update Folder entries.
    char *from_path = S_fullpath_ptr(self, from);
    char *to_path   = S_fullpath_ptr(self, to);
    bool  retval    = S_hard_link(from_path, to_path);
    FREEMEM(from_path);
    FREEMEM(to_path);
    return retval;
}

bool
FSFolder_Local_Delete_IMP(FSFolder *self, String *name) {
    // TODO: Delete should only delete files. We should add RmDir for
    // directories.
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    char *path   = S_fullpath_ptr(self, name);
    bool  retval = S_delete(path);
    DECREF(Hash_Delete(ivars->entries, name));
    FREEMEM(path);
    return retval;
}

void
FSFolder_Close_IMP(FSFolder *self) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    Hash_Clear(ivars->entries);
}

Folder*
FSFolder_Local_Find_Folder_IMP(FSFolder *self, String *name) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);

    Folder *subfolder = NULL;
    if (!name || !Str_Get_Size(name)) {
        // No entity can be identified by NULL or empty string.
        return NULL;
    }
    else if (!S_is_local_entry(name)) {
        return NULL;
    }
    else if (Str_Starts_With_Utf8(name, ".", 1)) {
        // Don't allow access outside of the main dir.
        return NULL;
    }
    else if (NULL != (subfolder = (Folder*)Hash_Fetch(ivars->entries, name))) {
        if (Folder_is_a(subfolder, FOLDER)) {
            return subfolder;
        }
        else {
            return NULL;
        }
    }

    String *fullpath = S_fullpath(self, name);
    if (S_dir_ok(fullpath)) {
        subfolder = (Folder*)FSFolder_new(fullpath);
        if (!subfolder) {
            DECREF(fullpath);
            THROW(ERR, "Failed to open FSFolder at '%o'", fullpath);
        }
        // Try to open a CompoundFileReader. On failure, just use the
        // existing folder.
        String *cfmeta_file = SSTR_WRAP_C("cfmeta.json");
        if (Folder_Local_Exists(subfolder, cfmeta_file)) {
            CompoundFileReader *cf_reader = CFReader_open(subfolder);
            if (cf_reader) {
                DECREF(subfolder);
                subfolder = (Folder*)cf_reader;
            }
        }
        Hash_Store(ivars->entries, name, (Obj*)subfolder);
    }
    DECREF(fullpath);

    return subfolder;
}

static String*
S_fullpath(FSFolder *self, String *path) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    String *fullpath = Str_newf("%o%s%o", ivars->path, CHY_DIR_SEP, path);
    String *retval;
    if (CHY_DIR_SEP[0] != '/') {
        // Replace '/' with CHY_DIR_SEP.
        StringIterator *iter = Str_Top(fullpath);
        CharBuf *buf = CB_new(Str_Get_Size(fullpath));
        int32_t cp;

        while (STR_OOB != (cp = StrIter_Next(iter))) {
            if (cp == '/') { cp = CHY_DIR_SEP[0]; }
            CB_Cat_Char(buf, cp);
        }

        retval = CB_Yield_String(buf);
        DECREF(buf);
        DECREF(iter);
        DECREF(fullpath);
    }
    else {
        retval = fullpath;
    }
    return retval;
}

static char*
S_fullpath_ptr(FSFolder *self, String *path) {
    FSFolderIVARS *const ivars = FSFolder_IVARS(self);
    size_t folder_size = Str_Get_Size(ivars->path);
    size_t path_size   = Str_Get_Size(path);
    size_t full_size   = folder_size + 1 + path_size;
    const char *folder_ptr = Str_Get_Ptr8(ivars->path);
    const char *path_ptr   = Str_Get_Ptr8(path);

    char *buf = (char*)MALLOCATE(full_size + 1);
    memcpy(buf, folder_ptr, folder_size);
    buf[folder_size] = CHY_DIR_SEP[0];
    memcpy(buf + folder_size + 1, path_ptr, path_size);
    buf[full_size] = '\0';

    if (CHY_DIR_SEP[0] != '/') {
        for (size_t i = 0; i < full_size; ++i) {
            if (buf[i] == '/') { buf[i] = CHY_DIR_SEP[0]; }
        }
    }

    return buf;
}

static bool
S_is_local_entry(String *path) {
    return !Str_Contains_Utf8(path, "/", 1);
}

/***************************************************************************/

#if (defined(CHY_HAS_WINDOWS_H) && !defined(__CYGWIN__))

// Windows.h defines INCREF and DECREF, so we include it only at the end of
// this file and undef those symbols.
#undef INCREF
#undef DECREF

#include <windows.h>

static bool
S_dir_ok(String *path) {
    char *path_ptr = Str_To_Utf8(path);
    DWORD attrs = GetFileAttributesA(path_ptr);
    bool retval = attrs != INVALID_FILE_ATTRIBUTES
                  && (attrs & FILE_ATTRIBUTE_DIRECTORY);
    FREEMEM(path_ptr);
    return retval;
}

static bool
S_create_dir(String *path) {
    bool retval = true;
    char *path_ptr = Str_To_Utf8(path);
    if (CreateDirectoryA(path_ptr, NULL) == 0) {
        ErrMsg_set_with_win_error("Couldn't create directory '%o'", path);
        retval = false;
    }
    SetFileAttributes(path_ptr, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
    FREEMEM(path_ptr);
    return retval;
}

static bool
S_exists(const char *path) {
    return GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES;
}

static bool
S_is_absolute(String *path) {
    int32_t code_point = Str_Code_Point_At(path, 0);

    if ((code_point >= 'A' && code_point <= 'Z')
        || (code_point >= 'a' && code_point <= 'z')) {
        code_point = Str_Code_Point_At(path, 1);
        if (code_point != ':') { return false; }
        code_point = Str_Code_Point_At(path, 2);
    }

    return code_point == '\\' || code_point == '/';
}

static String*
S_absolutify(String *path) {
    if (S_is_absolute(path)) { return Str_Clone(path); }

    DWORD  cwd_len = GetCurrentDirectoryA(0, NULL);
    char  *cwd     = (char*)MALLOCATE(cwd_len);
    DWORD  res     = GetCurrentDirectoryA(cwd_len, cwd);
    if (res == 0 || res > cwd_len) {
        THROW(ERR, "GetCurrentDirectory failed");
    }
    String *abs_path = Str_newf("%s\\%o", cwd, path);
    FREEMEM(cwd);

    return abs_path;
}

static bool
S_rename(const char *from_path, const char *to_path) {
    // TODO: We should consider using MoveFileEx with
    // MOVEFILE_REPLACE_EXISTING to better match POSIX semantics. But unlike
    // POSIX, this allows to replace a file with a directory, breaking the
    // tests.
    if (MoveFileA(from_path, to_path) != 0) {
        return true;
    }
    else {
        ErrMsg_set_with_win_error("rename from '%s' to '%s' failed",
                                  from_path, to_path);
        return false;
    }
}

static bool
S_hard_link(const char *from_path, const char *to_path) {
    if (CreateHardLinkA(to_path, from_path, NULL) != 0) {
        return true;
    }
    else {
        ErrMsg_set_with_win_error("CreateHardLink for new file '%s' "
                                  "from '%s' failed",
                                  to_path, from_path);
        return false;
    }
}

static bool
S_delete(const char *path) {
    if (RemoveDirectoryA(path) != 0) {
        return true;
    }
    if (GetLastError() != ERROR_DIRECTORY) {
        ErrMsg_set_with_win_error("removing '%s' failed", path);
        return false;
    }

    // Open file with FILE_FLAG_DELETE_ON_CLOSE and close it immediately.
    // In contrast to DeleteFile, this allows files opened with
    // FILE_SHARE_DELETE to be eventually deleted.
    DWORD share_mode = FILE_SHARE_READ
                       | FILE_SHARE_WRITE
                       | FILE_SHARE_DELETE;
    DWORD flags      = FILE_FLAG_DELETE_ON_CLOSE;
    DWORD attrs      = FILE_ATTRIBUTE_NORMAL;
    HANDLE handle = CreateFileA(path, DELETE, share_mode, NULL, OPEN_EXISTING,
                                flags | attrs, NULL);
    if (handle == INVALID_HANDLE_VALUE) {
        ErrMsg_set_with_win_error("removing '%s' failed", path);
        return false;
    }

    CloseHandle(handle);
    return true;
}

#elif (defined(CHY_HAS_UNISTD_H))

#include <errno.h>
#include <stdio.h>     // For rename, remove
#include <sys/stat.h>  // For stat, mkdir
#include <unistd.h>    // For getcwd, link, rmdir

static bool
S_dir_ok(String *path) {
    bool retval = false;
    char *path_ptr = Str_To_Utf8(path);
    struct stat stat_buf;
    if (stat(path_ptr, &stat_buf) != -1) {
        if (stat_buf.st_mode & S_IFDIR) { retval = true; }
    }
    FREEMEM(path_ptr);
    return retval;
}

static bool
S_create_dir(String *path) {
    bool retval = true;
    char *path_ptr = Str_To_Utf8(path);
    if (mkdir(path_ptr, 0777) != 0) {
        ErrMsg_set_with_errno("Couldn't create directory '%o'", path);
        retval = false;
    }
    FREEMEM(path_ptr);
    return retval;
}

static bool
S_exists(const char *path) {
    struct stat stat_buf;
    return stat(path, &stat_buf) == 0;
}

static bool
S_is_absolute(String *path) {
    return Str_Starts_With_Utf8(path, CHY_DIR_SEP, 1);
}

static String*
S_absolutify(String *path) {
    if (S_is_absolute(path)) { return Str_Clone(path); }

    char *cwd = NULL;
    for (size_t buf_size = 256; buf_size <= 65536; buf_size *= 2) {
        cwd = (char*)MALLOCATE(buf_size);
        if (getcwd(cwd, buf_size)) { break; }
        FREEMEM(cwd);
        cwd = NULL;
        if (errno != ERANGE) { THROW(ERR, "getcwd failed"); }
    }
    if (!cwd) { THROW(ERR, "getcwd failed"); }
    String *abs_path = Str_newf("%s" CHY_DIR_SEP "%o", cwd, path);
    FREEMEM(cwd);

    return abs_path;
}

static bool
S_rename(const char *from_path, const char *to_path) {
    if (rename(from_path, to_path) != 0) {
        ErrMsg_set_with_errno("rename from '%s' to '%s' failed",
                              from_path, to_path);
        return false;
    }
    else {
        return true;
    }
}

static bool
S_hard_link(const char *from_path, const char *to_path) {
    if (link(from_path, to_path) != 0) {
        ErrMsg_set_with_errno("hard link for new file '%s' from '%s' failed",
                              to_path, from_path);
        return false;
    }
    else {
        return true;
    }
}

static bool
S_delete(const char *path) {
#ifdef CHY_REMOVE_ZAPS_DIRS
    bool result = !remove(path);
#else
    bool result = !rmdir(path) || !remove(path);
#endif
    if (!result) {
        ErrMsg_set_with_errno("removing '%s' failed", path);
    }
    return result;
}

#else
  #error "Need either windows.h or unistd.h"
#endif /* CHY_HAS_UNISTD_H vs. CHY_HAS_WINDOWS_H */


