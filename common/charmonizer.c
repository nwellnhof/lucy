/* This is an auto-generated file -- do not edit directly. */

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

/***************************************************************************/

#line 21 "src/Charmonizer/Core/Defines.h"
/* Charmonizer/Core/Defines.h -- Universal definitions.
 */
#ifndef H_CHAZ_DEFINES
#define H_CHAZ_DEFINES 1

#ifndef true
  #define true 1
  #define false 0
#endif

#define CHAZ_QUOTE(x) #x "\n"

#endif /* H_CHAZ_DEFINES */


/***************************************************************************/

#line 21 "src/Charmonizer/Core/CFlags.h"
/* Charmonizer/Core/CFlags.h
 */

#ifndef H_CHAZ_CFLAGS
#define H_CHAZ_CFLAGS

#define CHAZ_CFLAGS_STYLE_POSIX  1
#define CHAZ_CFLAGS_STYLE_GNU    2
#define CHAZ_CFLAGS_STYLE_MSVC   3
#define CHAZ_CFLAGS_STYLE_SUN_C  4

typedef struct chaz_CFlags chaz_CFlags;

chaz_CFlags*
chaz_CFlags_new(int style);

void
chaz_CFlags_destroy(chaz_CFlags *flags);

const char*
chaz_CFlags_get_string(chaz_CFlags *flags);

void
chaz_CFlags_append(chaz_CFlags *flags, const char *string);

void
chaz_CFlags_clear(chaz_CFlags *flags);

void
chaz_CFlags_set_output_obj(chaz_CFlags *flags, const char *filename);

void
chaz_CFlags_set_output_exe(chaz_CFlags *flags, const char *filename);

void
chaz_CFlags_add_define(chaz_CFlags *flags, const char *name,
                       const char *value);

void
chaz_CFlags_add_include_dir(chaz_CFlags *flags, const char *dir);

void
chaz_CFlags_enable_optimization(chaz_CFlags *flags);

void
chaz_CFlags_disable_strict_aliasing(chaz_CFlags *flags);

void
chaz_CFlags_set_warnings_as_errors(chaz_CFlags *flags);

void
chaz_CFlags_compile_shared_library(chaz_CFlags *flags);

void
chaz_CFlags_hide_symbols(chaz_CFlags *flags);

void
chaz_CFlags_link_shared_library(chaz_CFlags *flags, const char *basename,
                                const char *version,
                                const char *major_version);

void
chaz_CFlags_set_link_output(chaz_CFlags *flags, const char *filename);

void
chaz_CFlags_add_library_path(chaz_CFlags *flags, const char *directory);

void
chaz_CFlags_add_shared_lib(chaz_CFlags *flags, const char *dir,
                           const char *basename, const char *major_version);

void
chaz_CFlags_add_external_lib(chaz_CFlags *flags, const char *library);

void
chaz_CFlags_add_rpath(chaz_CFlags *flags, const char *path);

void
chaz_CFlags_enable_code_coverage(chaz_CFlags *flags);

#endif /* H_CHAZ_CFLAGS */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/CLI.h"
#ifndef H_CHAZ_CLI
#define H_CHAZ_CLI 1

#define CHAZ_CLI_NO_ARG       0
#define CHAZ_CLI_ARG_REQUIRED (1 << 0)
#define CHAZ_CLI_ARG_OPTIONAL (1 << 1)

/* The CLI module provides argument parsing for a command line interface.
 */

typedef struct chaz_CLI chaz_CLI;

/* Constructor.
 *
 * @param name The name of the application.
 * @param description A description of the application.
 */
chaz_CLI*
chaz_CLI_new(const char *name, const char *description);

/* Destructor.
 */
void
chaz_CLI_destroy(chaz_CLI *self);

/* Return a string combining usage header with documentation of options.
 */
const char*
chaz_CLI_help(chaz_CLI *self);

/* Override the generated usage header.
 */
void
chaz_CLI_set_usage(chaz_CLI *self, const char *usage);

/* Register an option.  Updates the "help" string, invalidating previous
 * values.  Returns true on success, or reports an error and returns false if
 * the option was already registered.
 */
int
chaz_CLI_register(chaz_CLI *self, const char *name, const char *help,
                  int flags);

/* Set an option.  The specified option must have been registered previously.
 * The supplied `value` is optional and will be copied.
 *
 * Returns true on success.  Reports an error and returns false on failure.
 */
int
chaz_CLI_set(chaz_CLI *self, const char *name, const char *value);

/* Returns true if the option has been set, false otherwise.
 */
int
chaz_CLI_defined(chaz_CLI *self, const char *name);

/* Return the value of a given option converted to a long int.  Defaults to 0.
 * Reports an error if the named option has not been registered.
 */
long
chaz_CLI_longval(chaz_CLI *self, const char *name);

/* Return the value of an option as a C string.  Defaults to NULL.  Reports an
 * error if the named option has not been registered.
 */
const char*
chaz_CLI_strval(chaz_CLI *self, const char *name);

/* Unset an option, making subsequent calls to `get` return false and making
 * it possible to call `set` again.
 *
 * Returns true if the option exists and was able to be unset.
 */
int
chaz_CLI_unset(chaz_CLI *self, const char *name);

/* Parse `argc` and `argv`, setting options as appropriate.  Returns true on
 * success.  Reports an error and returns false if either an unexpected option
 * was encountered or an option which requires an argument was supplied
 * without one.
 */
int
chaz_CLI_parse(chaz_CLI *self, int argc, const char *argv[]);

#endif /* H_CHAZ_CLI */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/Compiler.h"
/* Charmonizer/Core/Compiler.h
 */

#ifndef H_CHAZ_COMPILER
#define H_CHAZ_COMPILER

#include <stddef.h>
/* #include "Charmonizer/Core/Defines.h" */
/* #include "Charmonizer/Core/CFlags.h" */

#define CHAZ_CC_BINFMT_ELF      1
#define CHAZ_CC_BINFMT_MACHO    2
#define CHAZ_CC_BINFMT_PE       3

/* Attempt to compile and link an executable.  Return true if the executable
 * file exists after the attempt.
 */
int
chaz_CC_compile_exe(const char *source_path, const char *exe_path,
                    const char *code);

/* Attempt to compile an object file.  Return true if the object file
 * exists after the attempt.
 */
int
chaz_CC_compile_obj(const char *source_path, const char *obj_path,
                    const char *code);

/* Attempt to compile the supplied source code and return true if the
 * effort succeeds.
 */
int
chaz_CC_test_compile(const char *source);

/* Attempt to compile and link the supplied source code and return true if
 * the effort succeeds.
 */
int
chaz_CC_test_link(const char *source);

/* Attempt to compile the supplied source code.  If successful, capture the
 * output of the program and return a pointer to a newly allocated buffer.
 * If the compilation fails, return NULL.  The length of the captured
 * output will be placed into the integer pointed to by [output_len].
 */
char*
chaz_CC_capture_output(const char *source, size_t *output_len);

/** Return true if macro is defined.
 */
int
chaz_CC_has_macro(const char *macro);

/** Return true if preprocessor expression matches predicate. Predicate has
 * the form "<op> value", e.g. ">= 0x1500".
 */
int
chaz_CC_test_macro(const char *expression, const char *predicate);

/** Initialize the compiler environment.
 */
void
chaz_CC_init(const char *cc_command, const char *cflags);

/* Clean up the environment.
 */
void
chaz_CC_clean_up(void);

/* Accessor for the compiler executable's string representation.
 */
const char*
chaz_CC_get_cc(void);

/* Accessor for `cflags`.
 */
const char*
chaz_CC_get_cflags(void);

/* Accessor for `extra_cflags`.
 */
chaz_CFlags*
chaz_CC_get_extra_cflags(void);

/* Accessor for `temp_cflags`.
 */
chaz_CFlags*
chaz_CC_get_temp_cflags(void);

/* Return a new CFlags object.
 */
chaz_CFlags*
chaz_CC_new_cflags(void);

/* Return the binary format.
 */
int
chaz_CC_binary_format(void);

/* Return the extension for an executable.
 */
const char*
chaz_CC_exe_ext(void);

/* Return the extension for a shared (dynamic) library.
 */
const char*
chaz_CC_shared_lib_ext(void);

/* Return the extension for a static library.
 */
const char*
chaz_CC_static_lib_ext(void);

/* Return the extension for an import library (Windows).
 */
const char*
chaz_CC_import_lib_ext(void);

/* Return the extension for a compiled object.
 */
const char*
chaz_CC_obj_ext(void);

int
chaz_CC_is_gcc(void);

int
chaz_CC_is_msvc(void);

int
chaz_CC_is_sun_c(void);

int
chaz_CC_is_cygwin(void);

int
chaz_CC_is_mingw(void);

int
chaz_CC_test_gcc_version(const char *predicate);

int
chaz_CC_test_msvc_version(const char *predicate);

int
chaz_CC_test_sun_c_version(const char *predicate);

const char*
chaz_CC_link_command(void);

/* Create a command for building a static library.
 *
 * @param target The target library filename.
 * @param objects The list of object files to be archived in the library.
 */
char*
chaz_CC_format_archiver_command(const char *target, const char *objects);

/* Returns a "ranlib" command if valid.
 *
 * @param target The library filename.
 */
char*
chaz_CC_format_ranlib_command(const char *target);

/** Returns the filename for a shared library.
 *
 * @param dir The target directory or NULL for the current directory.
 * @param basename The name of the library without prefix and extension.
 * @param version The library version.
 */
char*
chaz_CC_shared_lib_filename(const char *dir, const char *basename,
                            const char *version);

/** Returns the filename for an import library.
 *
 * @param dir The target directory or NULL for the current directory.
 * @param basename The name of the library without prefix and extension.
 * @param version The library version.
 */
char*
chaz_CC_import_lib_filename(const char *dir, const char *basename,
                            const char *version);

/** Returns the filename for an MSVC export file.
 *
 * @param dir The target directory or NULL for the current directory.
 * @param basename The name of the library without prefix and extension.
 * @param version The library version.
 */
char*
chaz_CC_export_filename(const char *dir, const char *basename,
                        const char *version);

/** Returns the filename for a static library.
 *
 * @param dir The target directory or NULL for the current directory.
 * @param basename The name of the library without prefix and extension.
 */
char*
chaz_CC_static_lib_filename(const char *dir, const char *basename);

#endif /* H_CHAZ_COMPILER */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/ConfWriter.h"
/* Charmonizer/Core/ConfWriter.h -- Write to a config file.
 */

#ifndef H_CHAZ_CONFWRITER
#define H_CHAZ_CONFWRITER 1

#include <stddef.h>
#include <stdarg.h>
/* #include "Charmonizer/Core/Defines.h" */

struct chaz_ConfWriter;

/* Initialize elements needed by ConfWriter.  Must be called before anything
 * else, but after os and compiler are initialized.
 */
void
chaz_ConfWriter_init(void);

/* Close the include guard on charmony.h, then close the file.  Delete temp
 * files and perform any other needed cleanup.
 */
void
chaz_ConfWriter_clean_up(void);

/* Print output to charmony.h.
 */
void
chaz_ConfWriter_append_conf(const char *fmt, ...);

/* Add a pound-define.
 */
void
chaz_ConfWriter_add_def(const char *sym, const char *value);

/* Add a globally scoped pound-define.
 */
void
chaz_ConfWriter_add_global_def(const char *sym, const char *value);

/* Add a typedef.
 */
void
chaz_ConfWriter_add_typedef(const char *type, const char *alias);

/* Add a globally scoped typedef.
 */
void
chaz_ConfWriter_add_global_typedef(const char *type, const char *alias);

/* Pound-include a system header (within angle brackets).
 */
void
chaz_ConfWriter_add_sys_include(const char *header);

/* Pound-include a locally created header (within quotes).
 */
void
chaz_ConfWriter_add_local_include(const char *header);

/* Print a "chapter heading" comment in the conf file when starting a module.
 */
void
chaz_ConfWriter_start_module(const char *module_name);

/* Leave a little whitespace at the end of each module.
 */
void
chaz_ConfWriter_end_module(void);

void
chaz_ConfWriter_add_writer(struct chaz_ConfWriter *writer);

typedef void
(*chaz_ConfWriter_clean_up_t)(void);
typedef void
(*chaz_ConfWriter_vappend_conf_t)(const char *fmt, va_list args); 
typedef void
(*chaz_ConfWriter_add_def_t)(const char *sym, const char *value);
typedef void
(*chaz_ConfWriter_add_global_def_t)(const char *sym, const char *value);
typedef void
(*chaz_ConfWriter_add_typedef_t)(const char *type, const char *alias);
typedef void
(*chaz_ConfWriter_add_global_typedef_t)(const char *type, const char *alias);
typedef void
(*chaz_ConfWriter_add_sys_include_t)(const char *header);
typedef void
(*chaz_ConfWriter_add_local_include_t)(const char *header);
typedef void
(*chaz_ConfWriter_start_module_t)(const char *module_name);
typedef void
(*chaz_ConfWriter_end_module_t)(void);
typedef struct chaz_ConfWriter {
    chaz_ConfWriter_clean_up_t           clean_up;
    chaz_ConfWriter_vappend_conf_t       vappend_conf;
    chaz_ConfWriter_add_def_t            add_def;
    chaz_ConfWriter_add_global_def_t     add_global_def;
    chaz_ConfWriter_add_typedef_t        add_typedef;
    chaz_ConfWriter_add_global_typedef_t add_global_typedef;
    chaz_ConfWriter_add_sys_include_t    add_sys_include;
    chaz_ConfWriter_add_local_include_t  add_local_include;
    chaz_ConfWriter_start_module_t       start_module;
    chaz_ConfWriter_end_module_t         end_module;
} chaz_ConfWriter;

#endif /* H_CHAZ_CONFWRITER */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/ConfWriterC.h"
/* Charmonizer/Core/ConfWriterC.h -- Write to a C header file.
 */

#ifndef H_CHAZ_CONFWRITERC
#define H_CHAZ_CONFWRITERC 1

/* Enable writing config to a C header file.
 */
void
chaz_ConfWriterC_enable(void);

#endif /* H_CHAZ_CONFWRITERC */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/ConfWriterPerl.h"
/* Charmonizer/Core/ConfWriterPerl.h -- Write to a Perl module file.
 */

#ifndef H_CHAZ_CONFWRITERPERL
#define H_CHAZ_CONFWRITERPERL 1

/* Enable writing config to a Perl module file.
 */
void
chaz_ConfWriterPerl_enable(void);

#endif /* H_CHAZ_CONFWRITERPERL */


/***************************************************************************/

#line 21 "src/Charmonizer/Core/ConfWriterPython.h"
/* Charmonizer/Core/ConfWriterPython.h -- Write to a Python module file.
 */

#ifndef H_CHAZ_CONFWRITERPYTHON
#define H_CHAZ_CONFWRITERPYTHON 1

/* Enable writing config to a Python module file.
 */
void
chaz_ConfWriterPython_enable(void);

#endif /* H_CHAZ_CONFWRITERPYTHON */


/***************************************************************************/

#line 21 "src/Charmonizer/Core/ConfWriterRuby.h"
/* Charmonizer/Core/ConfWriterRuby.h -- Write to a Ruby module file.
 */

#ifndef H_CHAZ_CONFWRITERRUBY
#define H_CHAZ_CONFWRITERRUBY 1

/* Enable writing config to a Ruby module file.
 */
void
chaz_ConfWriterRuby_enable(void);

#endif /* H_CHAZ_CONFWRITERRUBY */


/***************************************************************************/

#line 21 "src/Charmonizer/Core/HeaderChecker.h"
/* Charmonizer/Probe/HeaderChecker.h
 */

#ifndef H_CHAZ_HEAD_CHECK
#define H_CHAZ_HEAD_CHECK

/* #include "Charmonizer/Core/Defines.h" */

/* Bootstrap the HeadCheck.  Call this before anything else.
 */
void
chaz_HeadCheck_init(void);

/* Check for a particular header and return true if it's available.  The
 * test-compile is only run the first time a given request is made.
 */
int
chaz_HeadCheck_check_header(const char *header_name);

/* Attempt to compile a file which pulls in all the headers specified by name
 * in a null-terminated array.  If the compile succeeds, add them all to the
 * internal register and return true.
 */
int
chaz_HeadCheck_check_many_headers(const char **header_names);

/* Return true if the symbol is defined (possibly as a macro). */
int
chaz_HeadCheck_defines_symbol(const char *symbol, const char *includes);

/* Return true if the member is present in the struct. */
int
chaz_HeadCheck_contains_member(const char *struct_name, const char *member,
                               const char *includes);

/*
 * Return the size of the type or 0 if can't be determined. Only checks for
 * sizes 1, 2, 4, 8. If hint != 0, try this size first to speed up the
 * detection.
 */
int
chaz_HeadCheck_size_of_type(const char *type, const char *includes, int hint);

#endif /* H_CHAZ_HEAD_CHECK */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/Make.h"
/* Charmonizer/Core/Make.h
 */

#ifndef H_CHAZ_MAKE
#define H_CHAZ_MAKE

/* #include "Charmonizer/Core/CFlags.h" */

typedef struct chaz_MakeFile chaz_MakeFile;
typedef struct chaz_MakeVar chaz_MakeVar;
typedef struct chaz_MakeRule chaz_MakeRule;
typedef struct chaz_MakeBinary chaz_MakeBinary;

typedef void
(*chaz_Make_file_callback_t)(const char *dir, char *file, void *context);
typedef int
(*chaz_Make_file_filter_t)(const char *dir, char *file, void *context);

/** Initialize the environment.
 *
 * @param make_command Name of the make command. Auto-detect if NULL.
 */
void
chaz_Make_init(chaz_CLI *cli);

/** Clean up the environment.
 */
void
chaz_Make_clean_up(void);

/** Return the name of the detected 'make' executable.
 */
const char*
chaz_Make_get_make(void);

/** Return the type of shell used by the detected 'make' executable.
 */
int
chaz_Make_shell_type(void);

/** Recursively list files in a directory. For every file a callback is called
 * with the filename and a context variable.
 *
 * @param dir Directory to search in.
 * @param ext File extension to search for.
 * @param callback Callback to call for every matching file.
 * @param context Context variable to pass to callback.
 */
void
chaz_Make_list_files(const char *dir, const char *ext,
                     chaz_Make_file_callback_t callback, void *context);

/** MakeFile constructor.
 */
chaz_MakeFile*
chaz_MakeFile_new();

/** MakeFile destructor.
 */
void
chaz_MakeFile_destroy(chaz_MakeFile *self);

/** Add a variable to a makefile.
 *
 * @param name Name of the variable.
 * @param value Value of the variable. Can be NULL if you want add content
 * later.
 * @return a MakeVar.
 */
chaz_MakeVar*
chaz_MakeFile_add_var(chaz_MakeFile *self, const char *name,
                      const char *value);

/** Add a rule to a makefile.
 *
 * @param target The first target of the rule. Can be NULL if you want to add
 * targets later.
 * @param prereq The first prerequisite of the rule. Can be NULL if you want to
 * add prerequisites later.
 * @return a MakeRule.
 */
chaz_MakeRule*
chaz_MakeFile_add_rule(chaz_MakeFile *self, const char *target,
                       const char *prereq);

/** Return the rule for the 'install' target.
 */
chaz_MakeRule*
chaz_MakeFile_install_rule(chaz_MakeFile *self);

/** Return the rule for the 'clean' target.
 */
chaz_MakeRule*
chaz_MakeFile_clean_rule(chaz_MakeFile *self);

/** Return the rule for the 'distclean' target.
 */
chaz_MakeRule*
chaz_MakeFile_distclean_rule(chaz_MakeFile *self);

/** Add an executable. Returns a chaz_MakeBinary object.
 *
 * @param dir The target directory or NULL for the current directory.
 * @param basename The name of the executable without extension.
 * @param installed Whether the executable will be installed.
 */
chaz_MakeBinary*
chaz_MakeFile_add_exe(chaz_MakeFile *self, const char *dir,
                      const char *basename, int installed);

/** Add a shared library. The library will be built in the current directory.
 * Returns a chaz_MakeBinary object.
 *
 * @param dir The target directory or NULL for the current directory.
 * @param basename The name of the library without prefix and extension.
 * @param version The version of the library.
 * @param major_version The major version of the library.
 * @param installed Whether the library will be installed.
 */
chaz_MakeBinary*
chaz_MakeFile_add_shared_lib(chaz_MakeFile *self, const char *dir,
                             const char *basename, const char *version,
                             const char *major_version, int installed);

/** Add a static library. The library will be built in the current directory.
 * Returns a chaz_MakeBinary object.
 *
 * @param dir The target directory or NULL for the current directory.
 * @param basename The name of the library without prefix and extension.
 * @param installed Whether the library will be installed.
 */
chaz_MakeBinary*
chaz_MakeFile_add_static_lib(chaz_MakeFile *self, const char *dir,
                             const char *basename, int installed);

/** Add a rule to build the lemon parser generator.
 *
 * @param dir The lemon directory.
 */
chaz_MakeBinary*
chaz_MakeFile_add_lemon_exe(chaz_MakeFile *self, const char *dir);

/** Add a rule for a lemon grammar.
 *
 * @param base_name The filename of the grammar without extension.
 */
chaz_MakeRule*
chaz_MakeFile_add_lemon_grammar(chaz_MakeFile *self, const char *base_name);

/** Add command to install rule that copies a file to a target directory.
 *
 * @param src Path to the file.
 * @param root Destination root directory.
 * @param dest Destination directory relative to root. May be NULL.
 */
void
chaz_MakeFile_install(chaz_MakeFile *self, const char *src, const char *root,
                      const char *dest);

/** Add command to install rule that copies a directory to a target
 * directory.
 *
 * @param src Path to the directory.
 * @param root Destination root directory.
 * @param dest Destination directory relative to root. May be NULL.
 */
void
chaz_MakeFile_install_dir(chaz_MakeFile *self, const char *src,
                          const char *root, const char *dest);

/** Add command to install rule that creates a pkgconfig file in
 * `$(LIBDIR)/pkgconfig`. The following pkgconfig variables are set:
 *
 * - `version`: Contains the value of the `version` argument.
 * - `libdir`: Contains the value of $(LIBDIR).
 *
 * @param name Name of the pkgconfig file without extension.
 * @param version The version.
 * @param content The main content of the pkgconfig file.
 */
void
chaz_MakeFile_install_pkgconfig(chaz_MakeFile *self, const char *name,
                                const char *version, const char *content);

/** Write the makefile to a file named 'Makefile' in the current directory.
 */
void
chaz_MakeFile_write(chaz_MakeFile *self);

/** Append content to a makefile variable. The new content will be separated
 * from the existing content with whitespace.
 *
 * @param element The additional content.
 */
void
chaz_MakeVar_append(chaz_MakeVar *self, const char *element);

/** Add another target to a makefile rule.
 *
 * @param target The additional rule.
 */
void
chaz_MakeRule_add_target(chaz_MakeRule *self, const char *target);

/** Add another prerequisite to a makefile rule.
 *
 * @param prereq The additional prerequisite.
 */
void
chaz_MakeRule_add_prereq(chaz_MakeRule *self, const char *prereq);

/** Add a command to a rule.
 *
 * @param command The additional command.
 */
void
chaz_MakeRule_add_command(chaz_MakeRule *self, const char *command);

/** Add a command to create a directory.
 *
 * @param files The directory.
 */
void
chaz_MakeRule_add_mkdir_command(chaz_MakeRule *self, const char *dir);

/** Add a command to remove one or more files.
 *
 * @param files The list of files.
 */
void
chaz_MakeRule_add_rm_command(chaz_MakeRule *self, const char *files);

/** Add a command to remove one or more directories.
 *
 * @param dirs The list of directories.
 */
void
chaz_MakeRule_add_recursive_rm_command(chaz_MakeRule *self, const char *dirs);

/** Add one or more commands to call another makefile recursively.
 *
 * @param dir The directory in which to call the makefile.
 * @param target The target to call. Pass NULL for the default target.
 */
void
chaz_MakeRule_add_make_command(chaz_MakeRule *self, const char *dir,
                               const char *target);

/** Add a source file for the binary.
 *
 * @param dir The source directory or NULL for the current directory.
 * @param filename The filename.
 */
void
chaz_MakeBinary_add_src_file(chaz_MakeBinary *self, const char *dir,
                             const char *filename);

/** Add all .c files in a directory as sources for the binary.
 *
 * @param path The path to the directory.
 */
void
chaz_MakeBinary_add_src_dir(chaz_MakeBinary *self, const char *path);

/** Add .c files in a directory as sources for the binary if they match
 * a filter.
 *
 * @param path The path to the directory.
 * @param filter A callback that is invoked for every source file. The
 * source file is only added if the callback returns true. May be NULL.
 * @param context Context passed to filter.
 */
void
chaz_MakeBinary_add_filtered_src_dir(chaz_MakeBinary *self, const char *path,
                                     chaz_Make_file_filter_t filter,
                                     void *context);

/** Add a prerequisite to the make rule of the binary.
 *
 * @param prereq The prerequisite.
 */
void
chaz_MakeBinary_add_prereq(chaz_MakeBinary *self, const char *prereq);

/** Return a list of all objects separated by space.
 */
char*
chaz_MakeBinary_obj_string(chaz_MakeBinary *self);

/** Accessor for target.
 */
const char*
chaz_MakeBinary_get_target(chaz_MakeBinary *self);

/** Accessor for compile flags.
 */
chaz_CFlags*
chaz_MakeBinary_get_compile_flags(chaz_MakeBinary *self);

/** Accessor for link flags.
 */
chaz_CFlags*
chaz_MakeBinary_get_link_flags(chaz_MakeBinary *self);

#endif /* H_CHAZ_MAKE */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/OperatingSystem.h"
/* Charmonizer/Core/OperatingSystem.h - abstract an operating system down to a few
 * variables.
 */

#ifndef H_CHAZ_OPER_SYS
#define H_CHAZ_OPER_SYS

#define CHAZ_OS_POSIX    1
#define CHAZ_OS_CMD_EXE  2

/* Safely remove a file named [name]. Needed because of Windows quirks.
 * Returns true on success, false on failure.
 */
int
chaz_OS_remove(const char *name);

/* Invoke a command and attempt to suppress output from both stdout and stderr
 * (as if they had been sent to /dev/null).  If it's not possible to run the
 * command quietly, run it anyway.
 */
int
chaz_OS_run_quietly(const char *command);

/* Capture both stdout and stderr for a command to the supplied filepath.
 */
int
chaz_OS_run_redirected(const char *command, const char *path);

/* Run a command beginning with the name of an executable in the current
 * working directory and capture both stdout and stderr to the supplied
 * filepath.
 */
int
chaz_OS_run_local_redirected(const char *command, const char *path);

/* Run a command and return the output from stdout.
 */
char*
chaz_OS_run_and_capture(const char *command, size_t *output_len);

/* Attempt to create a directory.
 */
void
chaz_OS_mkdir(const char *filepath);

/* Attempt to remove a directory, which must be empty.
 */
void
chaz_OS_rmdir(const char *filepath);

/* Return the equivalent of /dev/null on this system.
 */
const char*
chaz_OS_dev_null(void);

/* Return the directory separator on this system.
 */
const char*
chaz_OS_dir_sep(void);

/* Return the shell type of this system.
 */
int
chaz_OS_shell_type(void);

/* Return the file extension for executables on this system. This can be
 * a different value than returned by chaz_CC_exe_ext() when
 * cross-compiling.
 */
const char*
chaz_OS_exe_ext(void);

/* Initialize the Charmonizer/Core/OperatingSystem module.
 */
void
chaz_OS_init(void);

#endif /* H_CHAZ_COMPILER */



/***************************************************************************/

#line 21 "src/Charmonizer/Core/Util.h"
/* Chaz/Core/Util.h -- miscellaneous utilities.
 */

#ifndef H_CHAZ_UTIL
#define H_CHAZ_UTIL 1

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

extern int chaz_Util_verbosity;

/* Open a file (truncating if necessary) and write [content] to it.  Util_die() if
 * an error occurs.
 */
void
chaz_Util_write_file(const char *filename, const char *content);

/* Read an entire file into memory.
 */
char*
chaz_Util_slurp_file(const char *file_path, size_t *len_ptr);

/* Return a newly allocated copy of a NULL-terminated string.
 */
char*
chaz_Util_strdup(const char *string);

/* Join a NULL-terminated list of strings using a separator.
 */
char*
chaz_Util_join(const char *sep, ...);

/* Join a NULL-terminated list of strings using a separator.
 */
char*
chaz_Util_vjoin(const char *sep, va_list args);

/* Get the length of a file (may overshoot on text files under DOS).
 */
long
chaz_Util_flength(void *file);

/* Print an error message to stderr and exit.
 */
void
chaz_Util_die(const char *format, ...);

/* Print an error message to stderr.
 */
void
chaz_Util_warn(const char *format, ...);

/* Attept to delete a file.  Return true if the file is gone, whether or not
 * it was there to begin with.  Issue a warning and return false if the file
 * still exists.
 */
int
chaz_Util_remove_and_verify(const char *file_path);

/* Attempt to open a file for reading, then close it immediately.
 */
int
chaz_Util_can_open_file(const char *file_path);

#endif /* H_CHAZ_UTIL */



/***************************************************************************/

#line 21 "src/Charmonizer/Probe.h"
#ifndef H_CHAZ
#define H_CHAZ 1

#include <stddef.h>
#include <stdio.h>

struct chaz_CLI;

/* Parse command line arguments, initializing and filling in the supplied
 * `args` struct.
 *
 *     APP_NAME --cc=CC_COMMAND
 *              [--enable-c]
 *              [--enable-perl]
 *              [--enable-python]
 *              [--enable-ruby]
 *              [-- [CFLAGS]]
 *
 * @return true if argument parsing proceeds without incident, false if
 * unexpected arguments are encountered or values are missing or invalid.
 */
int
chaz_Probe_parse_cli_args(int argc, const char *argv[],
                          struct chaz_CLI *cli);

/* Exit after printing usage instructions to stderr.
 */
void
chaz_Probe_die_usage(void);

/* Set up the Charmonizer environment.
 *
 * If the environment variable CHARM_VERBOSITY has been set, it will be
 * processed at this time:
 *
 *      0 - silent
 *      1 - normal
 *      2 - debugging
 */
void
chaz_Probe_init(struct chaz_CLI *cli);

/* Clean up the Charmonizer environment -- deleting tempfiles, etc.  This
 * should be called only after everything else finishes.
 */
void
chaz_Probe_clean_up(void);

#endif /* Include guard. */



/***************************************************************************/

#line 21 "src/Charmonizer/Probe/AtomicOps.h"
/* Charmonizer/Probe/AtomicOps.h
 */

#ifndef H_CHAZ_ATOMICOPS
#define H_CHAZ_ATOMICOPS

#include <stdio.h>

/* Run the AtomicOps module.
 *
 * These following symbols will be defined if the associated headers are
 * available:
 *
 * HAS_LIBKERN_OSATOMIC_H  <libkern/OSAtomic.h> (Mac OS X)
 * HAS_SYS_ATOMIC_H        <sys/atomic.h>       (Solaris)
 * HAS_INTRIN_H            <intrin.h>           (Windows)
 *
 * This symbol is defined if OSAtomicCompareAndSwapPtr is available:
 *
 * HAS_OSATOMIC_CAS_PTR
 */
void chaz_AtomicOps_run(void);

#endif /* H_CHAZ_ATOMICOPS */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/Booleans.h"
/* Charmonizer/Probe/Booleans.h -- bool type.
 *
 * If stdbool.h is is available, it will be pound-included in the configuration
 * header.  If it is not, the following typedef will be defined:
 *
 * bool
 *
 * These symbols will be defined if they are not already:
 *
 * true
 * false
 */

#ifndef H_CHAZ_BOOLEANS
#define H_CHAZ_BOOLEANS

#include <stdio.h>

/* Run the Booleans module.
 */
void chaz_Booleans_run(void);

#endif /* H_CHAZ_BOOLEANS */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/BuildEnv.h"
/* Charmonizer/Probe/BuildEnv.h -- Build environment.
 *
 * Capture various information about the build environment, including the C
 * compiler's interface, the shell, the operating system, etc.
 *
 * The following symbols will be defined:
 *
 * CC - String representation of the C compiler executable.
 * CFLAGS - C compiler flags.
 * EXTRA_CFLAGS - Extra C compiler flags.
 */

#ifndef H_CHAZ_BUILDENV
#define H_CHAZ_BUILDENV

#include <stdio.h>

/* Run the BuildEnv module.
 */
void chaz_BuildEnv_run(void);

#endif /* H_CHAZ_BUILDENV */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/DirManip.h"
/* Charmonizer/Probe/DirManip.h
 */

#ifndef H_CHAZ_DIRMANIP
#define H_CHAZ_DIRMANIP

/* The DirManip module exports or aliases symbols related to directory and file
 * manipulation.
 *
 * Defined if the header files dirent.h and direct.h are available, respectively:
 *
 * HAS_DIRENT_H
 * HAS_DIRECT_H
 *
 * Defined if struct dirent has these members.
 *
 * HAS_DIRENT_D_NAMLEN
 * HAS_DIRENT_D_TYPE
 *
 * The "makedir" macro will be aliased to the POSIX-specified two-argument
 * "mkdir" interface:
 *
 * makedir
 *
 * On some systems, the second argument to makedir will be ignored, in which
 * case this symbol will be true; otherwise, it will be false: (TODO: This
 * isn't verified and may sometimes be incorrect.)
 *
 * MAKEDIR_MODE_IGNORED
 *
 * String representing the system's directory separator:
 *
 * DIR_SEP
 *
 * True if the remove() function removes directories, false otherwise:
 *
 * REMOVE_ZAPS_DIRS
 */
void chaz_DirManip_run(void);

#endif /* H_CHAZ_DIR_SEP */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/Floats.h"
/* Charmonizer/Probe/Floats.h -- floating point types.
 *
 * The following symbols will be created if the platform supports IEEE 754
 * floating point types:
 *
 * F32_NAN
 * F32_INF
 * F32_NEGINF
 * F64_NAN
 * F64_INF
 * F64_NEGINF
 *
 * TODO: Actually test to see whether IEEE 754 is supported, rather than just
 * lying about it.
 */

#ifndef H_CHAZ_FLOATS
#define H_CHAZ_FLOATS

/* Run the Floats module.
 */
void
chaz_Floats_run(void);

/* Return the name of the math library to link against or NULL.
 */
const char*
chaz_Floats_math_library(void);

#endif /* H_CHAZ_FLOATS */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/FuncMacro.h"
/* Charmonizer/Probe/FuncMacro.h
 */

#ifndef H_CHAZ_FUNC_MACRO
#define H_CHAZ_FUNC_MACRO

#include <stdio.h>

/* Run the FuncMacro module.
 *
 * If __func__ successfully resolves, this will be defined:
 *
 * HAS_ISO_FUNC_MACRO
 *
 * If __FUNCTION__ successfully resolves, this will be defined:
 *
 * HAS_GNUC_FUNC_MACRO
 *
 * If one or the other succeeds, these will be defined:
 *
 * HAS_FUNC_MACRO
 * FUNC_MACRO
 *
 * The "inline" keyword will also be probed for.  If it is available, the
 * following macro will be defined to "inline", otherwise it will be defined
 * to nothing.
 *
 * INLINE
 */
void chaz_FuncMacro_run(void);

#endif /* H_CHAZ_FUNC_MACRO */




/***************************************************************************/

#line 20 "src/Charmonizer/Probe/Headers.h"
/* Charmonizer/Probe/Headers.h
 */

#ifndef H_CHAZ_HEADERS
#define H_CHAZ_HEADERS

#include <stdio.h>
/* #include "Charmonizer/Core/Defines.h" */

/* Check whether a particular header file is available.  The test-compile is
 * only run the first time a given request is made.
 */
int
chaz_Headers_check(const char *header_name);

/* Run the Headers module.
 *
 * Exported symbols:
 *
 * If HAS_C89 is declared, this system has all the header files described in
 * Ansi C 1989.  HAS_C90 is a synonym.  (It would be surprising if they are
 * not defined, because Charmonizer itself assumes C89.)
 *
 * HAS_C89
 * HAS_C90
 *
 * One symbol is exported for each C89 header file:
 *
 * HAS_ASSERT_H
 * HAS_CTYPE_H
 * HAS_ERRNO_H
 * HAS_FLOAT_H
 * HAS_LIMITS_H
 * HAS_LOCALE_H
 * HAS_MATH_H
 * HAS_SETJMP_H
 * HAS_SIGNAL_H
 * HAS_STDARG_H
 * HAS_STDDEF_H
 * HAS_STDIO_H
 * HAS_STDLIB_H
 * HAS_STRING_H
 * HAS_TIME_H
 *
 * One symbol is exported for every POSIX header present, and HAS_POSIX is
 * exported if they're all there.
 *
 * HAS_POSIX
 *
 * HAS_CPIO_H
 * HAS_DIRENT_H
 * HAS_FCNTL_H
 * HAS_GRP_H
 * HAS_PWD_H
 * HAS_SYS_STAT_H
 * HAS_SYS_TIMES_H
 * HAS_SYS_TYPES_H
 * HAS_SYS_UTSNAME_H
 * HAS_WAIT_H
 * HAS_TAR_H
 * HAS_TERMIOS_H
 * HAS_UNISTD_H
 * HAS_UTIME_H
 *
 * If pthread.h is available, this will be exported:
 *
 * HAS_PTHREAD_H
 */
void
chaz_Headers_run(void);

#endif /* H_CHAZ_HEADERS */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/Integers.h"
/* Charmonizer/Probe/Integers.h -- info about integer types and sizes.
 *
 * One or the other of these will be defined, depending on whether the
 * processor is big-endian or little-endian.
 *
 * BIG_END
 * LITTLE_END
 *
 * These will always be defined:
 *
 * SIZEOF_CHAR
 * SIZEOF_SHORT
 * SIZEOF_INT
 * SIZEOF_LONG
 * SIZEOF_PTR
 *
 * If long longs are available these symbols will be defined:
 *
 * HAS_LONG_LONG
 * SIZEOF_LONG_LONG
 *
 * Similarly, with the __int64 type (the sizeof is included for completeness):
 *
 * HAS___INT64
 * SIZEOF___INT64
 *
 * If the inttypes.h or stdint.h header files are available, these may be
 * defined:
 *
 * HAS_INTTYPES_H
 * HAS_STDINT_H
 *
 * If stdint.h is is available, it will be pound-included in the configuration
 * header.  If it is not, the following typedefs and macros will be defined if
 * possible:
 *
 * int8_t
 * int16_t
 * int32_t
 * int64_t
 * uint8_t
 * uint16_t
 * uint32_t
 * uint64_t
 * INT8_MAX
 * INT16_MAX
 * INT32_MAX
 * INT64_MAX
 * INT8_MIN
 * INT16_MIN
 * INT32_MIN
 * INT64_MIN
 * UINT8_MAX
 * UINT16_MAX
 * UINT32_MAX
 * UINT64_MAX
 * SIZE_MAX
 * INT32_C
 * INT64_C
 * UINT32_C
 * UINT64_C
 *
 * If inttypes.h is is available, it will be pound-included in the
 * configuration header.  If it is not, the following macros will be defined if
 * possible:
 *
 * PRId64
 * PRIu64
 *
 * Availability of integer types is indicated by which of these are defined:
 *
 * HAS_INT8_T
 * HAS_INT16_T
 * HAS_INT32_T
 * HAS_INT64_T
 *
 * If 64-bit integers are available, this macro will promote pointers to i64_t
 * safely.
 *
 * PTR_TO_I64(ptr)
 */

#ifndef H_CHAZ_INTEGERS
#define H_CHAZ_INTEGERS

#include <stdio.h>

/* Run the Integers module.
 */
void chaz_Integers_run(void);

#endif /* H_CHAZ_INTEGERS */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/LargeFiles.h"
/* Charmonizer/Probe/LargeFiles.h
 */

#ifndef H_CHAZ_LARGE_FILES
#define H_CHAZ_LARGE_FILES

#include <stdio.h>

/* The LargeFiles module attempts to detect these symbols or alias them to
 * synonyms:
 *
 * off64_t
 * fopen64
 * ftello64
 * fseeko64
 * lseek64
 * pread64
 *
 * If off64_t or its equivalent is available, this will be defined:
 *
 * HAS_64BIT_OFFSET_TYPE
 *
 * If 64-bit variants of fopen, ftell, and fseek are available, this will be
 * defined:
 *
 * HAS_64BIT_STDIO
 *
 * If 64-bit variants of pread and lseek are available, then corresponding
 * symbols will be defined:
 *
 * HAS_64BIT_PREAD
 * HAS_64BIT_LSEEK
 *
 * Use of the off64_t symbol may require sys/types.h.
 */
void chaz_LargeFiles_run(void);

#endif /* H_CHAZ_LARGE_FILES */



/***************************************************************************/

#line 21 "src/Charmonizer/Probe/Memory.h"
/* Charmonizer/Probe/Memory.h
 */

#ifndef H_CHAZ_MEMORY
#define H_CHAZ_MEMORY

/* The Memory module attempts to detect these symbols or alias them to
 * synonyms:
 *
 * alloca
 *
 * These following symbols will be defined if the associated headers are
 * available:
 *
 * HAS_SYS_MMAN_H          <sys/mman.h>
 * HAS_ALLOCA_H            <alloca.h>
 * HAS_MALLOC_H            <malloc.h>
 *
 * Defined if alloca() is available via stdlib.h:
 *
 * ALLOCA_IN_STDLIB_H
 */
void chaz_Memory_run(void);

#endif /* H_CHAZ_MEMORY */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/RegularExpressions.h"
/* Charmonizer/Probe/RegularExpressions.h -- regular expressions.
 */

#ifndef H_CHAZ_REGULAREXPRESSIONS
#define H_CHAZ_REGULAREXPRESSIONS

/* Run the RegularExpressions module.
 */
void chaz_RegularExpressions_run(void);

#endif /* H_CHAZ_REGULAREXPRESSIONS */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/Strings.h"
/* Charmonizer/Probe/Strings.h
 */

#ifndef H_CHAZ_STRINGS
#define H_CHAZ_STRINGS

/* The Strings module attempts to detect whether snprintf works as specified
 * by the C99 standard. It also looks for system-specific functions which can
 * be used to emulate snprintf.
 */
void chaz_Strings_run(void);

#endif /* H_CHAZ_STRINGS */



/***************************************************************************/

#line 21 "src/Charmonizer/Probe/SymbolVisibility.h"
/* Charmonizer/Probe/SymbolVisibility.h
 */

#ifndef H_CHAZ_SYMBOLVISIBILITY
#define H_CHAZ_SYMBOLVISIBILITY

void chaz_SymbolVisibility_run(void);

#endif /* H_CHAZ_SYMBOLVISIBILITY */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/UnusedVars.h"
/* Charmonizer/Probe/UnusedVars.h
 */

#ifndef H_CHAZ_UNUSED_VARS
#define H_CHAZ_UNUSED_VARS

#include <stdio.h>

/* Run the UnusedVars module.
 *
 * These symbols are exported:
 *
 * UNUSED_VAR(var)
 * UNREACHABLE_RETURN(type)
 *
 */
void chaz_UnusedVars_run(void);

#endif /* H_CHAZ_UNUSED_VARS */




/***************************************************************************/

#line 21 "src/Charmonizer/Probe/VariadicMacros.h"
/* Charmonizer/Probe/VariadicMacros.h
 */

#ifndef H_CHAZ_VARIADIC_MACROS
#define H_CHAZ_VARIADIC_MACROS

#include <stdio.h>

/* Run the VariadicMacros module.
 *
 * If your compiler supports ISO-style variadic macros, this will be defined:
 *
 * HAS_ISO_VARIADIC_MACROS
 *
 * If your compiler supports GNU-style variadic macros, this will be defined:
 *
 * HAS_GNUC_VARIADIC_MACROS
 *
 * If you have at least one of the above, this will be defined:
 *
 * HAS_VARIADIC_MACROS
 */
void chaz_VariadicMacros_run(void);

#endif /* H_CHAZ_VARIADIC_MACROS */




/***************************************************************************/

#line 17 "src/Charmonizer/Core/CFlags.c"
#include <string.h>
#include <stdlib.h>
/* #include "Charmonizer/Core/CFlags.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */

struct chaz_CFlags {
    int   style;
    char *string;
};

chaz_CFlags*
chaz_CFlags_new(int style) {
    chaz_CFlags *flags = (chaz_CFlags*)malloc(sizeof(chaz_CFlags));
    flags->style  = style;
    flags->string = chaz_Util_strdup("");
    return flags;
}

void
chaz_CFlags_destroy(chaz_CFlags *flags) {
    free(flags->string);
    free(flags);
}

const char*
chaz_CFlags_get_string(chaz_CFlags *flags) {
    return flags->string;
}

void
chaz_CFlags_append(chaz_CFlags *flags, const char *string) {
    char *new_string;
    if (flags->string[0] == '\0') {
        new_string = chaz_Util_strdup(string);
    }
    else {
        new_string = chaz_Util_join(" ", flags->string, string, NULL);
    }
    free(flags->string);
    flags->string = new_string;
}

void
chaz_CFlags_clear(chaz_CFlags *flags) {
    if (flags->string[0] != '\0') {
        free(flags->string);
        flags->string = chaz_Util_strdup("");
    }
}

void
chaz_CFlags_set_output_obj(chaz_CFlags *flags, const char *filename) {
    const char *output;
    char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        output = "/c /Fo";
    }
    else {
        /* POSIX */
        output = "-c -o ";
    }
    string = chaz_Util_join("", output, filename, NULL);
    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_set_output_exe(chaz_CFlags *flags, const char *filename) {
    const char *output;
    char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        output = "/Fe";
    }
    else {
        /* POSIX */
        output = "-o ";
    }
    string = chaz_Util_join("", output, filename, NULL);
    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_add_define(chaz_CFlags *flags, const char *name,
                       const char *value) {
    const char *define;
    char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        define = "/D";
    }
    else {
        /* POSIX */
        define = "-D ";
    }
    if (value) {
        string = chaz_Util_join("", define, name, "=", value, NULL);
    }
    else {
        string = chaz_Util_join("", define, name, NULL);
    }
    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_add_include_dir(chaz_CFlags *flags, const char *dir) {
    const char *include;
    char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC)  {
        include = "/I ";
    }
    else {
        /* POSIX */
        include = "-I ";
    }
    string = chaz_Util_join("", include, dir, NULL);
    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_enable_optimization(chaz_CFlags *flags) {
    const char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        string = "/O2";
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        string = "-O2";
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        string = "-xO4";
    }
    else {
        /* POSIX */
        string = "-O 1";
    }
    chaz_CFlags_append(flags, string);
}

void
chaz_CFlags_enable_debugging(chaz_CFlags *flags) {
    if (flags->style == CHAZ_CFLAGS_STYLE_GNU
        || flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        chaz_CFlags_append(flags, "-g");
    }
}

void
chaz_CFlags_disable_strict_aliasing(chaz_CFlags *flags) {
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        return;
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        chaz_CFlags_append(flags, "-fno-strict-aliasing");
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        chaz_CFlags_append(flags, "-xalias_level=any");
    }
    else {
        chaz_Util_die("Don't know how to disable strict aliasing with '%s'",
                      chaz_CC_get_cc());
    }
}

void
chaz_CFlags_set_warnings_as_errors(chaz_CFlags *flags) {
    const char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        string = "/WX";
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        string = "-Werror";
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        string = "-errwarn=%all";
    }
    else {
        chaz_Util_die("Don't know how to set warnings as errors with '%s'",
                      chaz_CC_get_cc());
    }
    chaz_CFlags_append(flags, string);
}

void
chaz_CFlags_compile_shared_library(chaz_CFlags *flags) {
    const char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        string = "/MD";
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        int binary_format = chaz_CC_binary_format();
        if (binary_format == CHAZ_CC_BINFMT_MACHO) {
            string = "-fno-common";
        }
        else if (binary_format == CHAZ_CC_BINFMT_ELF) {
            string = "-fPIC";
        }
        else {
            /* MinGW. */
            return;
        }
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        string = "-KPIC";
    }
    else {
        return;
    }
    chaz_CFlags_append(flags, string);
}

void
chaz_CFlags_hide_symbols(chaz_CFlags *flags) {
    if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        if (chaz_CC_binary_format() != CHAZ_CC_BINFMT_PE) {
            chaz_CFlags_append(flags, "-fvisibility=hidden");
        }
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        static int checked = 0;
        static int version_ge_550;

        if (!checked) {
            /* Requires Sun Studio 8. */
            version_ge_550 = chaz_CC_test_sun_c_version(">= 0x550");
            checked = 1;
        }

        if (version_ge_550) {
            chaz_CFlags_append(flags, "-xldscope=hidden");
        }
    }
}

void
chaz_CFlags_link_shared_library(chaz_CFlags *flags, const char *basename,
                                const char *version,
                                const char *major_version) {
    char *string = NULL;

    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        string = chaz_Util_strdup("/DLL");
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        int binary_format = chaz_CC_binary_format();

        if (binary_format == CHAZ_CC_BINFMT_MACHO) {
            string = chaz_Util_join(" ", "-dynamiclib", "-current_version",
                                    version, "-compatibility_version",
                                    major_version, NULL);
        }
        else if (binary_format == CHAZ_CC_BINFMT_ELF) {
            string = chaz_Util_join("", "-shared -Wl,-soname,lib", basename,
                                    ".so.", major_version, NULL);
        }
        else if (binary_format == CHAZ_CC_BINFMT_PE) {
            string = chaz_Util_join("", "-shared -Wl,--out-implib,lib",
                                    basename, "-", major_version, ".dll.a",
                                    NULL);
        }
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        string = chaz_Util_join("", "-G -h lib", basename, ".so.",
                                major_version, NULL);
    }
    else {
        chaz_Util_die("Don't know how to link a shared library with '%s'",
                      chaz_CC_get_cc());
    }

    if (string) {
        chaz_CFlags_append(flags, string);
        free(string);
    }
}

void
chaz_CFlags_set_link_output(chaz_CFlags *flags, const char *filename) {
    const char *output;
    char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        output = "/OUT:";
    }
    else {
        output = "-o ";
    }
    string = chaz_Util_join("", output, filename, NULL);
    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_add_library_path(chaz_CFlags *flags, const char *directory) {
    const char *lib_path;
    char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        if (strcmp(directory, ".") == 0) {
            /* The MS linker searches the current directory by default. */
            return;
        }
        else {
            lib_path = "/LIBPATH:";
        }
    }
    else {
        lib_path = "-L ";
    }
    string = chaz_Util_join("", lib_path, directory, NULL);
    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_add_shared_lib(chaz_CFlags *flags, const char *dir,
                           const char *basename, const char *major_version) {
    int binfmt = chaz_CC_binary_format();
    char *filename;
    if (binfmt == CHAZ_CC_BINFMT_PE) {
        filename = chaz_CC_import_lib_filename(dir, basename, major_version);
    }
    else {
        filename = chaz_CC_shared_lib_filename(dir, basename, major_version);
    }
    chaz_CFlags_append(flags, filename);
    free(filename);
}

void
chaz_CFlags_add_external_lib(chaz_CFlags *flags, const char *library) {
    char *string;
    if (flags->style == CHAZ_CFLAGS_STYLE_MSVC) {
        string = chaz_Util_join("", library, ".lib", NULL);
    }
    else {
        string = chaz_Util_join(" ", "-l", library, NULL);
    }
    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_add_rpath(chaz_CFlags *flags, const char *path) {
    char *string;

    if (chaz_CC_binary_format() != CHAZ_CC_BINFMT_ELF) { return; }

    if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        string = chaz_Util_join("", "-Wl,-rpath,", path, NULL);
    }
    else if (flags->style == CHAZ_CFLAGS_STYLE_SUN_C) {
        string = chaz_Util_join(" ", "-R", path, NULL);
    }
    else {
        chaz_Util_die("Don't know how to set rpath with '%s'",
                      chaz_CC_get_cc());
    }

    chaz_CFlags_append(flags, string);
    free(string);
}

void
chaz_CFlags_enable_code_coverage(chaz_CFlags *flags) {
    if (flags->style == CHAZ_CFLAGS_STYLE_GNU) {
        chaz_CFlags_append(flags, "--coverage");
    }
    else {
        chaz_Util_die("Don't know how to enable code coverage with '%s'",
                      chaz_CC_get_cc());
    }
}



/***************************************************************************/

#line 17 "src/Charmonizer/Core/CLI.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
/* #include "Charmonizer/Core/CLI.h" */
/* #include "Charmonizer/Core/Util.h" */

typedef struct chaz_CLIOption {
    char *name;
    char *help;
    char *value;
    int   defined;
    int   flags;
} chaz_CLIOption;

struct chaz_CLI {
    char *name;
    char *desc;
    char *usage;
    char *help;
    chaz_CLIOption *opts;
    int   num_opts;
};

static void
S_chaz_CLI_error(chaz_CLI *self, const char *pattern, ...) {
    va_list ap;
    (void)self;
    if (chaz_Util_verbosity > 0) {
        va_start(ap, pattern);
        vfprintf(stderr, pattern, ap);
        va_end(ap);
        fprintf(stderr, "\n");
    }
}

static void
S_chaz_CLI_rebuild_help(chaz_CLI *self) {
    int i;
    size_t amount = 200; /* Length of section headers. */

    /* Allocate space. */
    if (self->usage) {
        amount += strlen(self->usage);
    }
    else {
        amount += strlen(self->name);
    }
    if (self->desc) {
        amount += strlen(self->desc);
    }
    for (i = 0; i < self->num_opts; i++) {
        chaz_CLIOption *opt = &self->opts[i];
        amount += 24 + 2 * strlen(opt->name);
        if (opt->flags) {
            amount += strlen(opt->name);
        }
        if (opt->help) {
            amount += strlen(opt->help);
        }
    }
    free(self->help);
    self->help = (char*)malloc(amount);
    self->help[0] = '\0';

    /* Accumulate "help" string. */
    if (self->usage) {
        strcat(self->help, self->usage);
    }
    else {
        strcat(self->help, "Usage: ");
        strcat(self->help, self->name);
        if (self->num_opts) {
            strcat(self->help, " [OPTIONS]");
        }
    }
    if (self->desc) {
        strcat(self->help, "\n\n");
        strcat(self->help, self->desc);
    }
    strcat(self->help, "\n");
    if (self->num_opts) {
        strcat(self->help, "\nArguments:\n");
        for (i = 0; i < self->num_opts; i++) {
            chaz_CLIOption *opt = &self->opts[i];
            size_t line_start = strlen(self->help);
            size_t current_len;

            strcat(self->help, "  --");
            strcat(self->help, opt->name);
            current_len = strlen(self->help);
            if (opt->flags) {
                int j;
                if (opt->flags & CHAZ_CLI_ARG_OPTIONAL) {
                    self->help[current_len++] = '[';
                }
                self->help[current_len++] = '=';
                for (j = 0; opt->name[j]; j++) {
                    unsigned char c = (unsigned char)opt->name[j];
                    self->help[current_len++] = toupper(c);
                }
                if (opt->flags & CHAZ_CLI_ARG_OPTIONAL) {
                    self->help[current_len++] = ']';
                }
                self->help[current_len] = '\0';
            }
            if (opt->help) {
                self->help[current_len++] = ' ';
                while (current_len - line_start < 25) {
                    self->help[current_len++] = ' ';
                }
                self->help[current_len] = '\0';
                strcpy(self->help + current_len, opt->help);
            }
            strcat(self->help, "\n");
        }
    }
    strcat(self->help, "\n");
}

static chaz_CLIOption*
S_chaz_CLI_find_opt(chaz_CLI *self, const char *name) {
    int i;
    for (i = 0; i < self->num_opts; i++) {
        chaz_CLIOption *opt = &self->opts[i];
        if (strcmp(opt->name, name) == 0) {
            return opt;
        }
    }
    return NULL;
}

chaz_CLI*
chaz_CLI_new(const char *name, const char *description) {
    chaz_CLI *self  = calloc(1, sizeof(chaz_CLI));
    self->name      = chaz_Util_strdup(name ? name : "PROGRAM");
    self->desc      = description ? chaz_Util_strdup(description) : NULL;
    self->help      = NULL;
    self->opts      = NULL;
    self->num_opts  = 0;
    S_chaz_CLI_rebuild_help(self);
    return self;
}

void
chaz_CLI_destroy(chaz_CLI *self) {
    int i;
    for (i = 0; i < self->num_opts; i++) {
        chaz_CLIOption *opt = &self->opts[i];
        free(opt->name);
        free(opt->help);
        free(opt->value);
    }
    free(self->name);
    free(self->desc);
    free(self->opts);
    free(self->usage);
    free(self->help);
    free(self);
}

void
chaz_CLI_set_usage(chaz_CLI *self, const char *usage) {
    free(self->usage);
    self->usage = chaz_Util_strdup(usage);
}

const char*
chaz_CLI_help(chaz_CLI *self) {
    return self->help;
}

int
chaz_CLI_register(chaz_CLI *self, const char *name, const char *help,
                  int flags) {
    int rank;
    int i;
    int arg_required = !!(flags & CHAZ_CLI_ARG_REQUIRED);
    int arg_optional = !!(flags & CHAZ_CLI_ARG_OPTIONAL);

    /* Validate flags */
    if (arg_required && arg_optional) {
        S_chaz_CLI_error(self, "Conflicting flags: value both optional "
                         "and required");
        return 0;
    }

    /* Insert new option.  Keep options sorted by name. */
    for (rank = self->num_opts; rank > 0; rank--) {
        int comparison = strcmp(name, self->opts[rank - 1].name);
        if (comparison == 0) {
            S_chaz_CLI_error(self, "Option '%s' already registered", name);
            return 0;
        }
        else if (comparison > 0) {
            break;
        }
    }
    self->num_opts += 1;
    self->opts = realloc(self->opts, self->num_opts * sizeof(chaz_CLIOption));
    for (i = self->num_opts - 1; i > rank; i--) {
        self->opts[i] = self->opts[i - 1];
    }
    self->opts[rank].name    = chaz_Util_strdup(name);
    self->opts[rank].help    = help ? chaz_Util_strdup(help) : NULL;
    self->opts[rank].flags   = flags;
    self->opts[rank].defined = 0;
    self->opts[rank].value   = NULL;

    /* Update `help` with new option. */
    S_chaz_CLI_rebuild_help(self);

    return 1;
}

int
chaz_CLI_set(chaz_CLI *self, const char *name, const char *value) {
    chaz_CLIOption *opt = S_chaz_CLI_find_opt(self, name);
    if (opt == NULL) {
        S_chaz_CLI_error(self, "Attempt to set unknown option: '%s'", name);
        return 0;
    }
    if (opt->defined) {
        S_chaz_CLI_error(self, "'%s' specified multiple times", name);
        return 0;
    }
    opt->defined = 1;
    if (opt->flags == CHAZ_CLI_NO_ARG) {
        if (value != NULL) {
            S_chaz_CLI_error(self, "'%s' expects no value", name);
            return 0;
        }
    }
    else {
        if (value == NULL) {
            S_chaz_CLI_error(self, "'%s' expects a value", name);
            return 0;
        }
        opt->value = chaz_Util_strdup(value);
    }
    return 1;
}

int
chaz_CLI_unset(chaz_CLI *self, const char *name) {
    chaz_CLIOption *opt = S_chaz_CLI_find_opt(self, name);
    if (opt == NULL) {
        S_chaz_CLI_error(self, "Attempt to unset unknown option: '%s'", name);
        return 0;
    }
    free(opt->value);
    opt->value = NULL;
    opt->defined = 0;
    return 1;
}

int
chaz_CLI_defined(chaz_CLI *self, const char *name) {
    chaz_CLIOption *opt = S_chaz_CLI_find_opt(self, name);
    if (opt == NULL) {
        S_chaz_CLI_error(self, "Inquiry for unknown option: '%s'", name);
        return 0;
    }
    return opt->defined;
}

long
chaz_CLI_longval(chaz_CLI *self, const char *name) {
    chaz_CLIOption *opt = S_chaz_CLI_find_opt(self, name);
    if (opt == NULL) {
        S_chaz_CLI_error(self, "Longval request for unknown option: '%s'",
                         name);
        return 0;
    }
    if (!opt->defined || !opt->value) {
        return 0;
    }
    return strtol(opt->value, NULL, 10);
}

const char*
chaz_CLI_strval(chaz_CLI *self, const char *name) {
    chaz_CLIOption *opt = S_chaz_CLI_find_opt(self, name);
    if (opt == NULL) {
        S_chaz_CLI_error(self, "Strval request for unknown option: '%s'",
                         name);
        return 0;
    }
    return opt->value;
}

int
chaz_CLI_parse(chaz_CLI *self, int argc, const char *argv[]) {
    int i;
    char *name = NULL;
    size_t name_cap = 0;

    /* Parse most args. */
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        size_t name_len = 0;
        const char *value = NULL;

        /* Stop processing if we see `-` or `--`. */
        if (strcmp(arg, "--") == 0 || strcmp(arg, "-") == 0) {
            break;
        }

        if (strncmp(arg, "--", 2) != 0) {
            S_chaz_CLI_error(self, "Unexpected argument: '%s'", arg);
            free(name);
            return 0;
        }

        /* Extract the name of the argument, look for a potential value. */
        while (1) {
            char c = arg[name_len + 2];
            if (isalnum((unsigned char)c) || c == '-' || c == '_') {
                name_len++;
            }
            else if (c == '\0') {
                break;
            }
            else if (c == '=') {
                /* The rest of the arg is the value. */
                value = arg + 2 + name_len + 1;
                break;
            }
            else {
                free(name);
                S_chaz_CLI_error(self, "Malformed argument: '%s'", arg);
                return 0;
            }
        }
        if (name_len + 1 > name_cap) {
            name_cap = name_len + 1;
            name = (char*)realloc(name, name_cap);
        }
        memcpy(name, arg + 2, name_len);
        name[name_len] = '\0';

        if (value == NULL && i + 1 < argc) {
            /* Support both '--opt=val' and '--opt val' styles. */
            chaz_CLIOption *opt = S_chaz_CLI_find_opt(self, name);
            if (opt == NULL) {
                S_chaz_CLI_error(self, "Attempt to set unknown option: '%s'",
                                 name);
                free(name);
                return 0;
            }
            if (opt->flags != CHAZ_CLI_NO_ARG) {
                i++;
                value = argv[i];
            }
        }

        /* Attempt to set the option. */
        if (!chaz_CLI_set(self, name, value)) {
            free(name);
            return 0;
        }
    }

    free(name);

    for (i = 0; i < self->num_opts; i++) {
        chaz_CLIOption *opt = &self->opts[i];
        if (!opt->defined && (opt->flags & CHAZ_CLI_ARG_REQUIRED)) {
            S_chaz_CLI_error(self, "Option '%s' is required", opt->name);
            return 0;
        }
    }

    return 1;
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/Compiler.c"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */

/* Detect binary format.
 */
static void
chaz_CC_detect_binary_format(const char *filename);

/* Detect macros which may help to identify some compilers.
 */
static void
chaz_CC_detect_known_compilers(void);

/** Build a library filename from its components.
 */
static char*
chaz_CC_build_lib_filename(const char *dir, const char *prefix,
                           const char *basename, const char *version,
                           const char *ext);

/* Temporary files. */
#define CHAZ_CC_TRY_SOURCE_PATH  "_charmonizer_try.c"
#define CHAZ_CC_TRY_BASENAME     "_charmonizer_try"
#define CHAZ_CC_TARGET_PATH      "_charmonizer_target"

/* Static vars. */
static struct {
    char     *cc_command;
    char     *cflags;
    char     *try_exe_name;
    char      exe_ext[10];
    char      shared_lib_ext[10];
    char      static_lib_ext[10];
    char      import_lib_ext[10];
    char      obj_ext[10];
    char      gcc_version_str[30];
    int       binary_format;
    int       cflags_style;
    int       is_gcc;
    int       is_msvc;
    int       is_clang;
    int       is_sun_c;
    int       is_cygwin;
    int       is_mingw;
    chaz_CFlags *extra_cflags;
    chaz_CFlags *temp_cflags;
} chaz_CC = {
    NULL, NULL, NULL,
    "", "", "", "", "", "",
    0, 0, 0, 0, 0, 0, 0, 0,
    NULL, NULL
};

void
chaz_CC_init(const char *compiler_command, const char *compiler_flags) {
    const char *code = "int main() { return 0; }\n";
    int compile_succeeded = 0;

    if (chaz_Util_verbosity) { printf("Creating compiler object...\n"); }

    /* Assign, init. */
    chaz_CC.cc_command   = chaz_Util_strdup(compiler_command);
    chaz_CC.cflags       = chaz_Util_strdup(compiler_flags);
    chaz_CC.extra_cflags = NULL;
    chaz_CC.temp_cflags  = NULL;

    /* Set names for the targets which we "try" to compile. */
    strcpy(chaz_CC.exe_ext, ".exe");
    chaz_CC.try_exe_name
        = chaz_Util_join("", CHAZ_CC_TRY_BASENAME, chaz_CC.exe_ext, NULL);

    /* If we can't compile or execute anything, game over. */
    if (chaz_Util_verbosity) {
        printf("Trying to compile and execute a small test file...\n");
    }

    /* Try MSVC argument style. */
    if (!compile_succeeded) {
        chaz_CC.cflags_style = CHAZ_CFLAGS_STYLE_MSVC;
        if (!chaz_Util_remove_and_verify(chaz_CC.try_exe_name)) {
            chaz_Util_die("Failed to delete file '%s'", chaz_CC.try_exe_name);
        }
        compile_succeeded = chaz_CC_compile_exe(CHAZ_CC_TRY_SOURCE_PATH,
                                                CHAZ_CC_TRY_BASENAME, code);
        if (compile_succeeded) {
            strcpy(chaz_CC.obj_ext, ".obj");
        }
    }

    /* Try POSIX argument style. */
    if (!compile_succeeded) {
        chaz_CC.cflags_style = CHAZ_CFLAGS_STYLE_POSIX;
        if (!chaz_Util_remove_and_verify(chaz_CC.try_exe_name)) {
            chaz_Util_die("Failed to delete file '%s'", chaz_CC.try_exe_name);
        }
        compile_succeeded = chaz_CC_compile_exe(CHAZ_CC_TRY_SOURCE_PATH,
                                                CHAZ_CC_TRY_BASENAME, code);
        if (compile_succeeded) {
            strcpy(chaz_CC.obj_ext, ".o");
        }
    }

    if (!compile_succeeded) {
        chaz_Util_die("Failed to compile a small test file");
    }
    chaz_CC_detect_binary_format(chaz_CC.try_exe_name);
    chaz_Util_remove_and_verify(chaz_CC.try_exe_name);

    chaz_CC_detect_known_compilers();

    if (chaz_CC_is_gcc()) {
        chaz_CC.cflags_style = CHAZ_CFLAGS_STYLE_GNU;
    }
    else if (chaz_CC_is_msvc()) {
        chaz_CC.cflags_style = CHAZ_CFLAGS_STYLE_MSVC;
    }
    else if (chaz_CC_is_sun_c()) {
        chaz_CC.cflags_style = CHAZ_CFLAGS_STYLE_SUN_C;
    }
    else {
        chaz_CC.cflags_style = CHAZ_CFLAGS_STYLE_POSIX;
    }
    chaz_CC.extra_cflags = chaz_CFlags_new(chaz_CC.cflags_style);
    chaz_CC.temp_cflags  = chaz_CFlags_new(chaz_CC.cflags_style);

    /* File extensions. */
    if (chaz_CC.binary_format == CHAZ_CC_BINFMT_ELF) {
        if (chaz_Util_verbosity) {
            printf("Detected binary format: ELF\n");
        }
        strcpy(chaz_CC.exe_ext, "");
        strcpy(chaz_CC.shared_lib_ext, ".so");
        strcpy(chaz_CC.static_lib_ext, ".a");
        strcpy(chaz_CC.obj_ext, ".o");
    }
    else if (chaz_CC.binary_format == CHAZ_CC_BINFMT_MACHO) {
        if (chaz_Util_verbosity) {
            printf("Detected binary format: Mach-O\n");
        }
        strcpy(chaz_CC.exe_ext, "");
        strcpy(chaz_CC.shared_lib_ext, ".dylib");
        strcpy(chaz_CC.static_lib_ext, ".a");
        strcpy(chaz_CC.obj_ext, ".o");
    }
    else if (chaz_CC.binary_format == CHAZ_CC_BINFMT_PE) {
        if (chaz_Util_verbosity) {
            printf("Detected binary format: Portable Executable\n");
        }
        strcpy(chaz_CC.exe_ext, ".exe");
        strcpy(chaz_CC.shared_lib_ext, ".dll");
        if (chaz_CC_is_gcc()) {
            strcpy(chaz_CC.static_lib_ext, ".a");
            strcpy(chaz_CC.import_lib_ext, ".dll.a");
            strcpy(chaz_CC.obj_ext, ".o");
        }
        else {
            strcpy(chaz_CC.static_lib_ext, ".lib");
            strcpy(chaz_CC.import_lib_ext, ".lib");
            strcpy(chaz_CC.obj_ext, ".obj");
        }

        if (chaz_CC_has_macro("__CYGWIN__")) {
            chaz_CC.is_cygwin = 1;
        }
        if (chaz_CC_has_macro("__MINGW32__")) {
            chaz_CC.is_mingw = 1;
        }
    }
    else {
        chaz_Util_die("Failed to detect binary format");
    }

    free(chaz_CC.try_exe_name);
    chaz_CC.try_exe_name
        = chaz_Util_join("", CHAZ_CC_TRY_BASENAME, chaz_CC.exe_ext, NULL);
}

static void
chaz_CC_detect_binary_format(const char *filename) {
    char *output;
    size_t output_len;
    int binary_format = 0;

    output = chaz_Util_slurp_file(filename, &output_len);

    /* ELF. */
    if (binary_format == 0 && output_len >= 4
        && memcmp(output, "\x7F" "ELF", 4) == 0
       ) {
        binary_format = CHAZ_CC_BINFMT_ELF;
    }

    /* Macho-O. */
    if (binary_format == 0 && output_len >= 4
        && (memcmp(output, "\xCA\xFE\xBA\xBE", 4) == 0      /* Fat binary. */
            || memcmp(output, "\xFE\xED\xFA\xCE", 4) == 0   /* 32-bit BE. */
            || memcmp(output, "\xFE\xED\xFA\xCF", 4) == 0   /* 64-bit BE. */
            || memcmp(output, "\xCE\xFA\xED\xFE", 4) == 0   /* 32-bit LE. */
            || memcmp(output, "\xCF\xFA\xED\xFE", 4) == 0)  /* 64-bit LE. */
       ) {
        binary_format = CHAZ_CC_BINFMT_MACHO;
    }

    /* Portable Executable. */
    if (binary_format == 0 && output_len >= 0x40
        && memcmp(output, "MZ", 2) == 0
       ) {
        size_t pe_header_off =
            (unsigned char)output[0x3C]
            | ((unsigned char)output[0x3D] << 8)
            | ((unsigned char)output[0x3E] << 16)
            | ((unsigned char)output[0x3F] << 24);

        if (output_len >= pe_header_off + 4
            && memcmp(output + pe_header_off, "PE\0\0", 4) == 0
           ) {
            binary_format = CHAZ_CC_BINFMT_PE;
        }
    }

    chaz_CC.binary_format = binary_format;
    free(output);
}

int
chaz_CC_has_macro(const char *macro) {
    static const char template[] =
        CHAZ_QUOTE(  #ifdef %s             )
        CHAZ_QUOTE(  int i;                )
        CHAZ_QUOTE(  #else                 )
        CHAZ_QUOTE(  #error "nope"         )
        CHAZ_QUOTE(  #endif                );
    size_t size = sizeof(template)
                  + strlen(macro)
                  + 20;
    char *code = (char*)malloc(size);
    int retval = 0;
    sprintf(code, template, macro);
    retval = chaz_CC_test_compile(code);
    free(code);
    return retval;
}

int
chaz_CC_test_macro(const char *expression, const char *predicate) {
    static const char template[] =
        CHAZ_QUOTE(  #if (%s) %s           )
        CHAZ_QUOTE(  int i;                )
        CHAZ_QUOTE(  #else                 )
        CHAZ_QUOTE(  #error "nope"         )
        CHAZ_QUOTE(  #endif                );
    size_t size = sizeof(template)
                  + strlen(expression)
                  + strlen(predicate)
                  + 20;
    char *code = (char*)malloc(size);
    int retval = 0;
    sprintf(code, template, expression, predicate);
    retval = chaz_CC_test_compile(code);
    free(code);
    return retval;
}

static void
chaz_CC_detect_known_compilers(void) {
    chaz_CC.is_gcc   = chaz_CC_has_macro("__GNUC__");
    chaz_CC.is_msvc  = chaz_CC_has_macro("_MSC_VER");
    chaz_CC.is_clang = chaz_CC_has_macro("__clang__");
    chaz_CC.is_sun_c = chaz_CC_has_macro("__SUNPRO_C");
}

void
chaz_CC_clean_up(void) {
    free(chaz_CC.cc_command);
    free(chaz_CC.cflags);
    free(chaz_CC.try_exe_name);
    chaz_CFlags_destroy(chaz_CC.extra_cflags);
    chaz_CFlags_destroy(chaz_CC.temp_cflags);
}

int
chaz_CC_compile_exe(const char *source_path, const char *exe_name,
                    const char *code) {
    chaz_CFlags *local_cflags = chaz_CFlags_new(chaz_CC.cflags_style);
    const char *extra_cflags_string = "";
    const char *temp_cflags_string  = "";
    const char *local_cflags_string;
    char *exe_file = chaz_Util_join("", exe_name, chaz_CC.exe_ext, NULL);
    char *command;
    int result;

    /* Write the source file. */
    chaz_Util_write_file(source_path, code);

    /* Prepare and run the compiler command. */
    if (chaz_CC.extra_cflags) {
        extra_cflags_string = chaz_CFlags_get_string(chaz_CC.extra_cflags);
    }
    if (chaz_CC.temp_cflags) {
        temp_cflags_string = chaz_CFlags_get_string(chaz_CC.temp_cflags);
    }
    chaz_CFlags_set_output_exe(local_cflags, exe_file);
    local_cflags_string = chaz_CFlags_get_string(local_cflags);
    command = chaz_Util_join(" ", chaz_CC.cc_command, chaz_CC.cflags,
                             source_path, extra_cflags_string,
                             temp_cflags_string, local_cflags_string, NULL);
    if (chaz_Util_verbosity < 2) {
        chaz_OS_run_quietly(command);
    }
    else {
        printf("%s\n", command);
        system(command);
    }

    if (chaz_CC_is_msvc()) {
        /* Zap MSVC junk. */
        size_t  junk_buf_size = strlen(exe_file) + 4;
        char   *junk          = (char*)malloc(junk_buf_size);
        sprintf(junk, "%s.obj", exe_name);
        chaz_Util_remove_and_verify(junk);
        sprintf(junk, "%s.ilk", exe_name);
        chaz_Util_remove_and_verify(junk);
        sprintf(junk, "%s.pdb", exe_name);
        chaz_Util_remove_and_verify(junk);
        free(junk);
    }

    /* See if compilation was successful.  Remove the source file. */
    result = chaz_Util_can_open_file(exe_file);
    if (!chaz_Util_remove_and_verify(source_path)) {
        chaz_Util_die("Failed to remove '%s'", source_path);
    }

    chaz_CFlags_destroy(local_cflags);
    free(command);
    free(exe_file);
    return result;
}

int
chaz_CC_compile_obj(const char *source_path, const char *obj_name,
                    const char *code) {
    chaz_CFlags *local_cflags = chaz_CFlags_new(chaz_CC.cflags_style);
    const char *extra_cflags_string = "";
    const char *temp_cflags_string  = "";
    const char *local_cflags_string;
    char *obj_file = chaz_Util_join("", obj_name, chaz_CC.obj_ext, NULL);
    char *command;
    int result;

    /* Write the source file. */
    chaz_Util_write_file(source_path, code);

    /* Prepare and run the compiler command. */
    if (chaz_CC.extra_cflags) {
        extra_cflags_string = chaz_CFlags_get_string(chaz_CC.extra_cflags);
    }
    if (chaz_CC.temp_cflags) {
        temp_cflags_string = chaz_CFlags_get_string(chaz_CC.temp_cflags);
    }
    chaz_CFlags_set_output_obj(local_cflags, obj_file);
    local_cflags_string = chaz_CFlags_get_string(local_cflags);
    command = chaz_Util_join(" ", chaz_CC.cc_command, chaz_CC.cflags,
                             source_path, extra_cflags_string,
                             temp_cflags_string, local_cflags_string, NULL);
    if (chaz_Util_verbosity < 2) {
        chaz_OS_run_quietly(command);
    }
    else {
        printf("%s\n", command);
        system(command);
    }

    /* See if compilation was successful.  Remove the source file. */
    result = chaz_Util_can_open_file(obj_file);
    if (!chaz_Util_remove_and_verify(source_path)) {
        chaz_Util_die("Failed to remove '%s'", source_path);
    }

    chaz_CFlags_destroy(local_cflags);
    free(command);
    free(obj_file);
    return result;
}

int
chaz_CC_test_compile(const char *source) {
    int compile_succeeded;
    char *try_obj_name
        = chaz_Util_join("", CHAZ_CC_TRY_BASENAME, chaz_CC.obj_ext, NULL);
    if (!chaz_Util_remove_and_verify(try_obj_name)) {
        chaz_Util_die("Failed to delete file '%s'", try_obj_name);
    }
    compile_succeeded = chaz_CC_compile_obj(CHAZ_CC_TRY_SOURCE_PATH,
                                            CHAZ_CC_TRY_BASENAME, source);
    chaz_Util_remove_and_verify(try_obj_name);
    free(try_obj_name);
    return compile_succeeded;
}

int
chaz_CC_test_link(const char *source) {
    int link_succeeded;
    if (!chaz_Util_remove_and_verify(chaz_CC.try_exe_name)) {
        chaz_Util_die("Failed to delete file '%s'", chaz_CC.try_exe_name);
    }
    link_succeeded = chaz_CC_compile_exe(CHAZ_CC_TRY_SOURCE_PATH,
                                         CHAZ_CC_TRY_BASENAME, source);
    chaz_Util_remove_and_verify(chaz_CC.try_exe_name);
    return link_succeeded;
}

char*
chaz_CC_capture_output(const char *source, size_t *output_len) {
    char *captured_output = NULL;
    int compile_succeeded;

    /* Clear out previous versions and test to make sure removal worked. */
    if (!chaz_Util_remove_and_verify(chaz_CC.try_exe_name)) {
        chaz_Util_die("Failed to delete file '%s'", chaz_CC.try_exe_name);
    }
    if (!chaz_Util_remove_and_verify(CHAZ_CC_TARGET_PATH)) {
        chaz_Util_die("Failed to delete file '%s'", CHAZ_CC_TARGET_PATH);
    }

    /* Attempt compilation; if successful, run app and slurp output. */
    compile_succeeded = chaz_CC_compile_exe(CHAZ_CC_TRY_SOURCE_PATH,
                                            CHAZ_CC_TRY_BASENAME, source);
    if (compile_succeeded) {
        chaz_OS_run_local_redirected(chaz_CC.try_exe_name,
                                     CHAZ_CC_TARGET_PATH);
        captured_output = chaz_Util_slurp_file(CHAZ_CC_TARGET_PATH,
                                               output_len);
    }
    else {
        *output_len = 0;
    }

    /* Remove all the files we just created. */
    chaz_Util_remove_and_verify(CHAZ_CC_TRY_SOURCE_PATH);
    chaz_Util_remove_and_verify(chaz_CC.try_exe_name);
    chaz_Util_remove_and_verify(CHAZ_CC_TARGET_PATH);

    return captured_output;
}

const char*
chaz_CC_get_cc(void) {
    return chaz_CC.cc_command;
}

const char*
chaz_CC_get_cflags(void) {
    return chaz_CC.cflags;
}

chaz_CFlags*
chaz_CC_get_extra_cflags(void) {
    return chaz_CC.extra_cflags;
}

chaz_CFlags*
chaz_CC_get_temp_cflags(void) {
    return chaz_CC.temp_cflags;
}

chaz_CFlags*
chaz_CC_new_cflags(void) {
    return chaz_CFlags_new(chaz_CC.cflags_style);
}

int
chaz_CC_binary_format(void) {
    return chaz_CC.binary_format;
}

const char*
chaz_CC_exe_ext(void) {
    return chaz_CC.exe_ext;
}

const char*
chaz_CC_shared_lib_ext(void) {
    return chaz_CC.shared_lib_ext;
}

const char*
chaz_CC_static_lib_ext(void) {
    return chaz_CC.static_lib_ext;
}

const char*
chaz_CC_import_lib_ext(void) {
    return chaz_CC.import_lib_ext;
}

const char*
chaz_CC_obj_ext(void) {
    return chaz_CC.obj_ext;
}

int
chaz_CC_is_gcc(void) {
    return chaz_CC.is_gcc;
}

int
chaz_CC_is_msvc(void) {
    return chaz_CC.is_msvc;
}

int
chaz_CC_is_sun_c(void) {
    return chaz_CC.is_sun_c;
}

int
chaz_CC_is_cygwin(void) {
    return chaz_CC.is_cygwin;
}

int
chaz_CC_is_mingw(void) {
    return chaz_CC.is_mingw;
}

int
chaz_CC_test_gcc_version(const char *predicate) {
    static const char version[] =
        "10000 * __GNUC__ + 100 * __GNUC_MINOR__ + __GNUC_PATCHLEVEL__";
    return chaz_CC_test_macro(version, predicate);
}

int
chaz_CC_test_msvc_version(const char *predicate) {
    return chaz_CC_test_macro("_MSC_VER", predicate);
}

int
chaz_CC_test_sun_c_version(const char *predicate) {
    return chaz_CC_test_macro("__SUNPRO_C", predicate);
}

const char*
chaz_CC_link_command() {
    if (chaz_CC_is_msvc()) {
        return "link";
    }
    else {
        return chaz_CC.cc_command;
    }
}

char*
chaz_CC_format_archiver_command(const char *target, const char *objects) {
    if (chaz_CC_is_msvc()) {
        /* TODO: Write `objects` to a temporary file in order to avoid
         * exceeding line length limits. */
        char *out = chaz_Util_join("", "/OUT:", target, NULL);
        char *command = chaz_Util_join(" ", "lib", "/NOLOGO", objects, out,
                                       NULL);
        free(out);
        return command;
    }
    else {
        return chaz_Util_join(" ", "ar", "rcs", target, objects, NULL);
    }
}

char*
chaz_CC_format_ranlib_command(const char *target) {
    if (chaz_CC_is_msvc()) {
        return NULL;
    }
    return chaz_Util_join(" ", "ranlib", target, NULL);
}

char*
chaz_CC_shared_lib_filename(const char *dir, const char *basename,
                            const char *version) {
    /* Cygwin uses a "cyg" prefix for shared libraries. */
    const char *prefix = chaz_CC_is_msvc()
                         ? ""
                         : chaz_CC_is_cygwin() ? "cyg" : "lib";
    return chaz_CC_build_lib_filename(dir, prefix, basename, version,
                                      chaz_CC.shared_lib_ext);
}

char*
chaz_CC_import_lib_filename(const char *dir, const char *basename,
                            const char *version) {
    const char *prefix = chaz_CC_is_msvc() ? "" : "lib";
    return chaz_CC_build_lib_filename(dir, prefix, basename, version,
                                      chaz_CC.import_lib_ext);
}

char*
chaz_CC_export_filename(const char *dir, const char *basename,
                        const char *version) {
    /* Only for MSVC. */
    return chaz_CC_build_lib_filename(dir, "", basename, version, ".exp");
}

static char*
chaz_CC_build_lib_filename(const char *dir, const char *prefix,
                           const char *basename, const char *version,
                           const char *ext) {
    char *suffix;
    char *retval;

    if (version == NULL) {
        suffix = chaz_Util_strdup(ext);
    }
    else {
        int binary_format = chaz_CC_binary_format();

        if (binary_format == CHAZ_CC_BINFMT_PE) {
            suffix = chaz_Util_join("", "-", version, ext, NULL);
        }
        else if (binary_format == CHAZ_CC_BINFMT_MACHO) {
            suffix = chaz_Util_join("", ".", version, ext, NULL);
        }
        else if (binary_format == CHAZ_CC_BINFMT_ELF) {
            suffix = chaz_Util_join("", ext, ".", version, NULL);
        }
        else {
            chaz_Util_die("Unsupported binary format");
            return NULL;
        }
    }

    if (dir == NULL || strcmp(dir, ".") == 0) {
        retval = chaz_Util_join("", prefix, basename, suffix, NULL);
    }
    else {
        const char *dir_sep = chaz_OS_dir_sep();
        retval = chaz_Util_join("", dir, dir_sep, prefix, basename, suffix,
                                NULL);
    }

    free(suffix);
    return retval;
}

char*
chaz_CC_static_lib_filename(const char *dir, const char *basename) {
    const char *prefix = chaz_CC_is_msvc() ? "" : "lib";

    if (dir == NULL || strcmp(dir, ".") == 0) {
        return chaz_Util_join("", prefix, basename, chaz_CC.static_lib_ext,
                              NULL);
    }
    else {
        const char *dir_sep = chaz_OS_dir_sep();
        return chaz_Util_join("", dir, dir_sep, prefix, basename,
                              chaz_CC.static_lib_ext, NULL);
    }
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/ConfWriter.c"
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
#include <stdarg.h>
#include <stdio.h>

#define CW_MAX_WRITERS 10
static struct {
    chaz_ConfWriter *writers[CW_MAX_WRITERS];
    size_t num_writers;
} chaz_CW;

void
chaz_ConfWriter_init(void) {
    chaz_CW.num_writers = 0;
    return;
}

void
chaz_ConfWriter_clean_up(void) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->clean_up();
    }
}

void
chaz_ConfWriter_append_conf(const char *fmt, ...) {
    va_list args;
    size_t i;
    
    for (i = 0; i < chaz_CW.num_writers; i++) {
        va_start(args, fmt);
        chaz_CW.writers[i]->vappend_conf(fmt, args);
        va_end(args);
    }
}

void
chaz_ConfWriter_add_def(const char *sym, const char *value) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->add_def(sym, value);
    }
}

void
chaz_ConfWriter_add_global_def(const char *sym, const char *value) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->add_global_def(sym, value);
    }
}

void
chaz_ConfWriter_add_typedef(const char *type, const char *alias) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->add_typedef(type, alias);
    }
}

void
chaz_ConfWriter_add_global_typedef(const char *type, const char *alias) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->add_global_typedef(type, alias);
    }
}

void
chaz_ConfWriter_add_sys_include(const char *header) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->add_sys_include(header);
    }
}

void
chaz_ConfWriter_add_local_include(const char *header) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->add_local_include(header);
    }
}

void
chaz_ConfWriter_start_module(const char *module_name) {
    size_t i;
    if (chaz_Util_verbosity > 0) {
        printf("Running %s module...\n", module_name);
    }
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->start_module(module_name);
    }
}

void
chaz_ConfWriter_end_module(void) {
    size_t i;
    for (i = 0; i < chaz_CW.num_writers; i++) {
        chaz_CW.writers[i]->end_module();
    }
}

void
chaz_ConfWriter_add_writer(chaz_ConfWriter *writer) {
    chaz_CW.writers[chaz_CW.num_writers] = writer;
    chaz_CW.num_writers++;
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/ConfWriterC.c"
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/ConfWriterC.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */
/* #include "Charmonizer/Core/Compiler.h" */
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum chaz_ConfElemType {
    CHAZ_CONFELEM_DEF,
    CHAZ_CONFELEM_GLOBAL_DEF,
    CHAZ_CONFELEM_TYPEDEF,
    CHAZ_CONFELEM_GLOBAL_TYPEDEF,
    CHAZ_CONFELEM_SYS_INCLUDE,
    CHAZ_CONFELEM_LOCAL_INCLUDE
} chaz_ConfElemType;

typedef struct chaz_ConfElem {
    char *str1;
    char *str2;
    chaz_ConfElemType type;
} chaz_ConfElem;

/* Static vars. */
static struct {
    FILE          *fh;
    char          *MODULE_NAME;
    chaz_ConfElem *defs;
    size_t         def_cap;
    size_t         def_count;
} chaz_ConfWriterC = { NULL, NULL, NULL, 0, 0 };
static chaz_ConfWriter CWC_conf_writer;

/* Open the charmony.h file handle.  Print supplied text to it, if non-null.
 * Print an explanatory comment and open the include guard.
 */
static void
chaz_ConfWriterC_open_charmony_h(const char *charmony_start);

/* Push a new elem onto the def list. */
static void
chaz_ConfWriterC_push_def_list_item(const char *str1, const char *str2,
                     chaz_ConfElemType type);

/* Free the def list. */
static void
chaz_ConfWriterC_clear_def_list(void);

static void
chaz_ConfWriterC_clean_up(void);
static void
chaz_ConfWriterC_vappend_conf(const char *fmt, va_list args);
static void
chaz_ConfWriterC_add_def(const char *sym, const char *value);
static void
chaz_ConfWriterC_add_global_def(const char *sym, const char *value);
static void
chaz_ConfWriterC_add_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterC_add_global_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterC_add_sys_include(const char *header);
static void
chaz_ConfWriterC_add_local_include(const char *header);
static void
chaz_ConfWriterC_start_module(const char *module_name);
static void
chaz_ConfWriterC_end_module(void);

void
chaz_ConfWriterC_enable(void) {
    CWC_conf_writer.clean_up           = chaz_ConfWriterC_clean_up;
    CWC_conf_writer.vappend_conf       = chaz_ConfWriterC_vappend_conf;
    CWC_conf_writer.add_def            = chaz_ConfWriterC_add_def;
    CWC_conf_writer.add_global_def     = chaz_ConfWriterC_add_global_def;
    CWC_conf_writer.add_typedef        = chaz_ConfWriterC_add_typedef;
    CWC_conf_writer.add_global_typedef = chaz_ConfWriterC_add_global_typedef;
    CWC_conf_writer.add_sys_include    = chaz_ConfWriterC_add_sys_include;
    CWC_conf_writer.add_local_include  = chaz_ConfWriterC_add_local_include;
    CWC_conf_writer.start_module       = chaz_ConfWriterC_start_module;
    CWC_conf_writer.end_module         = chaz_ConfWriterC_end_module;
    chaz_ConfWriterC_open_charmony_h(NULL);
    chaz_ConfWriter_add_writer(&CWC_conf_writer);
    return;
}

static void
chaz_ConfWriterC_open_charmony_h(const char *charmony_start) {
    /* Open the filehandle. */
    chaz_ConfWriterC.fh = fopen("charmony.h", "w+");
    if (chaz_ConfWriterC.fh == NULL) {
        chaz_Util_die("Can't open 'charmony.h': %s", strerror(errno));
    }

    /* Print supplied text (if any) along with warning, open include guard. */
    if (charmony_start != NULL) {
        fwrite(charmony_start, sizeof(char), strlen(charmony_start),
               chaz_ConfWriterC.fh);
    }
    fprintf(chaz_ConfWriterC.fh,
            "/* Header file auto-generated by Charmonizer. \n"
            " * DO NOT EDIT THIS FILE!!\n"
            " */\n\n"
            "#ifndef H_CHARMONY\n"
            "#define H_CHARMONY 1\n\n"
           );
}

static void
chaz_ConfWriterC_clean_up(void) {
    /* Write the last bit of charmony.h and close. */
    fprintf(chaz_ConfWriterC.fh, "#endif /* H_CHARMONY */\n\n");
    if (fclose(chaz_ConfWriterC.fh)) {
        chaz_Util_die("Couldn't close 'charmony.h': %s", strerror(errno));
    }
}

static void
chaz_ConfWriterC_vappend_conf(const char *fmt, va_list args) {
    vfprintf(chaz_ConfWriterC.fh, fmt, args);
}

static int
chaz_ConfWriterC_sym_is_uppercase(const char *sym) {
    return isupper((unsigned char)sym[0]);
}

static char*
chaz_ConfWriterC_uppercase_string(const char *src) {
    char *retval = chaz_Util_strdup(src);
    size_t i;
    for (i = 0; retval[i]; ++i) {
        retval[i] = toupper((unsigned char)retval[i]);
    }
    return retval;
}

static void
chaz_ConfWriterC_add_def(const char *sym, const char *value) {
    chaz_ConfWriterC_push_def_list_item(sym, value, CHAZ_CONFELEM_DEF);
}

static void
chaz_ConfWriterC_append_def_to_conf(const char *sym, const char *value) {
    if (value) {
        if (chaz_ConfWriterC_sym_is_uppercase(sym)) {
            fprintf(chaz_ConfWriterC.fh, "#define CHY_%s %s\n", sym, value);
        }
        else {
            fprintf(chaz_ConfWriterC.fh, "#define chy_%s %s\n", sym, value);
        }
    }
    else {
        if (chaz_ConfWriterC_sym_is_uppercase(sym)) {
            fprintf(chaz_ConfWriterC.fh, "#define CHY_%s\n", sym);
        }
        else {
            fprintf(chaz_ConfWriterC.fh, "#define chy_%s\n", sym);
        }
    }
}

static void
chaz_ConfWriterC_add_global_def(const char *sym, const char *value) {
    chaz_ConfWriterC_push_def_list_item(sym, value, CHAZ_CONFELEM_GLOBAL_DEF);
}

static void
chaz_ConfWriterC_append_global_def_to_conf(const char *sym,
                                           const char *value) {
    char *name_end = strchr(sym, '(');
    if (name_end == NULL) {
        if (strcmp(sym, value) == 0) { return; }
        fprintf(chaz_ConfWriterC.fh, "#ifndef %s\n", sym);
    }
    else {
        size_t  name_len = (size_t)(name_end - sym);
        char   *name     = chaz_Util_strdup(sym);
        name[name_len] = '\0';
        fprintf(chaz_ConfWriterC.fh, "#ifndef %s\n", name);
        free(name);
    }
    if (value) {
        fprintf(chaz_ConfWriterC.fh, "  #define %s %s\n", sym, value);
    }
    else {
        fprintf(chaz_ConfWriterC.fh, "  #define %s\n", sym);
    }
    fprintf(chaz_ConfWriterC.fh, "#endif\n");
}

static void
chaz_ConfWriterC_add_typedef(const char *type, const char *alias) {
    chaz_ConfWriterC_push_def_list_item(alias, type, CHAZ_CONFELEM_TYPEDEF);
}

static void
chaz_ConfWriterC_append_typedef_to_conf(const char *type, const char *alias) {
    if (chaz_ConfWriterC_sym_is_uppercase(alias)) {
        fprintf(chaz_ConfWriterC.fh, "typedef %s CHY_%s;\n", type, alias);
    }
    else {
        fprintf(chaz_ConfWriterC.fh, "typedef %s chy_%s;\n", type, alias);
    }
}

static void
chaz_ConfWriterC_add_global_typedef(const char *type, const char *alias) {
    chaz_ConfWriterC_push_def_list_item(alias, type,
            CHAZ_CONFELEM_GLOBAL_TYPEDEF);
}

static void
chaz_ConfWriterC_append_global_typedef_to_conf(const char *type,
                                               const char *alias) {
    if (strcmp(type, alias) == 0) { return; }
    fprintf(chaz_ConfWriterC.fh, "typedef %s %s;\n", type, alias);
}

static void
chaz_ConfWriterC_add_sys_include(const char *header) {
    chaz_ConfWriterC_push_def_list_item(header, NULL,
                                        CHAZ_CONFELEM_SYS_INCLUDE);
}

static void
chaz_ConfWriterC_append_sys_include_to_conf(const char *header) {
    fprintf(chaz_ConfWriterC.fh, "#include <%s>\n", header);
}

static void
chaz_ConfWriterC_add_local_include(const char *header) {
    chaz_ConfWriterC_push_def_list_item(header, NULL,
                                        CHAZ_CONFELEM_LOCAL_INCLUDE);
}

static void
chaz_ConfWriterC_append_local_include_to_conf(const char *header) {
    fprintf(chaz_ConfWriterC.fh, "#include \"%s\"\n", header);
}

static void
chaz_ConfWriterC_start_module(const char *module_name) {
    fprintf(chaz_ConfWriterC.fh, "\n/* %s */\n", module_name);
    chaz_ConfWriterC.MODULE_NAME
        = chaz_ConfWriterC_uppercase_string(module_name);
}

static void
chaz_ConfWriterC_end_module(void) {
    size_t num_globals = 0;
    size_t i;
    chaz_ConfElem *defs = chaz_ConfWriterC.defs;
    for (i = 0; i < chaz_ConfWriterC.def_count; i++) {
        switch (defs[i].type) {
            case CHAZ_CONFELEM_GLOBAL_DEF:
                ++num_globals;
            /* fall through */
            case CHAZ_CONFELEM_DEF:
                chaz_ConfWriterC_append_def_to_conf(defs[i].str1,
                                                    defs[i].str2);
                break;
            case CHAZ_CONFELEM_GLOBAL_TYPEDEF: {
                char *sym = chaz_ConfWriterC_uppercase_string(defs[i].str1);
                chaz_ConfWriterC_append_def_to_conf(sym, defs[i].str2);
                free(sym);
                ++num_globals;
            }
            /* fall through */
            case CHAZ_CONFELEM_TYPEDEF:
                chaz_ConfWriterC_append_typedef_to_conf(defs[i].str2,
                                                        defs[i].str1);
                break;
            case CHAZ_CONFELEM_SYS_INCLUDE:
                ++num_globals;
                break;
            case CHAZ_CONFELEM_LOCAL_INCLUDE:
                chaz_ConfWriterC_append_local_include_to_conf(defs[i].str1);
                break;
            default:
                chaz_Util_die("Internal error: bad element type %d",
                              (int)defs[i].type);
        }
    }

    /* Write out short names. */
    if (chaz_ConfWriterC.def_count > 0) {
        fprintf(chaz_ConfWriterC.fh,
            "\n#if defined(CHY_USE_SHORT_NAMES) "
            "|| defined(CHAZ_USE_SHORT_NAMES)\n"
        );
        for (i = 0; i < chaz_ConfWriterC.def_count; i++) {
            switch (defs[i].type) {
                case CHAZ_CONFELEM_DEF:
                case CHAZ_CONFELEM_TYPEDEF:
                    {
                        const char *sym = defs[i].str1;
                        const char *value = defs[i].str2;
                        if (!value || strcmp(sym, value) != 0) {
                            const char *prefix
                                = chaz_ConfWriterC_sym_is_uppercase(sym)
                                  ? "CHY_" : "chy_";
                            fprintf(chaz_ConfWriterC.fh, "  #define %s %s%s\n",
                                    sym, prefix, sym);
                        }
                    }
                    break;
                case CHAZ_CONFELEM_GLOBAL_DEF:
                case CHAZ_CONFELEM_GLOBAL_TYPEDEF:
                case CHAZ_CONFELEM_SYS_INCLUDE:
                case CHAZ_CONFELEM_LOCAL_INCLUDE:
                    /* no-op */
                    break;
                default:
                    chaz_Util_die("Internal error: bad element type %d",
                                  (int)defs[i].type);
            }
        }

        fprintf(chaz_ConfWriterC.fh, "#endif /* USE_SHORT_NAMES */\n");
    }

    /* Write out global definitions and system includes. */
    if (num_globals) {
        fprintf(chaz_ConfWriterC.fh, "\n#ifdef CHY_EMPLOY_%s\n\n",
                chaz_ConfWriterC.MODULE_NAME);
        for (i = 0; i < chaz_ConfWriterC.def_count; i++) {
            switch (defs[i].type) {
                case CHAZ_CONFELEM_GLOBAL_DEF:
                    chaz_ConfWriterC_append_global_def_to_conf(defs[i].str1,
                                                               defs[i].str2);
                    break;
                case CHAZ_CONFELEM_GLOBAL_TYPEDEF:
                    chaz_ConfWriterC_append_global_typedef_to_conf(
                            defs[i].str2, defs[i].str1);
                    break;
                case CHAZ_CONFELEM_SYS_INCLUDE:
                    chaz_ConfWriterC_append_sys_include_to_conf(defs[i].str1);
                    break;
                case CHAZ_CONFELEM_DEF:
                case CHAZ_CONFELEM_TYPEDEF:
                case CHAZ_CONFELEM_LOCAL_INCLUDE:
                    /* no-op */
                    break;
                default:
                    chaz_Util_die("Internal error: bad element type %d",
                                  (int)defs[i].type);
            }
        }
        fprintf(chaz_ConfWriterC.fh, "\n#endif /* EMPLOY_%s */\n",
                chaz_ConfWriterC.MODULE_NAME);
    }

    fprintf(chaz_ConfWriterC.fh, "\n");

    free(chaz_ConfWriterC.MODULE_NAME);
    chaz_ConfWriterC_clear_def_list();
}

static void
chaz_ConfWriterC_push_def_list_item(const char *str1, const char *str2,
                     chaz_ConfElemType type) {
    if (chaz_ConfWriterC.def_count >= chaz_ConfWriterC.def_cap) { 
        size_t amount;
        chaz_ConfWriterC.def_cap += 10;
        amount = chaz_ConfWriterC.def_cap * sizeof(chaz_ConfElem);
        chaz_ConfWriterC.defs
            = (chaz_ConfElem*)realloc(chaz_ConfWriterC.defs, amount);
    }
    chaz_ConfWriterC.defs[chaz_ConfWriterC.def_count].str1
        = str1 ? chaz_Util_strdup(str1) : NULL;
    chaz_ConfWriterC.defs[chaz_ConfWriterC.def_count].str2
        = str2 ? chaz_Util_strdup(str2) : NULL;
    chaz_ConfWriterC.defs[chaz_ConfWriterC.def_count].type = type;
    chaz_ConfWriterC.def_count++;
}

static void
chaz_ConfWriterC_clear_def_list(void) {
    size_t i;
    for (i = 0; i < chaz_ConfWriterC.def_count; i++) {
        free(chaz_ConfWriterC.defs[i].str1);
        free(chaz_ConfWriterC.defs[i].str2);
    }
    free(chaz_ConfWriterC.defs);
    chaz_ConfWriterC.defs      = NULL;
    chaz_ConfWriterC.def_cap   = 0;
    chaz_ConfWriterC.def_count = 0;
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/ConfWriterPerl.c"
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/ConfWriterPerl.h" */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Static vars. */
static struct {
    FILE *fh;
} chaz_CWPerl = { NULL };
static chaz_ConfWriter CWPerl_conf_writer;

/* Open the Charmony.pm file handle.
 */
static void
chaz_ConfWriterPerl_open_config_pm(void);

static void
chaz_ConfWriterPerl_clean_up(void);
static void
chaz_ConfWriterPerl_vappend_conf(const char *fmt, va_list args);
static void
chaz_ConfWriterPerl_add_def(const char *sym, const char *value);
static void
chaz_ConfWriterPerl_add_global_def(const char *sym, const char *value);
static void
chaz_ConfWriterPerl_add_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterPerl_add_global_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterPerl_add_sys_include(const char *header);
static void
chaz_ConfWriterPerl_add_local_include(const char *header);
static void
chaz_ConfWriterPerl_start_module(const char *module_name);
static void
chaz_ConfWriterPerl_end_module(void);

void
chaz_ConfWriterPerl_enable(void) {
    CWPerl_conf_writer.clean_up           = chaz_ConfWriterPerl_clean_up;
    CWPerl_conf_writer.vappend_conf       = chaz_ConfWriterPerl_vappend_conf;
    CWPerl_conf_writer.add_def            = chaz_ConfWriterPerl_add_def;
    CWPerl_conf_writer.add_global_def     = chaz_ConfWriterPerl_add_global_def;
    CWPerl_conf_writer.add_typedef        = chaz_ConfWriterPerl_add_typedef;
    CWPerl_conf_writer.add_global_typedef = chaz_ConfWriterPerl_add_global_typedef;
    CWPerl_conf_writer.add_sys_include    = chaz_ConfWriterPerl_add_sys_include;
    CWPerl_conf_writer.add_local_include  = chaz_ConfWriterPerl_add_local_include;
    CWPerl_conf_writer.start_module       = chaz_ConfWriterPerl_start_module;
    CWPerl_conf_writer.end_module         = chaz_ConfWriterPerl_end_module;
    chaz_ConfWriterPerl_open_config_pm();
    chaz_ConfWriter_add_writer(&CWPerl_conf_writer);
    return;
}

static void
chaz_ConfWriterPerl_open_config_pm(void) {
    /* Open the filehandle. */
    chaz_CWPerl.fh = fopen("Charmony.pm", "w+");
    if (chaz_CWPerl.fh == NULL) {
        chaz_Util_die("Can't open 'Charmony.pm': %s", strerror(errno));
    }

    /* Start the module. */
    fprintf(chaz_CWPerl.fh,
            "# Auto-generated by Charmonizer. \n"
            "# DO NOT EDIT THIS FILE!!\n"
            "\n"
            "package Charmony;\n"
            "use strict;\n"
            "use warnings;\n"
            "\n"
            "my %%defs;\n"
            "\n"
            "sub config { \\%%defs }\n"
            "\n"
           );
}

static void
chaz_ConfWriterPerl_clean_up(void) {
    /* Write the last bit of Charmony.pm and close. */
    fprintf(chaz_CWPerl.fh, "\n1;\n\n");
    if (fclose(chaz_CWPerl.fh)) {
        chaz_Util_die("Couldn't close 'Charmony.pm': %s", strerror(errno));
    }
}

static void
chaz_ConfWriterPerl_vappend_conf(const char *fmt, va_list args) {
    (void)fmt;
    (void)args;
}

static char*
chaz_ConfWriterPerl_quotify(const char *string, char *buf, size_t buf_size) {
    char *quoted = buf;

    /* Don't bother with undef values here. */
    if (!string) {
        return NULL;
    }

    /* Allocate memory if necessary. */
    {
        const char *ptr;
        size_t space = 3; /* Quotes plus NUL termination. */
        for (ptr = string; *ptr; ptr++) {
            if (*ptr == '\'' || *ptr == '\\') {
                space += 2;
            }
            else {
                space += 1;
            }
        }
        if (space > buf_size) {
            quoted = (char*)malloc(space);
        }
    }

    /* Perform copying and escaping */
    {
        const char *ptr;
        size_t pos = 0;
        quoted[pos++] = '\'';
        for (ptr = string; *ptr; ptr++) {
            if (*ptr == '\'' || *ptr == '\\') {
                quoted[pos++] = '\\';
            }
            quoted[pos++] = *ptr;
        }
        quoted[pos++] = '\'';
        quoted[pos++] = '\0';
    }

    return quoted;
}

#define CFPERL_MAX_BUF 100
static void
chaz_ConfWriterPerl_add_def(const char *sym, const char *value) {
    char sym_buf[CFPERL_MAX_BUF + 1];
    char value_buf[CFPERL_MAX_BUF + 1];
    char *quoted_sym;
    char *quoted_value;

    /* Quote key. */
    if (!sym) {
        chaz_Util_die("Can't handle NULL key");
    }
    quoted_sym = chaz_ConfWriterPerl_quotify(sym, sym_buf, CFPERL_MAX_BUF);

    /* Quote value or use "undef". */
    if (!value) {
        strcpy(value_buf, "undef");
        quoted_value = value_buf;
    }
    else {
        quoted_value = chaz_ConfWriterPerl_quotify(value, value_buf,
                                                CFPERL_MAX_BUF);
    }

    fprintf(chaz_CWPerl.fh, "$defs{%s} = %s;\n", quoted_sym, quoted_value);

    if (quoted_sym   != sym_buf)   { free(quoted_sym);   }
    if (quoted_value != value_buf) { free(quoted_value); }
}

static void
chaz_ConfWriterPerl_add_global_def(const char *sym, const char *value) {
    (void)sym;
    (void)value;
}

static void
chaz_ConfWriterPerl_add_typedef(const char *type, const char *alias) {
    (void)type;
    (void)alias;
}

static void
chaz_ConfWriterPerl_add_global_typedef(const char *type, const char *alias) {
    (void)type;
    (void)alias;
}

static void
chaz_ConfWriterPerl_add_sys_include(const char *header) {
    (void)header;
}

static void
chaz_ConfWriterPerl_add_local_include(const char *header) {
    (void)header;
}

static void
chaz_ConfWriterPerl_start_module(const char *module_name) {
    fprintf(chaz_CWPerl.fh, "# %s\n", module_name);
}

static void
chaz_ConfWriterPerl_end_module(void) {
    fprintf(chaz_CWPerl.fh, "\n");
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/ConfWriterPython.c"
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/ConfWriterPython.h" */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Static vars. */
static struct {
    FILE *fh;
} chaz_CWPython = { NULL };
static chaz_ConfWriter CWPython_conf_writer;

/* Open the charmony.py file handle.
 */
static void
chaz_ConfWriterPython_open_config_py(void);

static void
chaz_ConfWriterPython_clean_up(void);
static void
chaz_ConfWriterPython_vappend_conf(const char *fmt, va_list args);
static void
chaz_ConfWriterPython_add_def(const char *sym, const char *value);
static void
chaz_ConfWriterPython_add_global_def(const char *sym, const char *value);
static void
chaz_ConfWriterPython_add_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterPython_add_global_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterPython_add_sys_include(const char *header);
static void
chaz_ConfWriterPython_add_local_include(const char *header);
static void
chaz_ConfWriterPython_start_module(const char *module_name);
static void
chaz_ConfWriterPython_end_module(void);

void
chaz_ConfWriterPython_enable(void) {
    CWPython_conf_writer.clean_up           = chaz_ConfWriterPython_clean_up;
    CWPython_conf_writer.vappend_conf       = chaz_ConfWriterPython_vappend_conf;
    CWPython_conf_writer.add_def            = chaz_ConfWriterPython_add_def;
    CWPython_conf_writer.add_global_def     = chaz_ConfWriterPython_add_global_def;
    CWPython_conf_writer.add_typedef        = chaz_ConfWriterPython_add_typedef;
    CWPython_conf_writer.add_global_typedef = chaz_ConfWriterPython_add_global_typedef;
    CWPython_conf_writer.add_sys_include    = chaz_ConfWriterPython_add_sys_include;
    CWPython_conf_writer.add_local_include  = chaz_ConfWriterPython_add_local_include;
    CWPython_conf_writer.start_module       = chaz_ConfWriterPython_start_module;
    CWPython_conf_writer.end_module         = chaz_ConfWriterPython_end_module;
    chaz_ConfWriterPython_open_config_py();
    chaz_ConfWriter_add_writer(&CWPython_conf_writer);
    return;
}

static void
chaz_ConfWriterPython_open_config_py(void) {
    /* Open the filehandle. */
    chaz_CWPython.fh = fopen("charmony.py", "w+");
    if (chaz_CWPython.fh == NULL) {
        chaz_Util_die("Can't open 'charmony.py': %s", strerror(errno));
    }

    /* Start the module. */
    fprintf(chaz_CWPython.fh,
            "# Auto-generated by Charmonizer. \n"
            "# DO NOT EDIT THIS FILE!!\n"
            "\n"
            "class Charmony(object):\n"
            "    @classmethod\n"
            "    def config(cls):\n"
            "        return cls.defs\n"
            "\n"
            "    defs = {}\n"
            "\n"
           );
}

static void
chaz_ConfWriterPython_clean_up(void) {
    /* No more code necessary to finish charmony.py, so just close. */
    if (fclose(chaz_CWPython.fh)) {
        chaz_Util_die("Couldn't close 'charmony.py': %s", strerror(errno));
    }
}

static void
chaz_ConfWriterPython_vappend_conf(const char *fmt, va_list args) {
    (void)fmt;
    (void)args;
}

static char*
chaz_ConfWriterPython_quotify(const char *string, char *buf, size_t buf_size) {
    char *quoted = buf;

    /* Don't bother with NULL values here. */
    if (!string) {
        return NULL;
    }

    /* Allocate memory if necessary. */
    {
        const char *ptr;
        size_t space = 3; /* Quotes plus NUL termination. */
        for (ptr = string; *ptr; ptr++) {
            if (*ptr == '\'' || *ptr == '\\') {
                space += 2;
            }
            else {
                space += 1;
            }
        }
        if (space > buf_size) {
            quoted = (char*)malloc(space);
        }
    }

    /* Perform copying and escaping */
    {
        const char *ptr;
        size_t pos = 0;
        quoted[pos++] = '\'';
        for (ptr = string; *ptr; ptr++) {
            if (*ptr == '\'' || *ptr == '\\') {
                quoted[pos++] = '\\';
            }
            quoted[pos++] = *ptr;
        }
        quoted[pos++] = '\'';
        quoted[pos++] = '\0';
    }

    return quoted;
}

#define CFPYTHON_MAX_BUF 100
static void
chaz_ConfWriterPython_add_def(const char *sym, const char *value) {
    char sym_buf[CFPYTHON_MAX_BUF + 1];
    char value_buf[CFPYTHON_MAX_BUF + 1];
    char *quoted_sym;
    char *quoted_value;

    /* Quote key. */
    if (!sym) {
        chaz_Util_die("Can't handle NULL key");
    }
    quoted_sym = chaz_ConfWriterPython_quotify(sym, sym_buf, CFPYTHON_MAX_BUF);

    /* Quote value or use "None". */
    if (!value) {
        strcpy(value_buf, "None");
        quoted_value = value_buf;
    }
    else {
        quoted_value = chaz_ConfWriterPython_quotify(value, value_buf,
                                                     CFPYTHON_MAX_BUF);
    }

    fprintf(chaz_CWPython.fh, "    defs[%s] = %s\n", quoted_sym, quoted_value);

    if (quoted_sym   != sym_buf)   { free(quoted_sym);   }
    if (quoted_value != value_buf) { free(quoted_value); }
}

static void
chaz_ConfWriterPython_add_global_def(const char *sym, const char *value) {
    (void)sym;
    (void)value;
}

static void
chaz_ConfWriterPython_add_typedef(const char *type, const char *alias) {
    (void)type;
    (void)alias;
}

static void
chaz_ConfWriterPython_add_global_typedef(const char *type, const char *alias) {
    (void)type;
    (void)alias;
}

static void
chaz_ConfWriterPython_add_sys_include(const char *header) {
    (void)header;
}

static void
chaz_ConfWriterPython_add_local_include(const char *header) {
    (void)header;
}

static void
chaz_ConfWriterPython_start_module(const char *module_name) {
    fprintf(chaz_CWPython.fh, "    # %s\n", module_name);
}

static void
chaz_ConfWriterPython_end_module(void) {
    fprintf(chaz_CWPython.fh, "\n");
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/ConfWriterRuby.c"
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/ConfWriterRuby.h" */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Static vars. */
static struct {
    FILE *fh;
} chaz_CWRuby = { NULL };
static chaz_ConfWriter CWRuby_conf_writer;

/* Open the Charmony.rb file handle.
 */
static void
chaz_ConfWriterRuby_open_config_rb(void);

static void
chaz_ConfWriterRuby_clean_up(void);
static void
chaz_ConfWriterRuby_vappend_conf(const char *fmt, va_list args);
static void
chaz_ConfWriterRuby_add_def(const char *sym, const char *value);
static void
chaz_ConfWriterRuby_add_global_def(const char *sym, const char *value);
static void
chaz_ConfWriterRuby_add_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterRuby_add_global_typedef(const char *type, const char *alias);
static void
chaz_ConfWriterRuby_add_sys_include(const char *header);
static void
chaz_ConfWriterRuby_add_local_include(const char *header);
static void
chaz_ConfWriterRuby_start_module(const char *module_name);
static void
chaz_ConfWriterRuby_end_module(void);

void
chaz_ConfWriterRuby_enable(void) {
    CWRuby_conf_writer.clean_up           = chaz_ConfWriterRuby_clean_up;
    CWRuby_conf_writer.vappend_conf       = chaz_ConfWriterRuby_vappend_conf;
    CWRuby_conf_writer.add_def            = chaz_ConfWriterRuby_add_def;
    CWRuby_conf_writer.add_global_def     = chaz_ConfWriterRuby_add_global_def;
    CWRuby_conf_writer.add_typedef        = chaz_ConfWriterRuby_add_typedef;
    CWRuby_conf_writer.add_global_typedef = chaz_ConfWriterRuby_add_global_typedef;
    CWRuby_conf_writer.add_sys_include    = chaz_ConfWriterRuby_add_sys_include;
    CWRuby_conf_writer.add_local_include  = chaz_ConfWriterRuby_add_local_include;
    CWRuby_conf_writer.start_module       = chaz_ConfWriterRuby_start_module;
    CWRuby_conf_writer.end_module         = chaz_ConfWriterRuby_end_module;
    chaz_ConfWriterRuby_open_config_rb();
    chaz_ConfWriter_add_writer(&CWRuby_conf_writer);
    return;
}

static void
chaz_ConfWriterRuby_open_config_rb(void) {
    /* Open the filehandle. */
    chaz_CWRuby.fh = fopen("Charmony.rb", "w+");
    if (chaz_CWRuby.fh == NULL) {
        chaz_Util_die("Can't open 'Charmony.rb': %s", strerror(errno));
    }

    /* Start the module. */
    fprintf(chaz_CWRuby.fh,
            "# Auto-generated by Charmonizer. \n"
            "# DO NOT EDIT THIS FILE!!\n"
            "\n"
            "module Charmony\n"
            "\n"
            "defs = {}\n"
            "\n"
            "def config\ndefs\nend\n"
            "\n"
           );
}

static void
chaz_ConfWriterRuby_clean_up(void) {
    /* Write the last bit of Charmony.rb and close. */
    fprintf(chaz_CWRuby.fh, "\nend\n\n");
    if (fclose(chaz_CWRuby.fh)) {
        chaz_Util_die("Couldn't close 'Charmony.rb': %s", strerror(errno));
    }
}

static void
chaz_ConfWriterRuby_vappend_conf(const char *fmt, va_list args) {
    (void)fmt;
    (void)args;
}

static char*
chaz_ConfWriterRuby_quotify(const char *string, char *buf, size_t buf_size) {
    char *quoted = buf;

    /* Don't bother with undef values here. */
    if (!string) {
        return NULL;
    }

    /* Allocate memory if necessary. */
    {
        const char *ptr;
        size_t space = 3; /* Quotes plus NUL termination. */
        for (ptr = string; *ptr; ptr++) {
            if (*ptr == '\'' || *ptr == '\\') {
                space += 2;
            }
            else {
                space += 1;
            }
        }
        if (space > buf_size) {
            quoted = (char*)malloc(space);
        }
    }

    /* Perform copying and escaping */
    {
        const char *ptr;
        size_t pos = 0;
        quoted[pos++] = '\'';
        for (ptr = string; *ptr; ptr++) {
            if (*ptr == '\'' || *ptr == '\\') {
                quoted[pos++] = '\\';
            }
            quoted[pos++] = *ptr;
        }
        quoted[pos++] = '\'';
        quoted[pos++] = '\0';
    }

    return quoted;
}

#define CFRUBY_MAX_BUF 100
static void
chaz_ConfWriterRuby_add_def(const char *sym, const char *value) {
    char sym_buf[CFRUBY_MAX_BUF + 1];
    char value_buf[CFRUBY_MAX_BUF + 1];
    char *quoted_sym;
    char *quoted_value;

    /* Quote key. */
    if (!sym) {
        chaz_Util_die("Can't handle NULL key");
    }
    quoted_sym = chaz_ConfWriterRuby_quotify(sym, sym_buf, CFRUBY_MAX_BUF);

    /* Quote value or use "nil". */
    if (!value) {
        strcpy(value_buf, "nil");
        quoted_value = value_buf;
    }
    else {
        quoted_value = chaz_ConfWriterRuby_quotify(value, value_buf,
                                                CFRUBY_MAX_BUF);
    }

    fprintf(chaz_CWRuby.fh, "defs[%s] = %s\n", quoted_sym, quoted_value);

    if (quoted_sym   != sym_buf)   { free(quoted_sym);   }
    if (quoted_value != value_buf) { free(quoted_value); }
}

static void
chaz_ConfWriterRuby_add_global_def(const char *sym, const char *value) {
    (void)sym;
    (void)value;
}

static void
chaz_ConfWriterRuby_add_typedef(const char *type, const char *alias) {
    (void)type;
    (void)alias;
}

static void
chaz_ConfWriterRuby_add_global_typedef(const char *type, const char *alias) {
    (void)type;
    (void)alias;
}

static void
chaz_ConfWriterRuby_add_sys_include(const char *header) {
    (void)header;
}

static void
chaz_ConfWriterRuby_add_local_include(const char *header) {
    (void)header;
}

static void
chaz_ConfWriterRuby_start_module(const char *module_name) {
    fprintf(chaz_CWRuby.fh, "# %s\n", module_name);
}

static void
chaz_ConfWriterRuby_end_module(void) {
    fprintf(chaz_CWRuby.fh, "\n");
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/HeaderChecker.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
#include <string.h>
#include <stdlib.h>

typedef struct chaz_CHeader {
    const char  *name;
    int          exists;
} chaz_CHeader;

/* Keep a sorted, dynamically-sized array of names of all headers we've
 * checked for so far.
 */
static struct {
    int            cache_size;
    chaz_CHeader **header_cache;
} chaz_HeadCheck = { 0, NULL };

/* Comparison function to feed to qsort, bsearch, etc.
 */
static int
chaz_HeadCheck_compare_headers(const void *vptr_a, const void *vptr_b);

/* Run a test compilation and return a new chaz_CHeader object encapsulating
 * the results.
 */
static chaz_CHeader*
chaz_HeadCheck_discover_header(const char *header_name);

/* Extend the cache, add this chaz_CHeader object to it, and sort.
 */
static void
chaz_HeadCheck_add_to_cache(chaz_CHeader *header);

/* Like add_to_cache, but takes a individual elements instead of a
 * chaz_CHeader* and checks if header exists in array first.
 */
static void
chaz_HeadCheck_maybe_add_to_cache(const char *header_name, int exists);

void
chaz_HeadCheck_init(void) {
    chaz_CHeader *null_header = (chaz_CHeader*)malloc(sizeof(chaz_CHeader));

    /* Create terminating record for the dynamic array of chaz_CHeader
     * objects. */
    null_header->name   = NULL;
    null_header->exists = false;
    chaz_HeadCheck.header_cache    = (chaz_CHeader**)malloc(sizeof(void*));
    *(chaz_HeadCheck.header_cache) = null_header;
    chaz_HeadCheck.cache_size = 1;
}

int
chaz_HeadCheck_check_header(const char *header_name) {
    chaz_CHeader  *header;
    chaz_CHeader   key;
    chaz_CHeader  *fake = &key;
    chaz_CHeader **header_ptr;

    /* Fake up a key to feed to bsearch; see if the header's already there. */
    key.name = header_name;
    key.exists = false;
    header_ptr = (chaz_CHeader**)bsearch(&fake, chaz_HeadCheck.header_cache,
                                         chaz_HeadCheck.cache_size,
                                         sizeof(void*),
                                         chaz_HeadCheck_compare_headers);

    /* If it's not there, go try a test compile. */
    if (header_ptr == NULL) {
        header = chaz_HeadCheck_discover_header(header_name);
        chaz_HeadCheck_add_to_cache(header);
    }
    else {
        header = *header_ptr;
    }

    return header->exists;
}

int
chaz_HeadCheck_check_many_headers(const char **header_names) {
    static const char test_code[] = "int main() { return 0; }\n";
    int success;
    int i;
    char *code_buf;
    size_t needed = sizeof(test_code) + 20;

    /* Build the source code string. */
    for (i = 0; header_names[i] != NULL; i++) {
        needed += strlen(header_names[i]);
        needed += sizeof("#include <>\n");
    }
    code_buf = (char*)malloc(needed);
    code_buf[0] = '\0';
    for (i = 0; header_names[i] != NULL; i++) {
        strcat(code_buf, "#include <");
        strcat(code_buf, header_names[i]);
        strcat(code_buf, ">\n");
    }
    strcat(code_buf, test_code);

    /* If the code compiles, bulk add all header names to the cache. */
    success = chaz_CC_test_compile(code_buf);
    if (success) {
        for (i = 0; header_names[i] != NULL; i++) {
            chaz_HeadCheck_maybe_add_to_cache(header_names[i], true);
        }
    }

    free(code_buf);
    return success;
}

int
chaz_HeadCheck_defines_symbol(const char *symbol, const char *includes) {
    static const char defines_code[] =
        CHAZ_QUOTE(  %s                                            )
        CHAZ_QUOTE(  int main() {                                  )
        CHAZ_QUOTE(  #ifdef %s                                     )
        CHAZ_QUOTE(      return 0;                                 )
        CHAZ_QUOTE(  #else                                         )
        CHAZ_QUOTE(      return (int)&%s;                          )
        CHAZ_QUOTE(  #endif                                        )
        CHAZ_QUOTE(  }                                             );
    long needed = sizeof(defines_code)
                  + 2 * strlen(symbol)
                  + strlen(includes)
                  + 10;
    char *buf = (char*)malloc(needed);
    int retval;
    sprintf(buf, defines_code, includes, symbol, symbol);
    retval = chaz_CC_test_compile(buf);
    free(buf);
    return retval;
}

int
chaz_HeadCheck_contains_member(const char *struct_name, const char *member,
                               const char *includes) {
    static const char contains_code[] =
        CHAZ_QUOTE(  #include <stddef.h>                           )
        CHAZ_QUOTE(  %s                                            )
        CHAZ_QUOTE(  int main() { return offsetof(%s, %s); }       );
    long needed = sizeof(contains_code)
                  + strlen(struct_name)
                  + strlen(member)
                  + strlen(includes)
                  + 10;
    char *buf = (char*)malloc(needed);
    int retval;
    sprintf(buf, contains_code, includes, struct_name, member);
    retval = chaz_CC_test_compile(buf);
    free(buf);
    return retval;
}

int
chaz_HeadCheck_size_of_type(const char *type, const char *includes, int hint) {
    static const char sizeof_code[] =
        CHAZ_QUOTE(  #include <stddef.h>                           )
        CHAZ_QUOTE(  %s                                            )
        CHAZ_QUOTE(  int a[sizeof(%s)==%d?1:-1];                   );
    size_t needed = sizeof(sizeof_code)
                    + strlen(type)
                    + strlen(includes)
                    + 10;
    char *buf = (char*)malloc(needed);
    static const int sizes[] = { 4, 8, 2, 1 };
    int retval = 0;
    int i;

    for (i = -1; i < (int)(sizeof(sizes) / sizeof(sizes[0])); i++) {
        int size;

        if (i < 0) {
            if (hint != 0) { size = hint; }
            else           { continue; }
        }
        else {
            if (sizes[i] != hint) { size = sizes[i]; }
            else                  { continue; }
        }

        sprintf(buf, sizeof_code, includes, type, size);
        if (chaz_CC_test_compile(buf)) {
            retval = size;
            break;
        }
    }

    free(buf);
    return retval;
}

static int
chaz_HeadCheck_compare_headers(const void *vptr_a, const void *vptr_b) {
    chaz_CHeader *const *const a = (chaz_CHeader*const*)vptr_a;
    chaz_CHeader *const *const b = (chaz_CHeader*const*)vptr_b;

    /* (NULL is "greater than" any string.) */
    if ((*a)->name == NULL)      { return 1; }
    else if ((*b)->name == NULL) { return -1; }
    else                         { return strcmp((*a)->name, (*b)->name); }
}

static chaz_CHeader*
chaz_HeadCheck_discover_header(const char *header_name) {
    static const char test_code[] = "int main() { return 0; }\n";
    chaz_CHeader* header = (chaz_CHeader*)malloc(sizeof(chaz_CHeader));
    size_t  needed = strlen(header_name) + sizeof(test_code) + 50;
    char *include_test = (char*)malloc(needed);

    /* Assign. */
    header->name = chaz_Util_strdup(header_name);

    /* See whether code that tries to pull in this header compiles. */
    sprintf(include_test, "#include <%s>\n%s", header_name, test_code);
    header->exists = chaz_CC_test_compile(include_test);

    free(include_test);
    return header;
}

static void
chaz_HeadCheck_add_to_cache(chaz_CHeader *header) {
    size_t amount;

    /* Realloc array -- inefficient, but this isn't a bottleneck. */
    amount = ++chaz_HeadCheck.cache_size * sizeof(void*);
    chaz_HeadCheck.header_cache
        = (chaz_CHeader**)realloc(chaz_HeadCheck.header_cache, amount);
    chaz_HeadCheck.header_cache[chaz_HeadCheck.cache_size - 1] = header;

    /* Keep the list of headers sorted. */
    qsort(chaz_HeadCheck.header_cache, chaz_HeadCheck.cache_size,
          sizeof(*(chaz_HeadCheck.header_cache)),
          chaz_HeadCheck_compare_headers);
}

static void
chaz_HeadCheck_maybe_add_to_cache(const char *header_name, int exists) {
    chaz_CHeader *header;
    chaz_CHeader  key;
    chaz_CHeader *fake = &key;

    /* Fake up a key and bsearch for it. */
    key.name   = header_name;
    key.exists = exists;
    header = (chaz_CHeader*)bsearch(&fake, chaz_HeadCheck.header_cache,
                                    chaz_HeadCheck.cache_size, sizeof(void*),
                                    chaz_HeadCheck_compare_headers);

    /* We've already done the test compile, so skip that step and add it. */
    if (header == NULL) {
        header = (chaz_CHeader*)malloc(sizeof(chaz_CHeader));
        header->name   = chaz_Util_strdup(header_name);
        header->exists = exists;
        chaz_HeadCheck_add_to_cache(header);
    }
}



/***************************************************************************/

#line 17 "src/Charmonizer/Core/Make.c"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* #include "Charmonizer/Core/Make.h" */
/* #include "Charmonizer/Core/CFlags.h" */
/* #include "Charmonizer/Core/CLI.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */
/* #include "Charmonizer/Core/Util.h" */

#define CHAZ_MAKEBINARY_EXE         1
#define CHAZ_MAKEBINARY_STATIC_LIB  2
#define CHAZ_MAKEBINARY_SHARED_LIB  3

struct chaz_MakeVar {
    char   *name;
    char   *value;
    size_t  num_elements;
};

struct chaz_MakeRule {
    char *targets;
    char *prereqs;
    char *commands;
};

struct chaz_MakeBinary {
    chaz_MakeRule  *rule;  /* Owned by MakeBinary. */

    chaz_MakeVar   *obj_var;
    char           *obj_dollar_var;
    char          **sources;  /* List of all sources. */
    size_t          num_sources;
    char          **single_sources;  /* Only sources from add_src_file. */
    size_t          num_single_sources;
    char          **dirs;
    size_t          num_dirs;

    chaz_MakeVar   *cflags_var;
    chaz_CFlags    *cflags;

    chaz_MakeVar   *ldflags_var;
    chaz_CFlags    *ldflags;
};

struct chaz_MakeFile {
    chaz_MakeVar    **vars;
    size_t            num_vars;
    chaz_MakeRule   **rules;
    size_t            num_rules;
    char            **install_dirs;
    size_t            num_install_dirs;
    chaz_MakeRule    *install;
    chaz_MakeRule    *clean;
    chaz_MakeRule    *distclean;
    chaz_MakeBinary **binaries;
    size_t            num_binaries;
};

typedef struct {
    chaz_MakeBinary         *binary;
    chaz_Make_file_filter_t  filter;
    void                    *filter_ctx;
} chaz_MakeBinaryContext;

/* Static vars. */
static struct {
    chaz_CLI *cli;
    char     *make_command;
    int       shell_type;
    int       supports_pattern_rules;
} chaz_Make = {
    NULL, NULL,
    0, 0
};

/* Detect make command.
 *
 * The argument list must be a NULL-terminated series of different spellings
 * of `make`, which will be auditioned in the order they are supplied.  Here
 * are several possibilities:
 *
 *      make
 *      gmake
 *      nmake
 *      dmake
 */
static int
S_chaz_Make_detect(const char *make1, ...);

static int
S_chaz_Make_audition(const char *make);

static chaz_MakeBinary*
S_chaz_MakeFile_add_binary(chaz_MakeFile *self, int type, const char *basename,
                           const char *target);

static void
S_chaz_MakeFile_add_install_dir(chaz_MakeFile *self, const char *dir);

static void
S_chaz_MakeFile_write_install_vars(FILE *out);

static void
S_chaz_MakeFile_write_binary_rules(chaz_MakeBinary *binary, FILE *out);

static void
S_chaz_MakeFile_write_object_rules(char **sources, const char *command,
                                   FILE *out);

static void
S_chaz_MakeFile_write_pattern_rules(char **dirs, const char *command,
                                    FILE *out);

static chaz_MakeRule*
S_chaz_MakeRule_new(const char *target, const char *prereq);

static void
S_chaz_MakeRule_destroy(chaz_MakeRule *self);

static void
S_chaz_MakeRule_write(chaz_MakeRule *self, FILE *out);

static void
S_chaz_MakeBinary_destroy(chaz_MakeBinary *self);

static void
S_chaz_MakeBinary_list_files_callback(const char *dir, char *file,
                                      void *context);
static void
S_chaz_MakeBinary_do_add_src_file(chaz_MakeBinary *self, const char *path);

/** Return the path to the object file for a source file.
 *
 * @param path The path to the source file.
 */
static char*
S_chaz_MakeBinary_obj_path(const char *src_path);

void
chaz_Make_init(chaz_CLI *cli) {
    const char *make_command = chaz_CLI_strval(cli, "make");

    chaz_Make.cli        = cli;
    chaz_Make.shell_type = chaz_OS_shell_type();

    if (make_command) {
        if (!S_chaz_Make_detect(make_command, NULL)) {
            chaz_Util_warn("Make utility '%s' doesn't appear to work",
                           make_command);
        }
    }
    else {
        int succeeded = 0;

        /* mingw32-make seems to try to run commands under both cmd.exe
         * and sh.exe. Not sure about dmake.
         */
        if (chaz_Make.shell_type == CHAZ_OS_POSIX) {
            succeeded = S_chaz_Make_detect("make", "gmake", "dmake",
                                           "mingw32-make", NULL);
        }
        else if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
            succeeded = S_chaz_Make_detect("nmake", "dmake", "mingw32-make",
                                           NULL);
        }

        if (!succeeded) {
            chaz_Util_warn("No working make utility found");
        }
        else if (chaz_Util_verbosity) {
            printf("Detected make utility '%s'\n", chaz_Make.make_command);
        }
    }
}

void
chaz_Make_clean_up(void) {
    free(chaz_Make.make_command);
}

const char*
chaz_Make_get_make(void) {
    return chaz_Make.make_command;
}

int
chaz_Make_shell_type(void) {
    return chaz_Make.shell_type;
}

static int
S_chaz_Make_detect(const char *make1, ...) {
    va_list args;
    const char *candidate;
    int found = 0;
    const char makefile_content[] =
        "foo:\n"
        "\t@echo 643490c943525d19\n"
        "\n"
        "%.ext:\n"
        "\t@echo 8f4ef20576b070d5\n";
    chaz_Util_write_file("_charm_Makefile", makefile_content);

    /* Audition candidates. */
    found = S_chaz_Make_audition(make1);
    va_start(args, make1);
    while (!found && (NULL != (candidate = va_arg(args, const char*)))) {
        found = S_chaz_Make_audition(candidate);
    }
    va_end(args);

    chaz_Util_remove_and_verify("_charm_Makefile");

    return found;
}

static int
S_chaz_Make_audition(const char *make) {
    int succeeded = 0;
    char *command = chaz_Util_join(" ", make, "-f", "_charm_Makefile", NULL);

    chaz_Util_remove_and_verify("_charm_foo");
    chaz_OS_run_redirected(command, "_charm_foo");
    if (chaz_Util_can_open_file("_charm_foo")) {
        size_t len;
        char *content = chaz_Util_slurp_file("_charm_foo", &len);
        if (content != NULL && strstr(content, "643490c943525d19") != NULL) {
            succeeded = 1;
        }
        free(content);
    }
    chaz_Util_remove_and_verify("_charm_foo");
    free(command);

    if (succeeded) {
        chaz_Make.make_command = chaz_Util_strdup(make);

        command = chaz_Util_join(" ", make, "-f", "_charm_Makefile", "foo.ext",
                                 NULL);
        chaz_OS_run_redirected(command, "_charm_foo");
        if (chaz_Util_can_open_file("_charm_foo")) {
            size_t len;
            char *content = chaz_Util_slurp_file("_charm_foo", &len);
            if (content != NULL
                && strstr(content, "8f4ef20576b070d5") != NULL
               ) {
                chaz_Make.supports_pattern_rules = 1;
            }
            free(content);
        }
        chaz_Util_remove_and_verify("_charm_foo");
        free(command);
    }

    return succeeded;
}

chaz_MakeFile*
chaz_MakeFile_new() {
    chaz_MakeFile *self = (chaz_MakeFile*)calloc(1, sizeof(chaz_MakeFile));
    char *generated;

    self->vars         = (chaz_MakeVar**)calloc(1, sizeof(chaz_MakeVar*));
    self->rules        = (chaz_MakeRule**)calloc(1, sizeof(chaz_MakeRule*));
    self->install_dirs = (char**)calloc(1, sizeof(char*));

    self->install   = S_chaz_MakeRule_new("install", "all");
    self->clean     = S_chaz_MakeRule_new("clean", NULL);
    self->distclean = S_chaz_MakeRule_new("distclean", "clean");

    self->binaries = (chaz_MakeBinary**)calloc(1, sizeof(chaz_MakeBinary*));

    /* MSVC leaves .obj files around when creating executables. */
    generated = chaz_Util_join("", "charmonizer", chaz_OS_exe_ext(),
                               " charmonizer.obj charmony.h Makefile", NULL);
    chaz_MakeRule_add_rm_command(self->distclean, generated);

    free(generated);
    return self;
}

void
chaz_MakeFile_destroy(chaz_MakeFile *self) {
    size_t i;

    for (i = 0; self->vars[i]; i++) {
        chaz_MakeVar *var = self->vars[i];
        free(var->name);
        free(var->value);
        free(var);
    }
    free(self->vars);

    for (i = 0; self->rules[i]; i++) {
        S_chaz_MakeRule_destroy(self->rules[i]);
    }
    free(self->rules);

    for (i = 0; self->install_dirs[i]; i++) {
        free(self->install_dirs[i]);
    }
    free(self->install_dirs);

    for (i = 0; self->binaries[i]; i++) {
        S_chaz_MakeBinary_destroy(self->binaries[i]);
    }
    free(self->binaries);

    S_chaz_MakeRule_destroy(self->install);
    S_chaz_MakeRule_destroy(self->clean);
    S_chaz_MakeRule_destroy(self->distclean);

    free(self);
}

chaz_MakeVar*
chaz_MakeFile_add_var(chaz_MakeFile *self, const char *name,
                      const char *value) {
    chaz_MakeVar  *var      = (chaz_MakeVar*)malloc(sizeof(chaz_MakeVar));
    chaz_MakeVar **vars     = self->vars;
    size_t         num_vars = self->num_vars + 1;

    var->name         = chaz_Util_strdup(name);
    var->value        = chaz_Util_strdup("");
    var->num_elements = 0;

    if (value) { chaz_MakeVar_append(var, value); }

    vars = (chaz_MakeVar**)realloc(vars,
                                   (num_vars + 1) * sizeof(chaz_MakeVar*));
    vars[num_vars-1] = var;
    vars[num_vars]   = NULL;
    self->vars = vars;
    self->num_vars = num_vars;

    return var;
}

chaz_MakeRule*
chaz_MakeFile_add_rule(chaz_MakeFile *self, const char *target,
                       const char *prereq) {
    chaz_MakeRule  *rule      = S_chaz_MakeRule_new(target, prereq);
    chaz_MakeRule **rules     = self->rules;
    size_t          num_rules = self->num_rules + 1;

    rules = (chaz_MakeRule**)realloc(rules,
                                     (num_rules + 1) * sizeof(chaz_MakeRule*));
    rules[num_rules-1] = rule;
    rules[num_rules]   = NULL;
    self->rules = rules;
    self->num_rules = num_rules;

    return rule;
}

chaz_MakeRule*
chaz_MakeFile_install_rule(chaz_MakeFile *self) {
    return self->install;
}

chaz_MakeRule*
chaz_MakeFile_clean_rule(chaz_MakeFile *self) {
    return self->clean;
}

chaz_MakeRule*
chaz_MakeFile_distclean_rule(chaz_MakeFile *self) {
    return self->distclean;
}

chaz_MakeBinary*
chaz_MakeFile_add_exe(chaz_MakeFile *self, const char *dir,
                      const char *basename, int installed) {
    const char *exe_ext = chaz_CC_exe_ext();
    char *target;
    char *command;
    chaz_MakeBinary *binary;
    chaz_CFlags *ldflags;

    if (dir == NULL || strcmp(dir, ".") == 0) {
        target = chaz_Util_join("", basename, exe_ext, NULL);
    }
    else {
        const char *dir_sep = chaz_OS_dir_sep();
        target = chaz_Util_join("", dir, dir_sep, basename, exe_ext, NULL);
    }

    binary = S_chaz_MakeFile_add_binary(self, CHAZ_MAKEBINARY_EXE, basename,
                                        target);

    ldflags = chaz_CC_new_cflags();
    if (chaz_CC_is_msvc()) {
        chaz_CFlags_append(ldflags, "/nologo");
    }
    chaz_CFlags_set_link_output(ldflags, "$@");

    /* Objects must come before flags since flags may contain libraries. */
    command = chaz_Util_join("", "$(LINK) ", chaz_CFlags_get_string(ldflags),
                             " ", binary->obj_dollar_var,
                             " $(", binary->ldflags_var->name, ") ", NULL);
    chaz_MakeRule_add_command(binary->rule, command);

    if (installed) {
        chaz_MakeFile_install(self, target, "$(BINDIR)", NULL);
    }

    chaz_CFlags_destroy(ldflags);
    free(command);
    free(target);
    return binary;
}

chaz_MakeBinary*
chaz_MakeFile_add_shared_lib(chaz_MakeFile *self, const char *dir,
                             const char *basename, const char *version,
                             const char *major_version, int installed) {
    int binfmt = chaz_CC_binary_format();
    char *path, *vpath, *mpath;
    char *command;
    chaz_MakeBinary *binary;
    chaz_CFlags *ldflags;

    path = chaz_CC_shared_lib_filename(dir, basename, NULL);
    if (binfmt == CHAZ_CC_BINFMT_PE) {
        vpath = chaz_CC_shared_lib_filename(dir, basename, major_version);
        mpath = NULL;
    }
    else {
        vpath = chaz_CC_shared_lib_filename(dir, basename, version);
        mpath = chaz_CC_shared_lib_filename(dir, basename, major_version);
    }

    binary = S_chaz_MakeFile_add_binary(self, CHAZ_MAKEBINARY_SHARED_LIB,
                                        basename, vpath);

    chaz_CFlags_compile_shared_library(binary->cflags);

    ldflags = chaz_CC_new_cflags();
    if (chaz_CC_is_msvc()) {
        chaz_CFlags_append(ldflags, "/nologo");
    }
    chaz_CFlags_set_link_output(ldflags, "$@");
    chaz_CFlags_link_shared_library(ldflags, basename, version, major_version);
    if (binfmt == CHAZ_CC_BINFMT_MACHO) {
        /* Set temporary install name with full path on Darwin. */
        char *install_name = chaz_Util_join("", "-install_name \"$(CURDIR)/",
                                            mpath, "\"", NULL);
        chaz_CFlags_append(ldflags, install_name);
        free(install_name);
    }

    command = chaz_Util_join("", "$(LINK) ", chaz_CFlags_get_string(ldflags),
                             " ", binary->obj_dollar_var,
                             " $(", binary->ldflags_var->name, ")", NULL);
    chaz_MakeRule_add_command(binary->rule, command);
    free(command);

    if (installed) {
        const char *root = binfmt == CHAZ_CC_BINFMT_PE
                           ? "$(BINDIR)" : "$(LIBDIR)";
        chaz_MakeFile_install(self, vpath, root, NULL);
    }

    /* Add symlinks. */
    if (binfmt == CHAZ_CC_BINFMT_ELF || binfmt == CHAZ_CC_BINFMT_MACHO) {
        char *name  = chaz_CC_shared_lib_filename(NULL, basename, NULL);
        char *vname = chaz_CC_shared_lib_filename(NULL, basename, version);
        char *mname = chaz_CC_shared_lib_filename(NULL, basename,
                                                  major_version);
        const char *ltarget = binfmt == CHAZ_CC_BINFMT_MACHO ? vname : mname;

        command = chaz_Util_join(" ", "ln -sf", vname, mpath, NULL);
        chaz_MakeRule_add_command(binary->rule, command);
        free(command);

        command = chaz_Util_join(" ", "ln -sf", ltarget, path, NULL);
        chaz_MakeRule_add_command(binary->rule, command);
        free(command);

        if (installed) {
            command = chaz_Util_join("", "ln -sf ", vname,
                                     " \"$(LIBDIR)/", mname, "\"",
                                     NULL);
            chaz_MakeRule_add_command(self->install, command);
            free(command);

            command = chaz_Util_join("", "ln -sf ", ltarget,
                                     " \"$(LIBDIR)/", name, "\"",
                                     NULL);
            chaz_MakeRule_add_command(self->install, command);
            free(command);

            if (binfmt == CHAZ_CC_BINFMT_MACHO) {
                /* Change install name to installation path. */
                command = chaz_Util_join("",
                    "install_name_tool",
                    " -id \"$(LIBDIR)/", mname, "\"",
                    " \"$(LIBDIR)/", vname, "\"",
                    NULL
                );
                chaz_MakeRule_add_command(self->install, command);
                free(command);
            }
        }

        chaz_MakeRule_add_rm_command(self->clean, mpath);
        chaz_MakeRule_add_rm_command(self->clean, path);

        free(mname);
        free(vname);
        free(name);
    }

    if (binfmt == CHAZ_CC_BINFMT_PE) {
        /* Import library. */
        char *filename = chaz_CC_import_lib_filename(dir, basename,
                                                     major_version);
        if (installed) {
            chaz_MakeFile_install(self, filename, "$(LIBDIR)", NULL);
        }
        chaz_MakeRule_add_rm_command(self->clean, filename);
        free(filename);
    }

    if (chaz_CC_is_msvc()) {
        /* Remove export file. */
        char *filename = chaz_CC_export_filename(dir, basename, major_version);
        chaz_MakeRule_add_rm_command(self->clean, filename);
        free(filename);
    }

    chaz_CFlags_destroy(ldflags);
    free(mpath);
    free(vpath);
    free(path);
    return binary;
}

chaz_MakeBinary*
chaz_MakeFile_add_static_lib(chaz_MakeFile *self, const char *dir,
                             const char *basename, int installed) {
    char *target = chaz_CC_static_lib_filename(dir, basename);
    char *command;
    chaz_MakeBinary *binary
        = S_chaz_MakeFile_add_binary(self, CHAZ_MAKEBINARY_STATIC_LIB,
                                     basename, target);

    command = chaz_CC_format_archiver_command("$@", binary->obj_dollar_var);
    chaz_MakeRule_add_command(binary->rule, command);

    if (installed) {
        chaz_MakeFile_install(self, target, "$(LIBDIR)", NULL);
    }

    free(command);
    free(target);
    return binary;
}

static chaz_MakeBinary*
S_chaz_MakeFile_add_binary(chaz_MakeFile *self, int type, const char *basename,
                           const char *target) {
    chaz_MakeBinary *binary
        = (chaz_MakeBinary*)calloc(1, sizeof(chaz_MakeBinary));
    const char *suffix;
    char *uc_base = chaz_Util_strdup(basename);
    char *binary_var_name;
    char *obj_var_name;
    char *cflags_var_name;
    char *ldflags_var_name;
    char *obj_dollar_var;
    size_t i;
    size_t num_binaries;
    size_t alloc_size;
    chaz_MakeBinary **binaries;

    switch (type) {
        case CHAZ_MAKEBINARY_EXE:        suffix = "EXE";        break;
        case CHAZ_MAKEBINARY_STATIC_LIB: suffix = "STATIC_LIB"; break;
        case CHAZ_MAKEBINARY_SHARED_LIB: suffix = "SHARED_LIB"; break;
        default:
            chaz_Util_die("Unknown binary type %d", type);
            return NULL;
    }

    for (i = 0; uc_base[i] != '\0'; i++) {
        uc_base[i] = toupper((unsigned char)uc_base[i]);
    }

    binary_var_name  = chaz_Util_join("_", uc_base, suffix, NULL);
    obj_var_name     = chaz_Util_join("_", uc_base, suffix, "OBJS", NULL);
    cflags_var_name  = chaz_Util_join("_", uc_base, suffix, "CFLAGS", NULL);
    ldflags_var_name = chaz_Util_join("_", uc_base, suffix, "LDFLAGS", NULL);
    obj_dollar_var   = chaz_Util_join("", "$(", obj_var_name, ")", NULL);

    chaz_MakeFile_add_var(self, binary_var_name, target);

    binary->rule           = S_chaz_MakeRule_new(target, obj_dollar_var);
    binary->obj_var        = chaz_MakeFile_add_var(self, obj_var_name, NULL);
    binary->obj_dollar_var = obj_dollar_var;
    binary->sources        = (char**)calloc(1, sizeof(char*));
    binary->single_sources = (char**)calloc(1, sizeof(char*));
    binary->dirs           = (char**)calloc(1, sizeof(char*));

    binary->cflags_var  = chaz_MakeFile_add_var(self, cflags_var_name, NULL);
    binary->cflags      = chaz_CC_new_cflags();
    binary->ldflags_var = chaz_MakeFile_add_var(self, ldflags_var_name, NULL);
    binary->ldflags     = chaz_CC_new_cflags();

    chaz_MakeRule_add_rm_command(self->clean, obj_dollar_var);
    chaz_MakeRule_add_rm_command(self->clean, target);

    num_binaries = self->num_binaries;
    alloc_size   = (num_binaries + 2) * sizeof(chaz_MakeBinary*);
    binaries     = (chaz_MakeBinary**)realloc(self->binaries, alloc_size);
    binaries[num_binaries]   = binary;
    binaries[num_binaries+1] = NULL;
    self->binaries     = binaries;
    self->num_binaries = num_binaries + 1;

    free(ldflags_var_name);
    free(cflags_var_name);
    free(obj_var_name);
    free(binary_var_name);
    free(uc_base);
    return binary;
}

chaz_MakeBinary*
chaz_MakeFile_add_lemon_exe(chaz_MakeFile *self, const char *dir) {
    chaz_MakeBinary *exe = chaz_MakeFile_add_exe(self, dir, "lemon", 0);
    chaz_MakeBinary_add_src_file(exe, dir, "lemon.c");
    return exe;
}

chaz_MakeRule*
chaz_MakeFile_add_lemon_grammar(chaz_MakeFile *self,
                                const char *base_name) {
    char *c_file  = chaz_Util_join(".", base_name, "c", NULL);
    char *h_file  = chaz_Util_join(".", base_name, "h", NULL);
    char *y_file  = chaz_Util_join(".", base_name, "y", NULL);
    char *command = chaz_Util_join(" ", "$(LEMON_EXE) -q", y_file, NULL);

    chaz_MakeRule *rule = chaz_MakeFile_add_rule(self, c_file, y_file);
    chaz_MakeRule *clean_rule = chaz_MakeFile_clean_rule(self);

    chaz_MakeRule_add_prereq(rule, "$(LEMON_EXE)");
    chaz_MakeRule_add_command(rule, command);

    chaz_MakeRule_add_rm_command(clean_rule, h_file);
    chaz_MakeRule_add_rm_command(clean_rule, c_file);

    free(c_file);
    free(h_file);
    free(y_file);
    free(command);
    return rule;
}

void
chaz_MakeFile_install(chaz_MakeFile *self, const char *src, const char *root,
                      const char *dest) {
    char *path;
    char *command;

    if (dest) {
        path = chaz_Util_join(chaz_OS_dir_sep(), root, dest, NULL);
    }
    else {
        path = chaz_Util_strdup(root);
    }

    S_chaz_MakeFile_add_install_dir(self, path);

    if (chaz_Make.shell_type == CHAZ_OS_POSIX) {
        command = chaz_Util_join("", "cp -f ", src, " \"", path, "\"", NULL);
    }
    else if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
        command = chaz_Util_join("", "copy /y ", src, " \"", path, "\" >nul",
                                 NULL);
    }
    else {
        chaz_Util_die("Unsupported shell type: %d", chaz_Make.shell_type);
    }

    chaz_MakeRule_add_command(self->install, command);

    free(command);
    free(path);
}

void
chaz_MakeFile_install_dir(chaz_MakeFile *self, const char *src,
                          const char *root, const char *dest) {
    char *path;
    char *command;

    if (dest) {
        path = chaz_Util_join(chaz_OS_dir_sep(), root, dest, NULL);
    }
    else {
        path = chaz_Util_strdup(root);
    }

    S_chaz_MakeFile_add_install_dir(self, path);

    if (chaz_Make.shell_type == CHAZ_OS_POSIX) {
        command = chaz_Util_join("", "cp -Rf ", src, "/* \"", path, "\"",
                                 NULL);
    }
    else if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
        command = chaz_Util_join("", "xcopy /seiy ", src, " \"", path,
                                 "\" >nul", NULL);
    }
    else {
        chaz_Util_die("Unsupported shell type: %d", chaz_Make.shell_type);
    }

    chaz_MakeRule_add_command(self->install, command);

    free(command);
    free(path);
}

void
chaz_MakeFile_install_pkgconfig(chaz_MakeFile *self, const char *name,
                                const char *version, const char *content) {
    size_t size;
    const char *p;
    char *q;
    char *escaped;
    char *command;

    if (chaz_OS_shell_type() != CHAZ_OS_POSIX) { return; }

    /* Escape content for POSIX printf utility. */

    for (p = content, size = 0; *p != '\0'; p++) {
        switch (*p) {
            case '%':  size += 2; break;
            case '\\': size += 2; break;
            case '\'': size += 4; break;
            case '\n': size += 2; break;
            default:   size += 1; break;
        }
    }

    escaped = (char*)malloc(size + 1);

    for (p = content, q = escaped; *p != '\0'; p++) {
        switch (*p) {
            case '%':  memcpy(q, "%%",    2); q += 2; break;
            case '\\': memcpy(q, "\\\\",  2); q += 2; break;
            case '\'': memcpy(q, "\\047", 4); q += 4; break;
            case '\n': memcpy(q, "\\n",   2); q += 2; break;
            default: *q++ = *p; break;
        }
    }

    *q++ = '\0';

    S_chaz_MakeFile_add_install_dir(self, "$(LIBDIR)/pkgconfig");

    command = chaz_Util_join("",
        "printf '"
            "libdir=$(LIBDIR)\\n"
            "version=", version, "\\n"
            "\\n",
            escaped,
        "' >\"$(LIBDIR)/pkgconfig/", name, ".pc\"",
        NULL
    );
    chaz_MakeRule_add_command(self->install, command);

    free(command);
    free(escaped);
}

static void
S_chaz_MakeFile_add_install_dir(chaz_MakeFile *self, const char *dir) {
    size_t   i;
    size_t   num_install_dirs;
    size_t   alloc_size;
    char   **install_dirs;

    for (i = 0; self->install_dirs[i]; i++) {
        if (strcmp(dir, self->install_dirs[i]) == 0) {
            return;
        }
    }

    num_install_dirs = self->num_install_dirs;
    alloc_size       = (num_install_dirs + 2) * sizeof(char*);
    install_dirs     = (char**)realloc(self->install_dirs, alloc_size);
    install_dirs[num_install_dirs]   = chaz_Util_strdup(dir);
    install_dirs[num_install_dirs+1] = NULL;
    self->install_dirs     = install_dirs;
    self->num_install_dirs = num_install_dirs + 1;
}

void
chaz_MakeFile_write(chaz_MakeFile *self) {
    FILE   *out;
    size_t  i;

    out = fopen("Makefile", "w");
    if (!out) {
        chaz_Util_die("Can't open Makefile\n");
    }

    if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
        /* Make sure that mingw32-make uses the cmd.exe shell. */
        fprintf(out, "SHELL = cmd\n");
    }

    fprintf(out, "CC = %s\n", chaz_CC_get_cc());
    fprintf(out, "LINK = %s\n", chaz_CC_link_command());

    S_chaz_MakeFile_write_install_vars(out);

    /* Finalize binary vars. */
    for (i = 0; self->binaries[i]; i++) {
        chaz_MakeBinary *binary = self->binaries[i];
        const char *flags;

        flags = chaz_CFlags_get_string(binary->cflags);
        chaz_MakeVar_append(binary->cflags_var, flags);
        flags = chaz_CFlags_get_string(binary->ldflags);
        chaz_MakeVar_append(binary->ldflags_var, flags);
    }

    for (i = 0; self->vars[i]; i++) {
        chaz_MakeVar *var = self->vars[i];
        fprintf(out, "%s = %s\n", var->name, var->value);
    }
    fprintf(out, "\n");

    for (i = 0; self->rules[i]; i++) {
        S_chaz_MakeRule_write(self->rules[i], out);
    }

    for (i = 0; self->binaries[i]; i++) {
        S_chaz_MakeFile_write_binary_rules(self->binaries[i], out);
    }

    if (self->num_install_dirs) {
        /* Prepend mkdir commands. */
        chaz_MakeRule *dummy = S_chaz_MakeRule_new(NULL, NULL);
        char *commands;

        for (i = 0; self->install_dirs[i]; i++) {
            chaz_MakeRule_add_mkdir_command(dummy, self->install_dirs[i]);
        }

        commands = chaz_Util_join("", dummy->commands, self->install->commands,
                                  NULL);
        free(self->install->commands);
        self->install->commands = commands;

        S_chaz_MakeRule_destroy(dummy);
    }

    S_chaz_MakeRule_write(self->install, out);
    S_chaz_MakeRule_write(self->clean, out);
    S_chaz_MakeRule_write(self->distclean, out);

    /* Suffix rule for .c files. */
    if (chaz_CC_is_msvc()) {
        fprintf(out, ".c.obj :\n");
        fprintf(out, "\t$(CC) /nologo $(CFLAGS) /c $< /Fo$@\n\n");
    }
    else {
        fprintf(out, ".c.o :\n");
        fprintf(out, "\t$(CC) $(CFLAGS) -c $< -o $@\n\n");
    }

    fclose(out);
}

static void
S_chaz_MakeFile_write_install_vars(FILE *out) {
    const char *dir_sep = chaz_OS_dir_sep();
    const char *strval;

    strval = chaz_CLI_strval(chaz_Make.cli, "prefix");
    fprintf(out, "PREFIX = %s\n", strval ? strval : "/usr/local");

    strval = chaz_CLI_strval(chaz_Make.cli, "bindir");
    if (strval) {
        fprintf(out, "BINDIR = %s\n", strval);
    }
    else {
        fprintf(out, "BINDIR = $(PREFIX)%sbin\n", dir_sep);
    }

    strval = chaz_CLI_strval(chaz_Make.cli, "datarootdir");
    if (strval) {
        fprintf(out, "DATAROOTDIR = %s\n", strval);
    }
    else {
        fprintf(out, "DATAROOTDIR = $(PREFIX)%sshare\n", dir_sep);
    }

    strval = chaz_CLI_strval(chaz_Make.cli, "datadir");
    fprintf(out, "DATADIR = %s\n", strval ? strval : "$(DATAROOTDIR)");

    strval = chaz_CLI_strval(chaz_Make.cli, "libdir");
    if (strval) {
        fprintf(out, "LIBDIR = %s\n", strval);
    }
    else {
        fprintf(out, "LIBDIR = $(PREFIX)%slib\n", dir_sep);
    }

    strval = chaz_CLI_strval(chaz_Make.cli, "mandir");
    if (strval) {
        fprintf(out, "MANDIR = %s\n", strval);
    }
    else {
        fprintf(out, "MANDIR = $(DATAROOTDIR)%sman\n", dir_sep);
    }
}

static void
S_chaz_MakeFile_write_binary_rules(chaz_MakeBinary *binary, FILE *out) {
    const char *cflags_string;

    S_chaz_MakeRule_write(binary->rule, out);

    cflags_string = chaz_CFlags_get_string(binary->cflags);

    /* Write rules to compile with custom flags. */
    if (cflags_string[0] != '\0') {
        char *dollar_var = chaz_Util_join("", "$(", binary->cflags_var->name,
                                          ")", NULL);

        if (!chaz_Make.supports_pattern_rules
            || chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
            /* Write a rule for each object file. This is needed for make
             * utilities that don't support pattern rules but also for
             * mingw32-make which has problems with pattern rules and
             * backslash directory separators.
             */
            S_chaz_MakeFile_write_object_rules(binary->sources, dollar_var,
                                               out);
        }
        else {
            /* Write a pattern rule for each directory. */
            S_chaz_MakeFile_write_pattern_rules(binary->dirs, dollar_var, out);
            /* Write a rule for each object added with add_src_file. */
            S_chaz_MakeFile_write_object_rules(binary->single_sources,
                                               dollar_var, out);
        }

        free(dollar_var);
    }
}

static void
S_chaz_MakeFile_write_object_rules(char **sources, const char *cflags,
                                   FILE *out) {
    const char *cc = chaz_CC_is_msvc() ? "$(CC) /nologo" : "$(CC)";
    chaz_CFlags *output_cflags = chaz_CC_new_cflags();
    const char *output_cflags_string;
    size_t i;

    chaz_CFlags_set_output_obj(output_cflags, "$@");
    output_cflags_string = chaz_CFlags_get_string(output_cflags);

    for (i = 0; sources[i]; i++) {
        const char *source = sources[i];
        char *obj_path = S_chaz_MakeBinary_obj_path(source);
        chaz_MakeRule *rule;
        char *command;

        if (obj_path == NULL) { continue; }

        rule = S_chaz_MakeRule_new(obj_path, source);
        command = chaz_Util_join(" ", cc, "$(CFLAGS)", cflags, source,
                                 output_cflags_string, NULL);
        chaz_MakeRule_add_command(rule, command);
        S_chaz_MakeRule_write(rule, out);

        free(command);
        S_chaz_MakeRule_destroy(rule);
        free(obj_path);
    }

    chaz_CFlags_destroy(output_cflags);
}

static void
S_chaz_MakeFile_write_pattern_rules(char **dirs, const char *cflags,
                                    FILE *out) {
    const char *cc = chaz_CC_is_msvc() ? "$(CC) /nologo" : "$(CC)";
    const char *obj_ext = chaz_CC_obj_ext();
    const char *dir_sep = chaz_OS_dir_sep();
    chaz_CFlags *output_cflags = chaz_CC_new_cflags();
    const char *output_cflags_string;
    char *command;
    size_t i;

    chaz_CFlags_set_output_obj(output_cflags, "$@");
    output_cflags_string = chaz_CFlags_get_string(output_cflags);
    command  = chaz_Util_join(" ", cc, "$(CFLAGS)", cflags, "$<",
                              output_cflags_string, NULL);

    for (i = 0; dirs[i]; i++) {
        const char *dir = dirs[i];
        char *target = chaz_Util_join("", dir, dir_sep, "%", obj_ext,
                                      NULL);
        char *prereq = chaz_Util_join("", dir, dir_sep, "%.c", NULL);
        chaz_MakeRule *rule = S_chaz_MakeRule_new(target, prereq);

        chaz_MakeRule_add_command(rule, command);
        S_chaz_MakeRule_write(rule, out);

        S_chaz_MakeRule_destroy(rule);
        free(prereq);
        free(target);
    }

    free(command);
    chaz_CFlags_destroy(output_cflags);
}

void
chaz_MakeVar_append(chaz_MakeVar *self, const char *element) {
    char *value;

    if (element[0] == '\0') { return; }

    if (self->num_elements == 0) {
        value = chaz_Util_strdup(element);
    }
    else {
        value = (char*)malloc(strlen(self->value) + strlen(element) + 20);

        if (self->num_elements == 1) {
            sprintf(value, "\\\n    %s \\\n    %s", self->value, element);
        }
        else {
            sprintf(value, "%s \\\n    %s", self->value, element);
        }
    }

    free(self->value);
    self->value = value;
    self->num_elements++;
}

static chaz_MakeRule*
S_chaz_MakeRule_new(const char *target, const char *prereq) {
    chaz_MakeRule *rule = (chaz_MakeRule*)malloc(sizeof(chaz_MakeRule));

    rule->targets  = NULL;
    rule->prereqs  = NULL;
    rule->commands = NULL;

    if (target) { chaz_MakeRule_add_target(rule, target); }
    if (prereq) { chaz_MakeRule_add_prereq(rule, prereq); }

    return rule;
}

static void
S_chaz_MakeRule_destroy(chaz_MakeRule *self) {
    if (self->targets)  { free(self->targets); }
    if (self->prereqs)  { free(self->prereqs); }
    if (self->commands) { free(self->commands); }
    free(self);
}

static void
S_chaz_MakeRule_write(chaz_MakeRule *self, FILE *out) {
    fprintf(out, "%s :", self->targets);
    if (self->prereqs) {
        fprintf(out, " %s", self->prereqs);
    }
    fprintf(out, "\n");
    if (self->commands) {
        fprintf(out, "%s", self->commands);
    }
    fprintf(out, "\n");
}

void
chaz_MakeRule_add_target(chaz_MakeRule *self, const char *target) {
    char *targets;

    if (!self->targets) {
        targets = chaz_Util_strdup(target);
    }
    else {
        targets = chaz_Util_join(" ", self->targets, target, NULL);
        free(self->targets);
    }

    self->targets = targets;
}

void
chaz_MakeRule_add_prereq(chaz_MakeRule *self, const char *prereq) {
    char *prereqs;

    if (!self->prereqs) {
        prereqs = chaz_Util_strdup(prereq);
    }
    else {
        prereqs = chaz_Util_join(" ", self->prereqs, prereq, NULL);
        free(self->prereqs);
    }

    self->prereqs = prereqs;
}

void
chaz_MakeRule_add_command(chaz_MakeRule *self, const char *command) {
    char *commands;

    if (!self->commands) {
        commands = (char*)malloc(strlen(command) + 20);
        sprintf(commands, "\t%s\n", command);
    }
    else {
        commands = (char*)malloc(strlen(self->commands) + strlen(command) + 20);
        sprintf(commands, "%s\t%s\n", self->commands, command);
        free(self->commands);
    }

    self->commands = commands;
}

void
chaz_MakeRule_add_mkdir_command(chaz_MakeRule *self, const char *dir) {
    char *command;

    if (chaz_Make.shell_type == CHAZ_OS_POSIX) {
        command = chaz_Util_join("", "mkdir -p \"", dir, "\"", NULL);
    }
    else if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
        command = chaz_Util_join("", "if not exist \"", dir, "\" mkdir \"",
                                 dir, "\"", NULL);
    }
    else {
        chaz_Util_die("Unsupported shell type: %d", chaz_Make.shell_type);
    }

    chaz_MakeRule_add_command(self, command);
    free(command);
}

void
chaz_MakeRule_add_rm_command(chaz_MakeRule *self, const char *files) {
    char *command;

    if (chaz_Make.shell_type == CHAZ_OS_POSIX) {
        command = chaz_Util_join(" ", "rm -f", files, NULL);
    }
    else if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
        command = chaz_Util_join("", "for %%i in (", files,
                                 ") do @if exist %%i del /f %%i", NULL);
    }
    else {
        chaz_Util_die("Unsupported shell type: %d", chaz_Make.shell_type);
    }

    chaz_MakeRule_add_command(self, command);
    free(command);
}

void
chaz_MakeRule_add_recursive_rm_command(chaz_MakeRule *self, const char *dirs) {
    char *command;

    if (chaz_Make.shell_type == CHAZ_OS_POSIX) {
        command = chaz_Util_join(" ", "rm -rf", dirs, NULL);
    }
    else if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
        command = chaz_Util_join("", "for %%i in (", dirs,
                                 ") do @if exist %%i rmdir /s /q %%i", NULL);
    }
    else {
        chaz_Util_die("Unsupported shell type: %d", chaz_Make.shell_type);
    }

    chaz_MakeRule_add_command(self, command);
    free(command);
}

void
chaz_MakeRule_add_make_command(chaz_MakeRule *self, const char *dir,
                               const char *target) {
    char *command;

    if (chaz_Make.shell_type == CHAZ_OS_POSIX) {
        if (!target) {
            command = chaz_Util_join("", "(cd ", dir, " && $(MAKE))", NULL);
        }
        else {
            command = chaz_Util_join("", "(cd ", dir, " && $(MAKE) ", target,
                                     ")", NULL);
        }
    }
    else if (chaz_Make.shell_type == CHAZ_OS_CMD_EXE) {
        if (!target) {
            command = chaz_Util_join(" ", "pushd", dir, "&& $(MAKE) && popd",
                                     NULL);
        }
        else {
            command = chaz_Util_join(" ", "pushd", dir, "&& $(MAKE)", target,
                                     "&& popd", NULL);
        }
    }
    else {
        chaz_Util_die("Unsupported shell type: %d", chaz_Make.shell_type);
    }

    chaz_MakeRule_add_command(self, command);
    free(command);
}

static void
S_chaz_MakeBinary_destroy(chaz_MakeBinary *self) {
    size_t i;

    free(self->obj_dollar_var);
    S_chaz_MakeRule_destroy(self->rule);

    for (i = 0; i < self->num_sources; i++) {
        free(self->sources[i]);
    }
    free(self->sources);
    for (i = 0; i < self->num_single_sources; i++) {
        free(self->single_sources[i]);
    }
    free(self->single_sources);
    for (i = 0; i < self->num_dirs; i++) {
        free(self->dirs[i]);
    }
    free(self->dirs);

    chaz_CFlags_destroy(self->cflags);
    chaz_CFlags_destroy(self->ldflags);

    free(self);
}

void
chaz_MakeBinary_add_src_file(chaz_MakeBinary *self, const char *dir,
                             const char *filename) {
    size_t num_sources = self->num_single_sources;
    size_t alloc_size  = (num_sources + 2) * sizeof(char*);
    char **sources = (char**)realloc(self->single_sources, alloc_size);
    char *path;

    if (dir == NULL || strcmp(dir, ".") == 0) {
        path = chaz_Util_strdup(filename);
    }
    else {
        const char *dir_sep = chaz_OS_dir_sep();
        path = chaz_Util_join(dir_sep, dir, filename, NULL);
    }

    /* Add to single_sources. */
    sources[num_sources]     = path;
    sources[num_sources+1]   = NULL;
    self->single_sources     = sources;
    self->num_single_sources = num_sources + 1;

    S_chaz_MakeBinary_do_add_src_file(self, path);
}

void
chaz_MakeBinary_add_src_dir(chaz_MakeBinary *self, const char *path) {
    chaz_MakeBinary_add_filtered_src_dir(self, path, NULL, NULL);
}

void
chaz_MakeBinary_add_filtered_src_dir(chaz_MakeBinary *self, const char *path,
                                     chaz_Make_file_filter_t filter,
                                     void *filter_ctx) {
    chaz_MakeBinaryContext context;
    size_t num_dirs = self->num_dirs;
    char **dirs = (char**)realloc(self->dirs, (num_dirs + 2) * sizeof(char*));

    dirs[num_dirs]   = chaz_Util_strdup(path);
    dirs[num_dirs+1] = NULL;
    self->dirs     = dirs;
    self->num_dirs = num_dirs + 1;

    context.binary     = self;
    context.filter     = filter;
    context.filter_ctx = filter_ctx;

    chaz_Make_list_files(path, "c", S_chaz_MakeBinary_list_files_callback,
                         &context);
}

static void
S_chaz_MakeBinary_list_files_callback(const char *dir, char *file,
                                      void *vcontext) {
    chaz_MakeBinaryContext *context = (chaz_MakeBinaryContext*)vcontext;
    const char *dir_sep = chaz_OS_dir_sep();

    if (context->filter == NULL
        || context->filter(dir, file, context->filter_ctx) != 0
       ) {
        char *path = chaz_Util_join(dir_sep, dir, file, NULL);
        S_chaz_MakeBinary_do_add_src_file(context->binary, path);
        free(path);
    }
}

static void
S_chaz_MakeBinary_do_add_src_file(chaz_MakeBinary *self, const char *path) {
    size_t num_sources = self->num_sources;
    size_t alloc_size  = (num_sources + 2) * sizeof(char*);
    char **sources = (char**)realloc(self->sources, alloc_size);
    char *obj_path;

    sources[num_sources]   = chaz_Util_strdup(path);
    sources[num_sources+1] = NULL;
    self->sources     = sources;
    self->num_sources = num_sources + 1;

    obj_path = S_chaz_MakeBinary_obj_path(path);
    if (obj_path == NULL) {
        chaz_Util_warn("Invalid source filename: %s", path);
    }
    else {
        chaz_MakeVar_append(self->obj_var, obj_path);
        free(obj_path);
    }
}

static char*
S_chaz_MakeBinary_obj_path(const char *src_path) {
    const char *dir_sep = chaz_OS_dir_sep();
    const char *obj_ext = chaz_CC_obj_ext();
    size_t obj_ext_len = strlen(obj_ext);
    size_t i = strlen(src_path);
    char *retval;

    while (i > 0) {
        i -= 1;
        if (src_path[i] == dir_sep[0]) { return NULL; }
        if (src_path[i] == '.')        { break; }
    }

    if (src_path[i] != '.') { return NULL; }

    retval = (char*)malloc(i + obj_ext_len + 1);
    memcpy(retval, src_path, i);
    memcpy(retval + i, obj_ext, obj_ext_len + 1);

    return retval;
}

void
chaz_MakeBinary_add_prereq(chaz_MakeBinary *self, const char *prereq) {
    chaz_MakeRule_add_prereq(self->rule, prereq);
}

char*
chaz_MakeBinary_obj_string(chaz_MakeBinary *self) {
    char *retval = chaz_Util_strdup("");
    size_t i;

    for (i = 0; i < self->num_sources; i++) {
        const char *sep = retval[0] == '\0' ? "" : " ";
        char *obj_path = S_chaz_MakeBinary_obj_path(self->sources[i]);
        char *tmp;

        if (obj_path == NULL) { continue; }

        tmp = chaz_Util_join("", retval, sep, obj_path, NULL);
        free(retval);
        retval = tmp;

        free(obj_path);
    }

    return retval;
}

const char*
chaz_MakeBinary_get_target(chaz_MakeBinary *self) {
    return self->rule->targets;
}

chaz_CFlags*
chaz_MakeBinary_get_compile_flags(chaz_MakeBinary *self) {
    return self->cflags;
}

chaz_CFlags*
chaz_MakeBinary_get_link_flags(chaz_MakeBinary *self) {
    return self->ldflags;
}

void
chaz_Make_list_files(const char *dir, const char *ext,
                     chaz_Make_file_callback_t callback, void *context) {
    int         shell_type = chaz_OS_shell_type();
    const char *pattern;
    char       *command;
    char       *list;
    char       *prefix;
    char       *file;
    size_t      command_size;
    size_t      list_len;
    size_t      prefix_len;

    /* List files using shell. */

    if (shell_type == CHAZ_OS_POSIX) {
        pattern = "find %s -name '*.%s' -type f";
    }
    else if (shell_type == CHAZ_OS_CMD_EXE) {
        pattern = "dir %s\\*.%s /s /b /a-d";
    }
    else {
        chaz_Util_die("Unknown shell type %d", shell_type);
    }

    command_size = strlen(pattern) + strlen(dir) + strlen(ext) + 10;
    command = (char*)malloc(command_size);
    sprintf(command, pattern, dir, ext);
    list = chaz_OS_run_and_capture(command, &list_len);
    free(command);
    if (!list) {
        chaz_Util_die("Failed to list files in '%s'", dir);
    }
    list[list_len-1] = 0;

    /* Find directory prefix to strip from files */

    if (shell_type == CHAZ_OS_POSIX) {
        prefix_len = strlen(dir);
        prefix = (char*)malloc(prefix_len + 2);
        memcpy(prefix, dir, prefix_len);
        prefix[prefix_len++] = '/';
        prefix[prefix_len]   = '\0';
    }
    else {
        char   *output;
        size_t  output_len;

        /* 'dir /s' returns absolute paths, so we have to find the absolute
         * path of the directory. This is done by using the variable
         * substitution feature of the 'for' command.
         */
        pattern = "for %%I in (%s) do @echo %%~fI";
        command_size = strlen(pattern) + strlen(dir) + 10;
        command = (char*)malloc(command_size);
        sprintf(command, pattern, dir);
        output = chaz_OS_run_and_capture(command, &output_len);
        free(command);
        if (!output) { chaz_Util_die("Failed to find absolute path"); }

        /* Strip whitespace from end of output. */
        for (prefix_len = output_len; prefix_len > 0; --prefix_len) {
            if (!isspace((unsigned char)output[prefix_len-1])) { break; }
        }
        prefix = (char*)malloc(prefix_len + 2);
        memcpy(prefix, output, prefix_len);
        prefix[prefix_len++] = '\\';
        prefix[prefix_len]   = '\0';
        free(output);
    }

    /* Iterate file list and invoke callback. */

    for (file = strtok(list, "\r\n"); file; file = strtok(NULL, "\r\n")) {
        if (strlen(file) <= prefix_len
            || memcmp(file, prefix, prefix_len) != 0
           ) {
            chaz_Util_die("Expected prefix '%s' for file name '%s'", prefix,
                          file);
        }

        callback(dir, file + prefix_len, context);
    }

    free(prefix);
    free(list);
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/OperatingSystem.c"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>

/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */

#define CHAZ_OS_TARGET_PATH  "_charmonizer_target"
#define CHAZ_OS_NAME_MAX     31

static struct {
    char name[CHAZ_OS_NAME_MAX+1];
    char dev_null[20];
    char dir_sep[2];
    char local_command_start[3];
    int  shell_type;
    int  run_sh_via_cmd_exe;
} chaz_OS = { "", "", "", "", 0, 0 };

static int
chaz_OS_run_sh_via_cmd_exe(const char *command, const char *path);

void
chaz_OS_init(void) {
    char *output;
    size_t output_len;

    if (chaz_Util_verbosity) {
        printf("Initializing Charmonizer/Core/OperatingSystem...\n");
    }

    /* Detect shell based on escape character. */

    /* Needed to make redirection work. */
    chaz_OS.shell_type = CHAZ_OS_POSIX;

    output = chaz_OS_run_and_capture("echo foo\\^bar", &output_len);

    if (output_len >= 7 && memcmp(output, "foo\\bar", 7) == 0) {
        /* Escape character is caret. */
        if (chaz_Util_verbosity) {
            printf("Detected cmd.exe shell\n");
        }

        /* Try to see whether running commands via the `sh` command works.
         * Run the `find` command to check whether we're in a somewhat POSIX
         * compatible environment. */
        free(output);
        chaz_OS.run_sh_via_cmd_exe = 1;
        output = chaz_OS_run_and_capture("find . -prune", &output_len);

        if (output_len >= 2
            && output[0] == '.'
            && isspace((unsigned char)output[1])
           ) {
            if (chaz_Util_verbosity) {
                printf("Detected POSIX shell via cmd.exe\n");
            }
            chaz_OS.shell_type = CHAZ_OS_POSIX;
        }
        else {
            chaz_OS.shell_type = CHAZ_OS_CMD_EXE;
            chaz_OS.run_sh_via_cmd_exe = 0;
        }

        /* Redirection is always run through cmd.exe. */
        strcpy(chaz_OS.dev_null, "nul");
    }
    else if (output_len >= 7 && memcmp(output, "foo^bar", 7) == 0) {
        /* Escape character is backslash. */
        if (chaz_Util_verbosity) {
            printf("Detected POSIX shell\n");
        }
        chaz_OS.shell_type = CHAZ_OS_POSIX;
        strcpy(chaz_OS.dev_null, "/dev/null");
    }

    if (chaz_OS.shell_type == CHAZ_OS_CMD_EXE) {
        strcpy(chaz_OS.dir_sep, "\\");
        /* Empty string should work, too. */
        strcpy(chaz_OS.local_command_start, ".\\");
    }
    else if (chaz_OS.shell_type == CHAZ_OS_POSIX) {
        strcpy(chaz_OS.dir_sep, "/");
        strcpy(chaz_OS.local_command_start, "./");
    }
    else {
        chaz_Util_die("Couldn't identify shell");
    }

    free(output);
}

const char*
chaz_OS_dev_null(void) {
    return chaz_OS.dev_null;
}

const char*
chaz_OS_dir_sep(void) {
    return chaz_OS.dir_sep;
}

int
chaz_OS_shell_type(void) {
    return chaz_OS.shell_type;
}

const char*
chaz_OS_exe_ext(void) {
#ifdef _WIN32
    return ".exe";
#else
    return "";
#endif
}

int
chaz_OS_remove(const char *name) {
    /*
     * On Windows it can happen that another process, typically a
     * virus scanner, still has an open handle on the file. This can
     * make the subsequent recreation of a file with the same name
     * fail. As a workaround, files are renamed to a random name
     * before deletion.
     */
    int retval = 0;

    static const size_t num_random_chars = 16;

    size_t  name_len = strlen(name);
    size_t  i;
    char   *temp_name = (char*)malloc(name_len + num_random_chars + 1);
    const char *working_name = name;
    clock_t start, now;

    strcpy(temp_name, name);
    for (i = 0; i < num_random_chars; i++) {
        temp_name[name_len+i] = 'A' + rand() % 26;
    }
    temp_name[name_len+num_random_chars] = '\0';

    /* Try over and over again for around 1 second to rename the file.
     * Ideally we would sleep between attempts, but sleep functionality is not
     * portable. */
    start = now = clock();
    while (now - start < CLOCKS_PER_SEC) {
        now = clock();
        if (!rename(name, temp_name)) {
            /* The rename succeeded. */
            working_name = temp_name;
            break;
        }
        else if (errno == ENOENT) {
            /* No such file or directory, so no point in trying to remove it.
             * (Technically ENOENT is POSIX but hopefully this works.) */
            free(temp_name);
            return 0;
        }
    }

    /* Try over and over again for around 1 second to delete the file. */
    start = now = clock();
    while (!retval && now - start < CLOCKS_PER_SEC) {
        now = clock();
        retval = !remove(working_name);
    }

    free(temp_name);
    return retval;
}

int
chaz_OS_run_local_redirected(const char *command, const char *path) {
    char *local_command
        = chaz_Util_join("", chaz_OS.local_command_start, command, NULL);
    int retval = chaz_OS_run_redirected(local_command, path);
    free(local_command);
    return retval;
}

int
chaz_OS_run_quietly(const char *command) {
    return chaz_OS_run_redirected(command, chaz_OS.dev_null);
}

int
chaz_OS_run_redirected(const char *command, const char *path) {
    int retval = 1;
    char *quiet_command = NULL;
    if (chaz_OS.run_sh_via_cmd_exe) {
        return chaz_OS_run_sh_via_cmd_exe(command, path);
    }
    if (chaz_OS.shell_type == CHAZ_OS_POSIX
        || chaz_OS.shell_type == CHAZ_OS_CMD_EXE
        ) {
        quiet_command = chaz_Util_join(" ", command, ">", path, "2>&1", NULL);
    }
    else {
        chaz_Util_die("Don't know the shell type");
    }
    retval = system(quiet_command);
    free(quiet_command);
    return retval;
}

static int
chaz_OS_run_sh_via_cmd_exe(const char *command, const char *path) {
    size_t i;
    size_t size;
    char *escaped_command;
    char *wrapped_command;
    char *p;
    int retval;

    /* Compute size. */

    size = 0;

    for (i = 0; command[i] != '\0'; i++) {
        char c = command[i];

        switch (c) {
            case '"':
            case '\\':
                size += 2;
                break;

            case '%':
            case '!':
                size += 3;
                break;

            default:
                size += 1;
                break;
        }
    }

    /* Build sh command. */

    escaped_command = (char*)malloc(size + 1);
    p = escaped_command;

    /* Escape special characters. */

    for (i = 0; command[i] != '\0'; i++) {
        char c = command[i];

        switch (c) {
            case '"':
            case '\\':
                /* Escape double quote and backslash. */
                *p++ = '\\';
                *p++ = c;
                break;

            case '%':
            case '!':
                /* Break out of double quotes for percent sign and
                 * exclamation mark. This prevents variable expansion. */
                *p++ = '"';
                *p++ = c;
                *p++ = '"';
                break;

            default:
                *p++ = c;
                break;
        }
    }

    *p++ = '\0';

    /* Run sh command. */

    wrapped_command = chaz_Util_join("", "sh -c \"", escaped_command, "\" > ",
                                     path, " 2>&1", NULL);
    retval = system(wrapped_command);

    free(wrapped_command);
    free(escaped_command);
    return retval;
}

char*
chaz_OS_run_and_capture(const char *command, size_t *output_len) {
    char *output;
    chaz_OS_run_redirected(command, CHAZ_OS_TARGET_PATH);
    output = chaz_Util_slurp_file(CHAZ_OS_TARGET_PATH, output_len);
    chaz_Util_remove_and_verify(CHAZ_OS_TARGET_PATH);
    return output;
}

void
chaz_OS_mkdir(const char *filepath) {
    char *command = NULL;
    if (chaz_OS.shell_type == CHAZ_OS_POSIX
        || chaz_OS.shell_type == CHAZ_OS_CMD_EXE
       ) {
        command = chaz_Util_join(" ", "mkdir", filepath, NULL);
    }
    else {
        chaz_Util_die("Don't know the shell type");
    }
    chaz_OS_run_quietly(command);
    free(command);
}

void
chaz_OS_rmdir(const char *filepath) {
    char *command = NULL;
    if (chaz_OS.shell_type == CHAZ_OS_POSIX) {
        command = chaz_Util_join(" ", "rmdir", filepath, NULL);
    }
    else if (chaz_OS.shell_type == CHAZ_OS_CMD_EXE) {
        command = chaz_Util_join(" ", "rmdir", "/q", filepath, NULL);
    }
    else {
        chaz_Util_die("Don't know the shell type");
    }
    chaz_OS_run_quietly(command);
    free(command);
}


/***************************************************************************/

#line 17 "src/Charmonizer/Core/Util.c"
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */

/* va_copy is not part of C89. Assume that simple assignment works if it
 * isn't defined.
 */
#ifndef va_copy
  #define va_copy(dst, src) ((dst) = (src))
#endif

/* Global verbosity setting. */
int chaz_Util_verbosity = 1;

void
chaz_Util_write_file(const char *filename, const char *content) {
    FILE *fh = fopen(filename, "w+");
    size_t content_len = strlen(content);
    if (fh == NULL) {
        chaz_Util_die("Couldn't open '%s': %s", filename, strerror(errno));
    }
    fwrite(content, sizeof(char), content_len, fh);
    if (fclose(fh)) {
        chaz_Util_die("Error when closing '%s': %s", filename,
                      strerror(errno));
    }
}

char*
chaz_Util_slurp_file(const char *file_path, size_t *len_ptr) {
    FILE   *const file = fopen(file_path, "rb");
    char   *contents;
    size_t  len;
    long    check_val;

    /* Sanity check. */
    if (file == NULL) {
        chaz_Util_die("Error opening file '%s': %s", file_path,
                      strerror(errno));
    }

    /* Find length; return NULL if the file has a zero-length. */
    len = chaz_Util_flength(file);
    if (len == 0) {
        *len_ptr = 0;
        return NULL;
    }

    /* Allocate memory and read the file. */
    contents = (char*)malloc(len * sizeof(char) + 1);
    if (contents == NULL) {
        chaz_Util_die("Out of memory at %d, %s", __FILE__, __LINE__);
    }
    contents[len] = '\0';
    check_val = fread(contents, sizeof(char), len, file);

    /* Weak error check, because CRLF might result in fewer chars read. */
    if (check_val <= 0) {
        chaz_Util_die("Tried to read %d characters of '%s', got %d", (int)len,
                      file_path, check_val);
    }

    /* Set length pointer for benefit of caller. */
    *len_ptr = check_val;

    /* Clean up. */
    if (fclose(file)) {
        chaz_Util_die("Error closing file '%s': %s", file_path,
                      strerror(errno));
    }

    return contents;
}

long
chaz_Util_flength(void *file) {
    FILE *f = (FILE*)file;
    const long bookmark = ftell(f);
    long check_val;
    long len;

    /* Seek to end of file and check length. */
    check_val = fseek(f, 0, SEEK_END);
    if (check_val == -1) {
        chaz_Util_die("fseek error : %s\n", strerror(errno));
    }
    len = ftell(f);
    if (len == -1) { chaz_Util_die("ftell error : %s\n", strerror(errno)); }

    /* Return to where we were. */
    check_val = fseek(f, bookmark, SEEK_SET);
    if (check_val == -1) {
        chaz_Util_die("fseek error : %s\n", strerror(errno));
    }

    return len;
}

char*
chaz_Util_strdup(const char *string) {
    size_t len = strlen(string);
    char *copy = (char*)malloc(len + 1);
    strncpy(copy, string, len);
    copy[len] = '\0';
    return copy;
}

char*
chaz_Util_join(const char *sep, ...) {
    va_list args;
    char *result;

    va_start(args, sep);
    result = chaz_Util_vjoin(sep, args);
    va_end(args);

    return result;
}

char*
chaz_Util_vjoin(const char *sep, va_list orig_args) {
    va_list args;
    const char *string;
    char *result, *p;
    size_t sep_len = strlen(sep);
    size_t size;
    int i;

    /* Determine result size. */
    va_copy(args, orig_args);
    size = 1;
    string = va_arg(args, const char*);
    for (i = 0; string; ++i) {
        if (i != 0) { size += sep_len; }
        size += strlen(string);
        string = va_arg(args, const char*);
    }
    va_end(args);

    result = (char*)malloc(size);

    /* Create result string. */
    va_copy(args, orig_args);
    p = result;
    string = va_arg(args, const char*);
    for (i = 0; string; ++i) {
        size_t len;
        if (i != 0) {
            memcpy(p, sep, sep_len);
            p += sep_len;
        }
        len = strlen(string);
        memcpy(p, string, len);
        p += len;
        string = va_arg(args, const char*);
    }
    va_end(args);

    *p = '\0';

    return result;
}

void
chaz_Util_die(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(1);
}

void
chaz_Util_warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}

int
chaz_Util_remove_and_verify(const char *file_path) {
    /* Attempt to delete the file.  If it's gone after the attempt, return
     * success, whether or not it was there to begin with.
     * (ENOENT is POSIX not C89, but let's go with it for now.) */
    int result = chaz_OS_remove(file_path);
    if (result || errno == ENOENT) {
        return 1;
    }

    /* Issue a warning and return failure. */
    chaz_Util_warn("Failed to remove '%s': %s at %s line %d",
                   file_path, strerror(errno), __FILE__, __LINE__);
    return 0;
}

int
chaz_Util_can_open_file(const char *file_path) {
    FILE *garbage_fh;

    /* Use fopen as a portable test for the existence of a file. */
    garbage_fh = fopen(file_path, "rb");
    if (garbage_fh == NULL) {
        return 0;
    }
    else {
        fclose(garbage_fh);
        return 1;
    }
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* #include "Charmonizer/Probe.h" */
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/ConfWriterC.h" */
/* #include "Charmonizer/Core/ConfWriterPerl.h" */
/* #include "Charmonizer/Core/ConfWriterPython.h" */
/* #include "Charmonizer/Core/ConfWriterRuby.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/CLI.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/Make.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */

int
chaz_Probe_parse_cli_args(int argc, const char *argv[], chaz_CLI *cli) {
    int i;

    /* Register Charmonizer-specific options. */
    chaz_CLI_register(cli, "enable-c", "generate charmony.h", CHAZ_CLI_NO_ARG);
    chaz_CLI_register(cli, "enable-perl", "generate Charmony.pm", CHAZ_CLI_NO_ARG);
    chaz_CLI_register(cli, "enable-python", "generate charmony.py", CHAZ_CLI_NO_ARG);
    chaz_CLI_register(cli, "enable-ruby", "generate charmony.rb", CHAZ_CLI_NO_ARG);
    chaz_CLI_register(cli, "enable-makefile", NULL, CHAZ_CLI_NO_ARG);
    chaz_CLI_register(cli, "enable-coverage", NULL, CHAZ_CLI_NO_ARG);
    chaz_CLI_register(cli, "cc", "compiler command", CHAZ_CLI_ARG_REQUIRED);
    chaz_CLI_register(cli, "cflags", NULL, CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "make", "make command", CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "prefix", "install prefix", CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "bindir", "install dir for executables", CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "datarootdir", "root install dir for data files", CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "datadir", "install dir for data files", CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "libdir", "install dir for libraries", CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "mandir", "install dir for man pages", CHAZ_CLI_ARG_OPTIONAL);

    /* Parse options, exiting on failure. */
    if (!chaz_CLI_parse(cli, argc, argv)) {
        fprintf(stderr, "%s", chaz_CLI_help(cli));
        exit(1);
    }

    /* Accumulate compiler flags. */
    {
        char *cflags = chaz_Util_strdup("");
        size_t cflags_len = 0;
        for (i = 0; i < argc; i++) {
            if (strcmp(argv[i], "--") == 0) {
                i++;
                break;
            }
        }
        for (; i < argc; i++) {
            const char *arg = argv[i];
            cflags_len += strlen(arg) + 2;
            cflags = (char*)realloc(cflags, cflags_len);
            strcat(cflags, " ");
            strcat(cflags, arg);
        }
        chaz_CLI_set(cli, "cflags", cflags);
        free(cflags);
    }

    /* Some Perl setups have a 'cc' config value with leading whitespace. */
    if (chaz_CLI_defined(cli, "cc")) {
        const char *arg = chaz_CLI_strval(cli, "cc");
        char  *cc;
        size_t len = strlen(arg);
        size_t l   = 0;
        size_t r   = len;
        size_t trimmed_len;

        while (isspace((unsigned char)arg[l])) {
            ++l;
        }
        while (r > l && isspace((unsigned char)arg[r-1])) {
            --r;
        }

        trimmed_len = r - l;
        cc = (char*)malloc(trimmed_len + 1);
        memcpy(cc, arg + l, trimmed_len);
        cc[trimmed_len] = '\0';
        chaz_CLI_unset(cli, "cc");
        chaz_CLI_set(cli, "cc", cc);
        free(cc);
    }

    /* Validate. */
    if (!chaz_CLI_defined(cli, "cc")
        || !strlen(chaz_CLI_strval(cli, "cc"))
       ) {
        return false;
    }

    return true;
}

void
chaz_Probe_die_usage(void) {
    fprintf(stderr,
            "Usage: ./charmonize --cc=CC_COMMAND [--enable-c] "
            "[--enable-perl] [--enable-python] [--enable-ruby] -- CFLAGS\n");
    exit(1);
}

void
chaz_Probe_init(struct chaz_CLI *cli) {
    int output_enabled = 0;

    {
        /* Process CHARM_VERBOSITY environment variable. */
        const char *verbosity_env = getenv("CHARM_VERBOSITY");
        if (verbosity_env && strlen(verbosity_env)) {
            chaz_Util_verbosity = strtol(verbosity_env, NULL, 10);
        }
    }

    /* Dispatch other initializers. */
    chaz_OS_init();
    chaz_CC_init(chaz_CLI_strval(cli, "cc"), chaz_CLI_strval(cli, "cflags"));
    chaz_ConfWriter_init();
    chaz_HeadCheck_init();
    chaz_Make_init(cli);

    /* Enable output. */
    if (chaz_CLI_defined(cli, "enable-c")) {
        chaz_ConfWriterC_enable();
        output_enabled = true;
    }
    if (chaz_CLI_defined(cli, "enable-perl")) {
        chaz_ConfWriterPerl_enable();
        output_enabled = true;
    }
    if (chaz_CLI_defined(cli, "enable-python")) {
        chaz_ConfWriterPython_enable();
        output_enabled = true;
    }
    if (chaz_CLI_defined(cli, "enable-ruby")) {
        chaz_ConfWriterRuby_enable();
        output_enabled = true;
    }
    if (!output_enabled) {
        fprintf(stderr, "No output formats enabled\n");
        exit(1);
    }

    if (chaz_Util_verbosity) { printf("Initialization complete.\n"); }
}

void
chaz_Probe_clean_up(void) {
    if (chaz_Util_verbosity) { printf("Cleaning up...\n"); }

    /* Dispatch various clean up routines. */
    chaz_ConfWriter_clean_up();
    chaz_CC_clean_up();
    chaz_Make_clean_up();

    if (chaz_Util_verbosity) { printf("Cleanup complete.\n"); }
}

/***************************************************************************/

#line 17 "src/Charmonizer/Probe/AtomicOps.c"
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/AtomicOps.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void
chaz_AtomicOps_run(void) {
    chaz_ConfWriter_start_module("AtomicOps");

    if (chaz_HeadCheck_check_header("stdatomic.h")) {
        chaz_ConfWriter_add_def("HAS_STDATOMIC_H", NULL);
    }
    if (chaz_HeadCheck_check_header("libkern/OSAtomic.h")) {
        chaz_ConfWriter_add_def("HAS_LIBKERN_OSATOMIC_H", NULL);

        /* Check for OSAtomicCompareAndSwapPtr, introduced in later versions
         * of OSAtomic.h. */
        if (chaz_HeadCheck_defines_symbol("OSAtomicCompareAndSwapPtr",
                                          "#include <libkern/OSAtomic.h>")
           ) {
            chaz_ConfWriter_add_def("HAS_OSATOMIC_CAS_PTR", NULL);
        }
    }
    if (chaz_HeadCheck_check_header("sys/atomic.h")) {
        chaz_ConfWriter_add_def("HAS_SYS_ATOMIC_H", NULL);
    }
    if (chaz_HeadCheck_check_header("windows.h")
        && chaz_HeadCheck_check_header("intrin.h")
       ) {
        chaz_ConfWriter_add_def("HAS_INTRIN_H", NULL);
    }

    chaz_ConfWriter_end_module();
}




/***************************************************************************/

#line 17 "src/Charmonizer/Probe/Booleans.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Probe/Booleans.h" */

void
chaz_Booleans_run(void) {
    int has_stdbool = chaz_HeadCheck_check_header("stdbool.h");

    chaz_ConfWriter_start_module("Booleans");

    if (has_stdbool) {
        chaz_ConfWriter_add_def("HAS_STDBOOL_H", NULL);
        chaz_ConfWriter_add_sys_include("stdbool.h");
    }
    else {
        chaz_ConfWriter_append_conf(
            "#if (defined(CHY_EMPLOY_BOOLEANS) && !defined(__cplusplus))\n"
            "  typedef int bool;\n"
            "  #ifndef true\n"
            "    #define true 1\n"
            "  #endif\n"
            "  #ifndef false\n"
            "    #define false 0\n"
            "  #endif\n"
            "#endif\n");
    }

    chaz_ConfWriter_end_module();
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe/BuildEnv.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/CFlags.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Probe/BuildEnv.h" */

void
chaz_BuildEnv_run(void) {
    chaz_CFlags *extra_cflags = chaz_CC_get_extra_cflags();
    const char  *extra_cflags_string = chaz_CFlags_get_string(extra_cflags);

    chaz_ConfWriter_start_module("BuildEnv");

    chaz_ConfWriter_add_def("CC", chaz_CC_get_cc());
    chaz_ConfWriter_add_def("CFLAGS", chaz_CC_get_cflags());
    chaz_ConfWriter_add_def("EXTRA_CFLAGS", extra_cflags_string);

    chaz_ConfWriter_end_module();
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe/DirManip.c"
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/OperatingSystem.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Probe/DirManip.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static struct {
    int  mkdir_num_args;
    char mkdir_command[7];
} chaz_DirManip = { 0, "" };

/* Source code for rmdir. */
static int
chaz_DirManip_compile_posix_mkdir(const char *header) {
    static const char posix_mkdir_code[] =
        CHAZ_QUOTE(  #include <%s>                                      )
        CHAZ_QUOTE(  int main(int argc, char **argv) {                  )
        CHAZ_QUOTE(      if (argc != 2) { return 1; }                   )
        CHAZ_QUOTE(      if (mkdir(argv[1], 0777) != 0) { return 2; }   )
        CHAZ_QUOTE(      return 0;                                      )
        CHAZ_QUOTE(  }                                                  );
    char code_buf[sizeof(posix_mkdir_code) + 30];
    int mkdir_available;
    if (strlen(header) > 25) {
        chaz_Util_die("Header name too long: '%s'", header);
    }

    /* Attempt compilation. */
    sprintf(code_buf, posix_mkdir_code, header);
    mkdir_available = chaz_CC_test_compile(code_buf);

    /* Set vars on success. */
    if (mkdir_available) {
        strcpy(chaz_DirManip.mkdir_command, "mkdir");
        if (strcmp(header, "direct.h") == 0) {
            chaz_DirManip.mkdir_num_args = 1;
        }
        else {
            chaz_DirManip.mkdir_num_args = 2;
        }
    }

    return mkdir_available;
}

static int
chaz_DirManip_compile_win_mkdir(void) {
    static const char win_mkdir_code[] =
        CHAZ_QUOTE(  #include <direct.h>                                )
        CHAZ_QUOTE(  int main(int argc, char **argv) {                  )
        CHAZ_QUOTE(      if (argc != 2) { return 1; }                   )
        CHAZ_QUOTE(      if (_mkdir(argv[1]) != 0) { return 2; }        )
        CHAZ_QUOTE(      return 0;                                      )
        CHAZ_QUOTE(  }                                                  );
    int mkdir_available;

    mkdir_available = chaz_CC_test_compile(win_mkdir_code);
    if (mkdir_available) {
        strcpy(chaz_DirManip.mkdir_command, "_mkdir");
        chaz_DirManip.mkdir_num_args = 1;
    }
    return mkdir_available;
}

static void
chaz_DirManip_try_mkdir(void) {
    if (chaz_HeadCheck_check_header("windows.h")) {
        if (chaz_DirManip_compile_win_mkdir())               { return; }
        if (chaz_DirManip_compile_posix_mkdir("direct.h"))   { return; }
    }
    if (chaz_DirManip_compile_posix_mkdir("sys/stat.h")) { return; }
}

static int
chaz_DirManip_compile_rmdir(const char *header) {
    static const char rmdir_code[] =
        CHAZ_QUOTE(  #include <%s>                                      )
        CHAZ_QUOTE(  int main(int argc, char **argv) {                  )
        CHAZ_QUOTE(      if (argc != 2) { return 1; }                   )
        CHAZ_QUOTE(      if (rmdir(argv[1]) != 0) { return 2; }         )
        CHAZ_QUOTE(      return 0;                                      )
        CHAZ_QUOTE(  }                                                  );
    char code_buf[sizeof(rmdir_code) + 30];
    int rmdir_available;
    if (strlen(header) > 25) {
        chaz_Util_die("Header name too long: '%s'", header);
    }
    sprintf(code_buf, rmdir_code, header);
    rmdir_available = chaz_CC_test_compile(code_buf);
    return rmdir_available;
}

static void
chaz_DirManip_try_rmdir(void) {
    if (chaz_DirManip_compile_rmdir("unistd.h"))   { return; }
    if (chaz_DirManip_compile_rmdir("dirent.h"))   { return; }
    if (chaz_DirManip_compile_rmdir("direct.h"))   { return; }
}

void
chaz_DirManip_run(void) {
    int has_dirent_h = chaz_HeadCheck_check_header("dirent.h");
    int has_direct_h = chaz_HeadCheck_check_header("direct.h");
    int has_dirent_d_namlen = false;
    int has_dirent_d_type   = false;

    chaz_ConfWriter_start_module("DirManip");
    chaz_DirManip_try_mkdir();
    chaz_DirManip_try_rmdir();

    /* Header checks. */
    if (has_dirent_h) {
        chaz_ConfWriter_add_def("HAS_DIRENT_H", NULL);
    }
    if (has_direct_h) {
        chaz_ConfWriter_add_def("HAS_DIRECT_H", NULL);
    }

    /* Check for members in struct dirent. */
    if (has_dirent_h) {
        has_dirent_d_namlen = chaz_HeadCheck_contains_member(
                                  "struct dirent", "d_namlen",
                                  "#include <sys/types.h>\n#include <dirent.h>"
                              );
        if (has_dirent_d_namlen) {
            chaz_ConfWriter_add_def("HAS_DIRENT_D_NAMLEN", NULL);
        }
        has_dirent_d_type = chaz_HeadCheck_contains_member(
                                "struct dirent", "d_type",
                                "#include <sys/types.h>\n#include <dirent.h>"
                            );
        if (has_dirent_d_type) {
            chaz_ConfWriter_add_def("HAS_DIRENT_D_TYPE", NULL);
        }
    }

    if (chaz_DirManip.mkdir_num_args == 2) {
        /* It's two args, but the command isn't "mkdir". */
        char scratch[50];
        if (strlen(chaz_DirManip.mkdir_command) > 30) {
            chaz_Util_die("Command too long: '%s'", chaz_DirManip.mkdir_command);
        }
        sprintf(scratch, "%s(_dir, _mode)", chaz_DirManip.mkdir_command);
        chaz_ConfWriter_add_def("makedir(_dir, _mode)", scratch);
        chaz_ConfWriter_add_def("MAKEDIR_MODE_IGNORED", "0");
    }
    else if (chaz_DirManip.mkdir_num_args == 1) {
        /* It's one arg... mode arg will be ignored. */
        char scratch[50];
        if (strlen(chaz_DirManip.mkdir_command) > 30) {
            chaz_Util_die("Command too long: '%s'", chaz_DirManip.mkdir_command);
        }
        sprintf(scratch, "%s(_dir)", chaz_DirManip.mkdir_command);
        chaz_ConfWriter_add_def("makedir(_dir, _mode)", scratch);
        chaz_ConfWriter_add_def("MAKEDIR_MODE_IGNORED", "1");
    }

    if (chaz_CC_has_macro("_WIN32") && !chaz_CC_is_cygwin()) {
        chaz_ConfWriter_add_def("DIR_SEP", "\"\\\\\"");
        chaz_ConfWriter_add_def("DIR_SEP_CHAR", "'\\\\'");
    }
    else {
        chaz_ConfWriter_add_def("DIR_SEP", "\"/\"");
        chaz_ConfWriter_add_def("DIR_SEP_CHAR", "'/'");
    }

    /* See whether remove works on directories. */
    chaz_OS_mkdir("_charm_test_remove_me");
    if (0 == remove("_charm_test_remove_me")) {
        chaz_ConfWriter_add_def("REMOVE_ZAPS_DIRS", NULL);
    }
    chaz_OS_rmdir("_charm_test_remove_me");

    chaz_ConfWriter_end_module();
}




/***************************************************************************/

#line 17 "src/Charmonizer/Probe/Floats.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/CFlags.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/Floats.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void
chaz_Floats_run(void) {
    chaz_ConfWriter_start_module("Floats");

    chaz_ConfWriter_append_conf(
        "typedef union { unsigned char c[4]; float f; } chy_floatu32;\n"
        "typedef union { unsigned char c[8]; double d; } chy_floatu64;\n"
        "#ifdef CHY_BIG_END\n"
        "static const chy_floatu32 chy_f32inf\n"
        "    = { { 0x7F, 0x80, 0, 0 } };\n"
        "static const chy_floatu32 chy_f32neginf\n"
        "    = { { 0xFF, 0x80, 0, 0 } };\n"
        "static const chy_floatu32 chy_f32nan\n"
        "    = { { 0x7F, 0xC0, 0, 0 } };\n"
        "static const chy_floatu64 chy_f64inf\n"
        "    = { { 0x7F, 0xF0, 0, 0, 0, 0, 0, 0 } };\n"
        "static const chy_floatu64 chy_f64neginf\n"
        "    = { { 0xFF, 0xF0, 0, 0, 0, 0, 0, 0 } };\n"
        "static const chy_floatu64 chy_f64nan\n"
        "    = { { 0x7F, 0xF8, 0, 0, 0, 0, 0, 0 } };\n"
        "#else /* BIG_END */\n"
        "static const chy_floatu32 chy_f32inf\n"
        "    = { { 0, 0, 0x80, 0x7F } };\n"
        "static const chy_floatu32 chy_f32neginf\n"
        "    = { { 0, 0, 0x80, 0xFF } };\n"
        "static const chy_floatu32 chy_f32nan\n"
        "    = { { 0, 0, 0xC0, 0x7F } };\n"
        "static const chy_floatu64 chy_f64inf\n"
        "    = { { 0, 0, 0, 0, 0, 0, 0xF0, 0x7F } };\n"
        "static const chy_floatu64 chy_f64neginf\n"
        "    = { { 0, 0, 0, 0, 0, 0, 0xF0, 0xFF } };\n"
        "static const chy_floatu64 chy_f64nan\n"
        "    = { { 0, 0, 0, 0, 0, 0, 0xF8, 0x7F } };\n"
        "#endif /* BIG_END */\n"
    );
    chaz_ConfWriter_add_def("F32_INF", "(chy_f32inf.f)");
    chaz_ConfWriter_add_def("F32_NEGINF", "(chy_f32neginf.f)");
    chaz_ConfWriter_add_def("F32_NAN", "(chy_f32nan.f)");
    chaz_ConfWriter_add_def("F64_INF", "(chy_f64inf.d)");
    chaz_ConfWriter_add_def("F64_NEGINF", "(chy_f64neginf.d)");
    chaz_ConfWriter_add_def("F64_NAN", "(chy_f64nan.d)");

    chaz_ConfWriter_end_module();
}

const char*
chaz_Floats_math_library(void) {
    /*
     * The cast to a specific function pointer type is required because
     * C++ overloads sqrt.
     */
    static const char sqrt_code[] =
        CHAZ_QUOTE(  #include <math.h>                              )
        CHAZ_QUOTE(  typedef double (*sqrt_t)(double);              )
        CHAZ_QUOTE(  int main() { return (int)(sqrt_t)sqrt; }       );
    chaz_CFlags *temp_cflags = chaz_CC_get_temp_cflags();
    int success;

    if (chaz_CC_test_link(sqrt_code)) {
        /* Linking against libm not needed. */
        return NULL;
    }

    chaz_CFlags_add_external_lib(temp_cflags, "m");
    success = chaz_CC_test_link(sqrt_code);
    chaz_CFlags_clear(temp_cflags);

    if (!success) {
        chaz_Util_die("Don't know how to use math library.");
    }

    return "m";
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe/FuncMacro.c"
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/FuncMacro.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Attempt to verify inline keyword. */
static int
chaz_FuncMacro_try_inline(const char *keyword) {
    static const char inline_code[] = "static %s int f() { return 1; }";
    char code[sizeof(inline_code) + 30];
    sprintf(code, inline_code, keyword);
    return chaz_CC_test_compile(code);
}

static void
chaz_FuncMacro_probe_inline(void) {
    static const char* inline_options[] = {
        "__inline",
        "__inline__",
        "inline"
    };
    const int num_inline_options = sizeof(inline_options) / sizeof(void*);
    int has_inline = false;
    int i;

    for (i = 0; i < num_inline_options; i++) {
        const char *inline_option = inline_options[i];
        if (chaz_FuncMacro_try_inline(inline_option)) {
            has_inline = true;
            chaz_ConfWriter_add_def("INLINE", inline_option);
            break;
        }
    }
    if (!has_inline) {
        chaz_ConfWriter_add_def("INLINE", NULL);
    }
}

void
chaz_FuncMacro_run(void) {
    int has_funcmac      = false;
    int has_iso_funcmac  = false;
    int has_gnuc_funcmac = false;

    chaz_ConfWriter_start_module("FuncMacro");

    /* Check for func macros. */
    if (chaz_CC_test_compile("const char *f() { return __func__; }")) {
        has_funcmac     = true;
        has_iso_funcmac = true;
    }
    if (chaz_CC_test_compile("const char *f() { return __FUNCTION__; }")) {
        has_funcmac      = true;
        has_gnuc_funcmac = true;
    }

    /* Write out common defines. */
    if (has_funcmac) {
        const char *macro_text = has_iso_funcmac
                                 ? "__func__"
                                 : "__FUNCTION__";
        chaz_ConfWriter_add_def("HAS_FUNC_MACRO", NULL);
        chaz_ConfWriter_add_def("FUNC_MACRO", macro_text);
    }

    /* Write out specific defines. */
    if (has_iso_funcmac) {
        chaz_ConfWriter_add_def("HAS_ISO_FUNC_MACRO", NULL);
    }
    if (has_gnuc_funcmac) {
        chaz_ConfWriter_add_def("HAS_GNUC_FUNC_MACRO", NULL);
    }

    /* Check for inline keyword. */
    chaz_FuncMacro_probe_inline();

    chaz_ConfWriter_end_module();
}




/***************************************************************************/

#line 17 "src/Charmonizer/Probe/Headers.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/Headers.h" */
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define CHAZ_HEADERS_MAX_KEEPERS 200

static struct {
    int keeper_count;
    const char *keepers[CHAZ_HEADERS_MAX_KEEPERS + 1];
} chaz_Headers = { 0, { NULL } };

/* Add a header to the keepers array.
 */
static void
chaz_Headers_keep(const char *header_name);

/* Transform "header.h" into "CHY_HAS_HEADER_H, storing the result into
 * `buffer`.
 */
static void
chaz_Headers_encode_affirmation(const char *header_name, char *buffer,
                                size_t buf_size);

/* Probe for all C89 headers. */
static void
chaz_Headers_probe_c89(void);

/* Probe for all POSIX headers. */
static void
chaz_Headers_probe_posix(void);

/* Prove for selected Windows headers. */
static void
chaz_Headers_probe_win(void);

int
chaz_Headers_check(const char *header_name) {
    return chaz_HeadCheck_check_header(header_name);
}

void
chaz_Headers_run(void) {
    int i;

    chaz_ConfWriter_start_module("Headers");

    chaz_Headers_probe_posix();
    chaz_Headers_probe_c89();
    chaz_Headers_probe_win();

    /* One-offs. */
    if (chaz_HeadCheck_check_header("pthread.h")) {
        chaz_Headers_keep("pthread.h");
    }

    /* Append the config with every header detected so far. */
    for (i = 0; chaz_Headers.keepers[i] != NULL; i++) {
        char aff_buf[200];
        chaz_Headers_encode_affirmation(chaz_Headers.keepers[i], aff_buf, 200);
        chaz_ConfWriter_add_def(aff_buf, NULL);
    }

    chaz_ConfWriter_end_module();
}

static void
chaz_Headers_keep(const char *header_name) {
    if (chaz_Headers.keeper_count >= CHAZ_HEADERS_MAX_KEEPERS) {
        chaz_Util_die("Too many keepers -- increase MAX_KEEPER_COUNT");
    }
    chaz_Headers.keepers[chaz_Headers.keeper_count++] = header_name;
    chaz_Headers.keepers[chaz_Headers.keeper_count]   = NULL;
}

static void
chaz_Headers_encode_affirmation(const char *header_name, char *buffer, size_t buf_size) {
    char *buf, *buf_end;
    size_t len = strlen(header_name) + sizeof("HAS_");
    if (len + 1 > buf_size) {
        chaz_Util_die("Buffer too small: %lu", (unsigned long)buf_size);
    }

    /* Start off with "HAS_". */
    strcpy(buffer, "HAS_");

    /* Transform one char at a time. */
    for (buf = buffer + sizeof("HAS_") - 1, buf_end = buffer + len;
         buf < buf_end;
         header_name++, buf++
        ) {
        if (*header_name == '\0') {
            *buf = '\0';
            break;
        }
        else if (isalnum((unsigned char)*header_name)) {
            *buf = toupper((unsigned char)*header_name);
        }
        else {
            *buf = '_';
        }
    }
}

static void
chaz_Headers_probe_c89(void) {
    const char *c89_headers[] = {
        "assert.h",
        "ctype.h",
        "errno.h",
        "float.h",
        "limits.h",
        "locale.h",
        "math.h",
        "setjmp.h",
        "signal.h",
        "stdarg.h",
        "stddef.h",
        "stdio.h",
        "stdlib.h",
        "string.h",
        "time.h",
        NULL
    };
    int i;

    /* Test for all c89 headers in one blast. */
    if (chaz_HeadCheck_check_many_headers((const char**)c89_headers)) {
        chaz_ConfWriter_add_def("HAS_C89", NULL);
        chaz_ConfWriter_add_def("HAS_C90", NULL);
        for (i = 0; c89_headers[i] != NULL; i++) {
            chaz_Headers_keep(c89_headers[i]);
        }
    }
    /* Test one-at-a-time. */
    else {
        for (i = 0; c89_headers[i] != NULL; i++) {
            if (chaz_HeadCheck_check_header(c89_headers[i])) {
                chaz_Headers_keep(c89_headers[i]);
            }
        }
    }
}

static void
chaz_Headers_probe_posix(void) {
    const char *posix_headers[] = {
        "cpio.h",
        "dirent.h",
        "fcntl.h",
        "grp.h",
        "pwd.h",
        "regex.h",
        "sched.h",
        "sys/stat.h",
        "sys/time.h",
        "sys/times.h",
        "sys/types.h",
        "sys/utsname.h",
        "sys/wait.h",
        "tar.h",
        "termios.h",
        "unistd.h",
        "utime.h",
        NULL
    };
    int i;

    /* Try for all POSIX headers in one blast. */
    if (chaz_HeadCheck_check_many_headers((const char**)posix_headers)) {
        chaz_ConfWriter_add_def("HAS_POSIX", NULL);
        for (i = 0; posix_headers[i] != NULL; i++) {
            chaz_Headers_keep(posix_headers[i]);
        }
    }
    /* Test one-at-a-time. */
    else {
        for (i = 0; posix_headers[i] != NULL; i++) {
            if (chaz_HeadCheck_check_header(posix_headers[i])) {
                chaz_Headers_keep(posix_headers[i]);
            }
        }
    }
}


static void
chaz_Headers_probe_win(void) {
    const char *win_headers[] = {
        "io.h",
        "windows.h",
        "process.h",
        NULL
    };
    int i;

    /* Test for all Windows headers in one blast */
    if (chaz_HeadCheck_check_many_headers((const char**)win_headers)) {
        for (i = 0; win_headers[i] != NULL; i++) {
            chaz_Headers_keep(win_headers[i]);
        }
    }
    /* Test one-at-a-time. */
    else {
        for (i = 0; win_headers[i] != NULL; i++) {
            if (chaz_HeadCheck_check_header(win_headers[i])) {
                chaz_Headers_keep(win_headers[i]);
            }
        }
    }
}


/***************************************************************************/

#line 17 "src/Charmonizer/Probe/Integers.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/Integers.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Determine endian-ness of this machine.
 */
static int
chaz_Integers_machine_is_big_endian(void);

static const char chaz_Integers_stdint_type_code[] =
    CHAZ_QUOTE(  #include <stdint.h>                       )
    CHAZ_QUOTE(  %s i;                                     );

static const char chaz_Integers_literal64_code[] =
    CHAZ_QUOTE(  int f() { return (int)9000000000000000000%s; }  );

void
chaz_Integers_run(void) {
    char *output;
    size_t output_len;
    int sizeof_char       = -1;
    int sizeof_short      = -1;
    int sizeof_int        = -1;
    int sizeof_ptr        = -1;
    int sizeof_long       = -1;
    int sizeof_long_long  = -1;
    int sizeof___int64    = -1;
    int sizeof_size_t     = -1;
    int has_8             = false;
    int has_16            = false;
    int has_32            = false;
    int has_64            = false;
    int has_long_long     = false;
    int has___int64       = false;
    int has_intptr_t      = false;
    int has_inttypes      = chaz_HeadCheck_check_header("inttypes.h");
    int has_stdint        = chaz_HeadCheck_check_header("stdint.h");
    char i32_t_type[10];
    char i32_t_postfix[10];
    char u32_t_postfix[10];
    char i64_t_type[10];
    char i64_t_postfix[10];
    char u64_t_postfix[10];
    char printf_modifier_32[10];
    char printf_modifier_64[10];
    char code_buf[1000];
    char scratch[50];

    chaz_ConfWriter_start_module("Integers");

    /* Document endian-ness. */
    if (chaz_Integers_machine_is_big_endian()) {
        chaz_ConfWriter_add_def("BIG_END", NULL);
    }
    else {
        chaz_ConfWriter_add_def("LITTLE_END", NULL);
    }

    /* Record sizeof() for several common integer types. */
    sizeof_char   = chaz_HeadCheck_size_of_type("char",  "", 1);
    sizeof_short  = chaz_HeadCheck_size_of_type("short", "", 2);
    sizeof_int    = chaz_HeadCheck_size_of_type("int",   "", 4);
    sizeof_long   = chaz_HeadCheck_size_of_type("long",  "", 4);
    sizeof_ptr    = chaz_HeadCheck_size_of_type("void*", "", 4);
    sizeof_size_t = chaz_HeadCheck_size_of_type("size_t",
                                                "#include <stddef.h>", 4);

    /* Determine whether long longs are available. */
    if (chaz_CC_test_compile("long long l;")) {
        has_long_long    = true;
        sizeof_long_long = chaz_HeadCheck_size_of_type("long long", "", 8);
    }

    /* Determine whether the __int64 type is available. */
    if (chaz_CC_test_compile("__int64 i;")) {
        has___int64 = true;
        sizeof___int64 = chaz_HeadCheck_size_of_type("__int64", "", 8);
    }

    /* Determine whether the intptr_t type is available (it's optional in
     * C99). */
    sprintf(code_buf, chaz_Integers_stdint_type_code, "intptr_t");
    if (chaz_CC_test_compile(code_buf)) {
        has_intptr_t = true;
    }

    /* Figure out which integer types are available. */
    if (sizeof_char == 1) {
        has_8 = true;
    }
    if (sizeof_short == 2) {
        has_16 = true;
    }
    if (sizeof_int == 4) {
        has_32 = true;
        strcpy(i32_t_type, "int");
        strcpy(i32_t_postfix, "");
        strcpy(u32_t_postfix, "U");
        strcpy(printf_modifier_32, "");
    }
    else if (sizeof_long == 4) {
        has_32 = true;
        strcpy(i32_t_type, "long");
        strcpy(i32_t_postfix, "L");
        strcpy(u32_t_postfix, "UL");
        strcpy(printf_modifier_32, "l");
    }
    if (sizeof_long == 8) {
        has_64 = true;
        strcpy(i64_t_type, "long");
    }
    else if (sizeof_long_long == 8) {
        has_64 = true;
        strcpy(i64_t_type, "long long");
    }
    else if (sizeof___int64 == 8) {
        has_64 = true;
        strcpy(i64_t_type, "__int64");
    }

    /* Probe for 64-bit literal syntax. */
    if (has_64 && sizeof_long == 8) {
        strcpy(i64_t_postfix, "L");
        strcpy(u64_t_postfix, "UL");
    }
    else if (has_64) {
        sprintf(code_buf, chaz_Integers_literal64_code, "LL");
        if (chaz_CC_test_compile(code_buf)) {
            strcpy(i64_t_postfix, "LL");
        }
        else {
            sprintf(code_buf, chaz_Integers_literal64_code, "i64");
            if (chaz_CC_test_compile(code_buf)) {
                strcpy(i64_t_postfix, "i64");
            }
            else {
                chaz_Util_die("64-bit types, but no literal syntax found");
            }
        }
        sprintf(code_buf, chaz_Integers_literal64_code, "ULL");
        if (chaz_CC_test_compile(code_buf)) {
            strcpy(u64_t_postfix, "ULL");
        }
        else {
            sprintf(code_buf, chaz_Integers_literal64_code, "Ui64");
            if (chaz_CC_test_compile(code_buf)) {
                strcpy(u64_t_postfix, "Ui64");
            }
            else {
                chaz_Util_die("64-bit types, but no literal syntax found");
            }
        }
    }

    /* Write out some conditional defines. */
    if (has_inttypes) {
        chaz_ConfWriter_add_def("HAS_INTTYPES_H", NULL);
    }
    if (has_stdint) {
        chaz_ConfWriter_add_def("HAS_STDINT_H", NULL);
    }
    if (has_long_long) {
        chaz_ConfWriter_add_def("HAS_LONG_LONG", NULL);
    }
    if (has___int64) {
        chaz_ConfWriter_add_def("HAS___INT64", NULL);
    }

    /* Write out sizes. */
    sprintf(scratch, "%d", sizeof_char);
    chaz_ConfWriter_add_def("SIZEOF_CHAR", scratch);
    sprintf(scratch, "%d", sizeof_short);
    chaz_ConfWriter_add_def("SIZEOF_SHORT", scratch);
    sprintf(scratch, "%d", sizeof_int);
    chaz_ConfWriter_add_def("SIZEOF_INT", scratch);
    sprintf(scratch, "%d", sizeof_long);
    chaz_ConfWriter_add_def("SIZEOF_LONG", scratch);
    sprintf(scratch, "%d", sizeof_ptr);
    chaz_ConfWriter_add_def("SIZEOF_PTR", scratch);
    sprintf(scratch, "%d", sizeof_size_t);
    chaz_ConfWriter_add_def("SIZEOF_SIZE_T", scratch);
    if (has_long_long) {
        sprintf(scratch, "%d", sizeof_long_long);
        chaz_ConfWriter_add_def("SIZEOF_LONG_LONG", scratch);
    }
    if (has___int64) {
        sprintf(scratch, "%d", sizeof___int64);
        chaz_ConfWriter_add_def("SIZEOF___INT64", scratch);
    }

    /* Write affirmations. */
    if (has_8) {
        chaz_ConfWriter_add_def("HAS_INT8_T", NULL);
    }
    if (has_16) {
        chaz_ConfWriter_add_def("HAS_INT16_T", NULL);
    }
    if (has_32) {
        chaz_ConfWriter_add_def("HAS_INT32_T", NULL);
    }
    if (has_64) {
        chaz_ConfWriter_add_def("HAS_INT64_T", NULL);
    }

    /* Create macro for promoting pointers to integers. */
    if (has_64) {
        if (sizeof_ptr == 8) {
            chaz_ConfWriter_add_def("PTR_TO_I64(ptr)",
                                    "((int64_t)(uint64_t)(ptr))");
        }
        else {
            chaz_ConfWriter_add_def("PTR_TO_I64(ptr)",
                                    "((int64_t)(uint32_t)(ptr))");
        }
    }

    chaz_ConfWriter_end_module();

    /* Integer typedefs. */

    chaz_ConfWriter_start_module("IntegerTypes");

    if (has_stdint) {
        chaz_ConfWriter_add_sys_include("stdint.h");
    }
    else {
        /* We support only the following subset of stdint.h
         *   int8_t
         *   int16_t
         *   int32_t
         *   int64_t
         *   intmax_t
         *   intptr_t
         *   uint8_t
         *   uint16_t
         *   uint32_t
         *   uint64_t
         *   uintmax_t
         *   uintptr_t
         */
        if (has_8) {
            chaz_ConfWriter_add_global_typedef("signed char", "int8_t");
            chaz_ConfWriter_add_global_typedef("unsigned char", "uint8_t");
        }
        if (has_16) {
            chaz_ConfWriter_add_global_typedef("signed short", "int16_t");
            chaz_ConfWriter_add_global_typedef("unsigned short", "uint16_t");
        }
        if (has_32) {
            chaz_ConfWriter_add_global_typedef(i32_t_type, "int32_t");
            sprintf(scratch, "unsigned %s", i32_t_type);
            chaz_ConfWriter_add_global_typedef(scratch, "uint32_t");
        }
        if (has_64) {
            chaz_ConfWriter_add_global_typedef(i64_t_type, "int64_t");
            sprintf(scratch, "unsigned %s", i64_t_type);
            chaz_ConfWriter_add_global_typedef(scratch, "uint64_t");
        }

        if (has_64) {
            chaz_ConfWriter_add_global_typedef(i64_t_type, "intmax_t");
            sprintf(scratch, "unsigned %s", i64_t_type);
            chaz_ConfWriter_add_global_typedef(scratch, "uintmax_t");
        }
        else if (has_32) {
            chaz_ConfWriter_add_global_typedef(i32_t_type, "intmax_t");
            sprintf(scratch, "unsigned %s", i32_t_type);
            chaz_ConfWriter_add_global_typedef(scratch, "uintmax_t");
        }
    }

    if (!has_intptr_t) {
        if (sizeof_ptr == 4) {
            chaz_ConfWriter_add_global_typedef(i32_t_type, "intptr_t");
            sprintf(scratch, "unsigned %s", i32_t_type);
            chaz_ConfWriter_add_global_typedef(scratch, "uintptr_t");
        }
        else if (sizeof_ptr == 8) {
            chaz_ConfWriter_add_global_typedef(i64_t_type, "intptr_t");
            sprintf(scratch, "unsigned %s", i64_t_type);
            chaz_ConfWriter_add_global_typedef(scratch, "uintptr_t");
        }
    }

    chaz_ConfWriter_end_module();

    /* Integer limits. */

    chaz_ConfWriter_start_module("IntegerLimits");

    if (has_stdint) {
        chaz_ConfWriter_add_sys_include("stdint.h");
    }
    else {
        /* We support only the following subset of stdint.h
         *   INT8_MAX
         *   INT16_MAX
         *   INT32_MAX
         *   INT64_MAX
         *   INTMAX_MAX
         *   INTPTR_MAX
         *   INT8_MIN
         *   INT16_MIN
         *   INT32_MIN
         *   INT64_MIN
         *   INTMAX_MIN
         *   INTPTR_MIN
         *   UINT8_MAX
         *   UINT16_MAX
         *   UINT32_MAX
         *   UINT64_MAX
         *   UINTMAX_MAX
         *   UINTPTR_MAX
         *   SIZE_MAX
         */
        if (has_8) {
            chaz_ConfWriter_add_global_def("INT8_MAX", "127");
            chaz_ConfWriter_add_global_def("INT8_MIN", "-128");
            chaz_ConfWriter_add_global_def("UINT8_MAX", "255");
        }
        if (has_16) {
            chaz_ConfWriter_add_global_def("INT16_MAX", "32767");
            chaz_ConfWriter_add_global_def("INT16_MIN", "-32768");
            chaz_ConfWriter_add_global_def("UINT16_MAX", "65535");
        }
        if (has_32) {
            chaz_ConfWriter_add_global_def("INT32_MAX", "2147483647");
            chaz_ConfWriter_add_global_def("INT32_MIN", "(-2147483647-1)");
            chaz_ConfWriter_add_global_def("UINT32_MAX", "4294967295U");
        }
        if (has_64) {
            sprintf(scratch, "9223372036854775807%s", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INT64_MAX", scratch);
            sprintf(scratch, "(-9223372036854775807%s-1)", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INT64_MIN", scratch);
            sprintf(scratch, "18446744073709551615%s", u64_t_postfix);
            chaz_ConfWriter_add_global_def("UINT64_MAX", scratch);
        }

        if (has_64) {
            sprintf(scratch, "9223372036854775807%s", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INTMAX_MAX", scratch);
            sprintf(scratch, "(-9223372036854775807%s-1)", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INTMAX_MIN", scratch);
            sprintf(scratch, "18446744073709551615%s", u64_t_postfix);
            chaz_ConfWriter_add_global_def("UINTMAX_MAX", scratch);
        }
        else if (has_32) {
            chaz_ConfWriter_add_global_def("INTMAX_MAX", "2147483647");
            chaz_ConfWriter_add_global_def("INTMAX_MIN", "(-2147483647-1)");
            chaz_ConfWriter_add_global_def("UINTMAX_MAX", "4294967295U");
        }

        chaz_ConfWriter_add_global_def("SIZE_MAX", "((size_t)-1)");
    }

    if (!has_intptr_t) {
        if (sizeof_ptr == 4) {
            chaz_ConfWriter_add_global_def("INTPTR_MAX", "2147483647");
            chaz_ConfWriter_add_global_def("INTPTR_MIN", "(-2147483647-1)");
            chaz_ConfWriter_add_global_def("UINTPTR_MAX", "4294967295U");
        }
        else if (sizeof_ptr == 8) {
            sprintf(scratch, "9223372036854775807%s", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INTPTR_MAX", scratch);
            sprintf(scratch, "(-9223372036854775807%s-1)", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INTPTR_MIN", scratch);
            sprintf(scratch, "18446744073709551615%s", u64_t_postfix);
            chaz_ConfWriter_add_global_def("UINTPTR_MAX", scratch);
        }
    }

    chaz_ConfWriter_end_module();

    /* Integer literals. */

    chaz_ConfWriter_start_module("IntegerLiterals");

    if (has_stdint) {
        chaz_ConfWriter_add_sys_include("stdint.h");
    }
    else {
        /* We support only the following subset of stdint.h
         *   INT32_C
         *   INT64_C
         *   INTMAX_C
         *   UINT32_C
         *   UINT64_C
         *   UINTMAX_C
         */
        if (has_32) {
            if (strcmp(i32_t_postfix, "") == 0) {
                chaz_ConfWriter_add_global_def("INT32_C(n)", "n");
            }
            else {
                sprintf(scratch, "n##%s", i32_t_postfix);
                chaz_ConfWriter_add_global_def("INT32_C(n)", scratch);
            }
            sprintf(scratch, "n##%s", u32_t_postfix);
            chaz_ConfWriter_add_global_def("UINT32_C(n)", scratch);
        }
        if (has_64) {
            sprintf(scratch, "n##%s", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INT64_C(n)", scratch);
            sprintf(scratch, "n##%s", u64_t_postfix);
            chaz_ConfWriter_add_global_def("UINT64_C(n)", scratch);
        }

        if (has_64) {
            sprintf(scratch, "n##%s", i64_t_postfix);
            chaz_ConfWriter_add_global_def("INTMAX_C(n)", scratch);
            sprintf(scratch, "n##%s", u64_t_postfix);
            chaz_ConfWriter_add_global_def("UINTMAX_C(n)", scratch);
        }
        else if (has_32) {
            if (strcmp(i32_t_postfix, "") == 0) {
                chaz_ConfWriter_add_global_def("INTMAX_C(n)", "n");
            }
            else {
                sprintf(scratch, "n##%s", i32_t_postfix);
                chaz_ConfWriter_add_global_def("INTMAX_C(n)", scratch);
            }
            sprintf(scratch, "n##%s", u32_t_postfix);
            chaz_ConfWriter_add_global_def("UINTMAX_C(n)", scratch);
        }
    }

    chaz_ConfWriter_end_module();

    /* Integer format strings. */

    chaz_ConfWriter_start_module("IntegerFormatStrings");

    if (has_inttypes) {
        if (chaz_CC_is_mingw()) {
            /* Suppress warnings about undefined inline function `llabs`
             * under MinGW.
             */
            chaz_ConfWriter_add_sys_include("stdlib.h");
        }
        chaz_ConfWriter_add_sys_include("inttypes.h");
    }

    /* Probe for 64-bit printf format string modifier. */
    if (!has_inttypes && has_64) {
        int i;
        const char *options[] = {
            "ll",
            "l",
            "L",
            "q",   /* Some *BSDs */
            "I64", /* Microsoft */
            NULL,
        };

        /* Buffer to hold the code, and its start and end. */
        static const char format_64_code[] =
            CHAZ_QUOTE(  #include <stdio.h>                            )
            CHAZ_QUOTE(  int main() {                                  )
            CHAZ_QUOTE(      printf("%%%su", 18446744073709551615%s);  )
            CHAZ_QUOTE(      return 0;                                 )
            CHAZ_QUOTE( }                                              );

        for (i = 0; options[i] != NULL; i++) {
            /* Try to print 2**64-1, and see if we get it back intact. */
            int success;
            sprintf(code_buf, format_64_code, options[i], u64_t_postfix);
            output = chaz_CC_capture_output(code_buf, &output_len);
            success = output != NULL
                      && strcmp(output, "18446744073709551615") == 0;
            free(output);

            if (success) {
                break;
            }
        }

        if (options[i] == NULL) {
            chaz_Util_die("64-bit types, but no printf modifier found");
        }

        strcpy(printf_modifier_64, options[i]);
    }

    if (!has_inttypes || !has_intptr_t) {
        /* We support only the following subset of inttypes.h
         *   PRId32
         *   PRIi32
         *   PRIo32
         *   PRIu32
         *   PRIx32
         *   PRIX32
         *   PRId64
         *   PRIi64
         *   PRIo64
         *   PRIu64
         *   PRIx64
         *   PRIX64
         *   PRIdMAX
         *   PRIiMAX
         *   PRIoMAX
         *   PRIuMAX
         *   PRIxMAX
         *   PRIXMAX
         *   PRIdPTR
         *   PRIiPTR
         *   PRIoPTR
         *   PRIuPTR
         *   PRIxPTR
         *   PRIXPTR
         */
        const char *ptr;
        char macro_name_32[]  = "PRI.32";
        char macro_name_64[]  = "PRI.64";
        char macro_name_max[] = "PRI.MAX";
        char macro_name_ptr[] = "PRI.PTR";

        for (ptr = "diouxX"; ptr[0] != '\0'; ptr++) {
            int c = ptr[0];

            if (has_32) {
                macro_name_32[3] = c;
                if (!has_inttypes) {
                    sprintf(scratch, "\"%s%c\"", printf_modifier_32, c);
                    chaz_ConfWriter_add_global_def(macro_name_32, scratch);
                    if (!has_64) {
                        macro_name_max[3] = c;
                        chaz_ConfWriter_add_global_def(macro_name_max,
                                                       scratch);
                    }
                }
                if (!has_intptr_t && sizeof_ptr == 4) {
                    macro_name_ptr[3] = c;
                    chaz_ConfWriter_add_global_def(macro_name_ptr,
                                                   macro_name_32);
                }
            }
            if (has_64) {
                macro_name_64[3] = c;
                if (!has_inttypes) {
                    sprintf(scratch, "\"%s%c\"", printf_modifier_64, c);
                    chaz_ConfWriter_add_global_def(macro_name_64, scratch);
                    macro_name_max[3] = c;
                    chaz_ConfWriter_add_global_def(macro_name_max, scratch);
                }
                if (!has_intptr_t && sizeof_ptr == 8) {
                    macro_name_ptr[3] = c;
                    chaz_ConfWriter_add_global_def(macro_name_ptr,
                                                   macro_name_64);
                }
            }
        }
    }

    chaz_ConfWriter_end_module();
}

static int
chaz_Integers_machine_is_big_endian(void) {
    long one = 1;
    return !(*((char*)(&one)));
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe/LargeFiles.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/LargeFiles.h" */
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Module vars. */
static struct {
    char off64_type[10];
} chaz_LargeFiles = { "" };

/* Sets of symbols which might provide large file support for stdio. */
typedef struct chaz_LargeFiles_stdio64_combo {
    const char *includes;
    const char *fopen_command;
    const char *ftell_command;
    const char *fseek_command;
} chaz_LargeFiles_stdio64_combo;

/* Sets of symbols which might provide large file support for unbuffered i/o.
 */
typedef struct chaz_LargeFiles_unbuff_combo {
    const char *includes;
    const char *lseek_command;
    const char *pread64_command;
} chaz_LargeFiles_unbuff_combo;

/* Check for a 64-bit file pointer type.
 */
static int
chaz_LargeFiles_probe_off64(void);

/* Check what name 64-bit ftell, fseek go by.
 */
static void
chaz_LargeFiles_probe_stdio64(void);
static int
chaz_LargeFiles_try_stdio64(chaz_LargeFiles_stdio64_combo *combo);

/* Probe for 64-bit unbuffered i/o.
 */
static void
chaz_LargeFiles_probe_unbuff(void);

/* Check for a 64-bit lseek.
 */
static int
chaz_LargeFiles_probe_lseek(chaz_LargeFiles_unbuff_combo *combo);

/* Check for a 64-bit pread.
 */
static int
chaz_LargeFiles_probe_pread64(chaz_LargeFiles_unbuff_combo *combo);

void
chaz_LargeFiles_run(void) {
    int found_off64_t = false;
    const char *stat_includes = "#include <stdio.h>\n#include <sys/stat.h>";

    chaz_ConfWriter_start_module("LargeFiles");

    /* Find off64_t or equivalent. */
    found_off64_t = chaz_LargeFiles_probe_off64();
    if (found_off64_t) {
        chaz_ConfWriter_add_def("HAS_64BIT_OFFSET_TYPE", NULL);
        chaz_ConfWriter_add_def("off64_t",  chaz_LargeFiles.off64_type);
    }

    /* See if stdio variants with 64-bit support exist. */
    chaz_LargeFiles_probe_stdio64();

    /* Probe for 64-bit versions of lseek and pread (if we have an off64_t). */
    if (found_off64_t) {
        chaz_LargeFiles_probe_unbuff();
    }

    /* Make checks needed for testing. */
    if (chaz_HeadCheck_check_header("sys/stat.h")) {
        chaz_ConfWriter_append_conf("#define CHAZ_HAS_SYS_STAT_H\n");
    }
    if (chaz_HeadCheck_check_header("io.h")) {
        chaz_ConfWriter_append_conf("#define CHAZ_HAS_IO_H\n");
    }
    if (chaz_HeadCheck_check_header("fcntl.h")) {
        chaz_ConfWriter_append_conf("#define CHAZ_HAS_FCNTL_H\n");
    }
    if (chaz_HeadCheck_contains_member("struct stat", "st_size", stat_includes)) {
        chaz_ConfWriter_append_conf("#define CHAZ_HAS_STAT_ST_SIZE\n");
    }
    if (chaz_HeadCheck_contains_member("struct stat", "st_blocks", stat_includes)) {
        chaz_ConfWriter_append_conf("#define CHAZ_HAS_STAT_ST_BLOCKS\n");
    }

    chaz_ConfWriter_end_module();
}

static int
chaz_LargeFiles_probe_off64(void) {
    static const char off64_code[] =
        CHAZ_QUOTE(  %s                                        )
        CHAZ_QUOTE(  int a[sizeof(%s)==8?1:-1];                );
    char code_buf[sizeof(off64_code) + 100];
    int i;
    int success = false;
    static const char* off64_options[] = {
        "off64_t",
        "off_t",
        "__int64",
        "long"
    };
    int num_off64_options = sizeof(off64_options) / sizeof(off64_options[0]);

    for (i = 0; i < num_off64_options; i++) {
        const char *candidate = off64_options[i];
        int has_sys_types_h = chaz_HeadCheck_check_header("sys/types.h");
        const char *sys_types_include = has_sys_types_h
                                        ? "#include <sys/types.h>"
                                        : "";

        /* Execute the probe. */
        sprintf(code_buf, off64_code, sys_types_include, candidate);
        if (chaz_CC_test_compile(code_buf)) {
            strcpy(chaz_LargeFiles.off64_type, candidate);
            success = true;
            break;
        }
    }
    return success;
}

static int
chaz_LargeFiles_try_stdio64(chaz_LargeFiles_stdio64_combo *combo) {
    static const char stdio64_code[] =
        CHAZ_QUOTE(  %s                                         )
        CHAZ_QUOTE(  #include <stdio.h>                         )
        CHAZ_QUOTE(  int a[sizeof(%s)==8?1:-1];                 )
        CHAZ_QUOTE(  int main() {                               )
        CHAZ_QUOTE(      FILE *f = %s("_charm_stdio64", "w");   )
        CHAZ_QUOTE(      %s pos = %s(f);                        )
        CHAZ_QUOTE(      %s(f, 0, SEEK_SET);                    )
        CHAZ_QUOTE(      return 0;                              )
        CHAZ_QUOTE(  }                                          );
    char code_buf[sizeof(stdio64_code) + 200];

    /* Prepare the source code. */
    sprintf(code_buf, stdio64_code, combo->includes,
            chaz_LargeFiles.off64_type, combo->fopen_command,
            chaz_LargeFiles.off64_type, combo->ftell_command,
            combo->fseek_command);

    /* Verify compilation and that the offset type has 8 bytes. */
    return chaz_CC_test_link(code_buf);
}

static void
chaz_LargeFiles_probe_stdio64(void) {
    int i;
    static chaz_LargeFiles_stdio64_combo stdio64_combos[] = {
        { "#include <sys/types.h>\n", "fopen64",   "ftello64",  "fseeko64"  },
        { "#include <sys/types.h>\n", "fopen",     "ftello64",  "fseeko64"  },
        { "#include <sys/types.h>\n", "fopen",     "ftello",    "fseeko"    },
        { "",                         "fopen",     "ftell",     "fseek"     },
        { "",                         "fopen",     "_ftelli64", "_fseeki64" },
        { "",                         "fopen",     "ftell",     "fseek"     },
        { NULL, NULL, NULL, NULL }
    };

    for (i = 0; stdio64_combos[i].includes != NULL; i++) {
        chaz_LargeFiles_stdio64_combo combo = stdio64_combos[i];
        if (chaz_LargeFiles_try_stdio64(&combo)) {
            chaz_ConfWriter_add_def("HAS_64BIT_STDIO", NULL);
            chaz_ConfWriter_add_def("fopen64",  combo.fopen_command);
            chaz_ConfWriter_add_def("ftello64", combo.ftell_command);
            chaz_ConfWriter_add_def("fseeko64", combo.fseek_command);
            break;
        }
    }
}

static int
chaz_LargeFiles_probe_lseek(chaz_LargeFiles_unbuff_combo *combo) {
    static const char lseek_code[] =
        CHAZ_QUOTE( %s                                      )
        CHAZ_QUOTE( int main() {                            )
        CHAZ_QUOTE(     %s(0, 0, SEEK_SET);                 )
        CHAZ_QUOTE(     return 0;                           )
        CHAZ_QUOTE( }                                       );
    char code_buf[sizeof(lseek_code) + 100];

    /* Verify compilation. */
    sprintf(code_buf, lseek_code, combo->includes, combo->lseek_command);
    return chaz_CC_test_link(code_buf);
}

static int
chaz_LargeFiles_probe_pread64(chaz_LargeFiles_unbuff_combo *combo) {
    /* Code for checking 64-bit pread.  The pread call will fail, but that's
     * fine as long as it compiles. */
    static const char pread64_code[] =
        CHAZ_QUOTE(  %s                                     )
        CHAZ_QUOTE(  int main() {                           )
        CHAZ_QUOTE(      char buf[1];                       )
        CHAZ_QUOTE(      %s(0, buf, 1, 1);                  )
        CHAZ_QUOTE(     return 0;                           )
        CHAZ_QUOTE(  }                                      );
    char code_buf[sizeof(pread64_code) + 100];

    /* Verify compilation. */
    sprintf(code_buf, pread64_code, combo->includes, combo->pread64_command);
    return chaz_CC_test_link(code_buf);
}

static void
chaz_LargeFiles_probe_unbuff(void) {
    static chaz_LargeFiles_unbuff_combo unbuff_combos[] = {
        { "#include <unistd.h>\n#include <fcntl.h>\n", "lseek64",   "pread64" },
        { "#include <unistd.h>\n#include <fcntl.h>\n", "lseek",     "pread"      },
        { "#include <io.h>\n#include <stdio.h>\n",     "_lseeki64", "NO_PREAD64" },
        { NULL, NULL, NULL }
    };
    int i;

    for (i = 0; unbuff_combos[i].lseek_command != NULL; i++) {
        chaz_LargeFiles_unbuff_combo combo = unbuff_combos[i];
        if (chaz_LargeFiles_probe_lseek(&combo)) {
            chaz_ConfWriter_add_def("HAS_64BIT_LSEEK", NULL);
            chaz_ConfWriter_add_def("lseek64", combo.lseek_command);
            break;
        }
    }
    for (i = 0; unbuff_combos[i].pread64_command != NULL; i++) {
        chaz_LargeFiles_unbuff_combo combo = unbuff_combos[i];
        if (chaz_LargeFiles_probe_pread64(&combo)) {
            chaz_ConfWriter_add_def("HAS_64BIT_PREAD", NULL);
            chaz_ConfWriter_add_def("pread64", combo.pread64_command);
            break;
        }
    }
}


/***************************************************************************/

#line 17 "src/Charmonizer/Probe/Memory.c"
/* #include "Charmonizer/Probe/Memory.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Probe for alloca() or equivalent. */
static void
chaz_Memory_probe_alloca(void);

void
chaz_Memory_run(void) {
    chaz_ConfWriter_start_module("Memory");

    chaz_Memory_probe_alloca();

    chaz_ConfWriter_end_module();
}

static void
chaz_Memory_probe_alloca(void) {
    static const char alloca_code[] =
        "#include <%s>\n"
        CHAZ_QUOTE(  int main() {                   )
        CHAZ_QUOTE(      void *foo = %s(1);         )
        CHAZ_QUOTE(      return 0;                  )
        CHAZ_QUOTE(  }                              );
    chaz_CFlags *temp_cflags = chaz_CC_get_temp_cflags();
    int has_alloca = false;
    char code_buf[sizeof(alloca_code) + 100];

    {
        /* OpenBSD needs sys/types.h for sys/mman.h to work and mmap() to be
         * available. Everybody else that has sys/mman.h should have
         * sys/types.h as well. */
        const char *mman_headers[] = {
            "sys/types.h",
            "sys/mman.h",
            NULL
        };
        if (chaz_HeadCheck_check_many_headers((const char**)mman_headers)) {
            chaz_ConfWriter_add_def("HAS_SYS_MMAN_H", NULL);
        }
    }

    /* Under GCC, alloca is a builtin that works without including the
     * correct header, generating only a warning. To avoid misdetection,
     * disable the alloca builtin temporarily. */
    if (chaz_CC_is_gcc()) {
        chaz_CFlags_append(temp_cflags, "-fno-builtin-alloca");
    }

    /* Unixen. */
    sprintf(code_buf, alloca_code, "alloca.h", "alloca");
    if (chaz_CC_test_link(code_buf)) {
        has_alloca = true;
        chaz_ConfWriter_add_def("HAS_ALLOCA_H", NULL);
        chaz_ConfWriter_add_def("alloca", "alloca");
    }
    if (!has_alloca) {
        sprintf(code_buf, alloca_code, "stdlib.h", "alloca");
        if (chaz_CC_test_link(code_buf)) {
            has_alloca = true;
            chaz_ConfWriter_add_def("ALLOCA_IN_STDLIB_H", NULL);
            chaz_ConfWriter_add_def("alloca", "alloca");
        }
    }

    /* Windows. */
    if (!has_alloca) {
        sprintf(code_buf, alloca_code, "malloc.h", "alloca");
        if (chaz_CC_test_link(code_buf)) {
            has_alloca = true;
            chaz_ConfWriter_add_def("HAS_MALLOC_H", NULL);
            chaz_ConfWriter_add_def("alloca", "alloca");
        }
    }
    if (!has_alloca) {
        sprintf(code_buf, alloca_code, "malloc.h", "_alloca");
        if (chaz_CC_test_link(code_buf)) {
            chaz_ConfWriter_add_def("HAS_MALLOC_H", NULL);
            chaz_ConfWriter_add_def("alloca", "_alloca");
        }
    }

    chaz_CFlags_clear(temp_cflags);
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe/RegularExpressions.c"
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Probe/RegularExpressions.h" */

void
chaz_RegularExpressions_run(void) {
    int has_regex_h     = chaz_HeadCheck_check_header("regex.h");
    int has_pcre_h      = chaz_HeadCheck_check_header("pcre.h");
    int has_pcreposix_h = chaz_HeadCheck_check_header("pcreposix.h");

    chaz_ConfWriter_start_module("RegularExpressions");

    /* PCRE headers. */
    if (has_pcre_h) {
        chaz_ConfWriter_add_def("HAS_PCRE_H", NULL);
    }
    if (has_pcreposix_h) {
        chaz_ConfWriter_add_def("HAS_PCREPOSIX_H", NULL);
    }

    /* Check for OS X enhanced regexes. */
    if (has_regex_h) {
        const char *reg_enhanced_code =
            CHAZ_QUOTE(  #include <regex.h>                             )
            CHAZ_QUOTE(  int main(int argc, char **argv) {              )
            CHAZ_QUOTE(      regex_t re;                                )
            CHAZ_QUOTE(      if (regcomp(&re, "^", REG_ENHANCED)) {     )
            CHAZ_QUOTE(          return 1;                              )
            CHAZ_QUOTE(      }                                          )
            CHAZ_QUOTE(      return 0;                                  )
            CHAZ_QUOTE(  }                                              );

        if (chaz_CC_test_compile(reg_enhanced_code)) {
            chaz_ConfWriter_add_def("HAS_REG_ENHANCED", NULL);
        }
    }

    chaz_ConfWriter_end_module();
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe/Strings.c"
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Probe/Strings.h" */

#include <stdlib.h>

/* Check for C99-compatible snprintf and possible replacements.
 */
static void
chaz_Strings_probe_c99_snprintf(void);

void
chaz_Strings_run(void) {
    chaz_ConfWriter_start_module("Strings");

    /* Check for C99 snprintf. */
    chaz_Strings_probe_c99_snprintf();

    chaz_ConfWriter_end_module();
}

static void
chaz_Strings_probe_c99_snprintf(void) {
    static const char snprintf_code[] =
        CHAZ_QUOTE(  #include <stdio.h>                             )
        CHAZ_QUOTE(  int main() {                                   )
        CHAZ_QUOTE(      char buf[4];                               )
        CHAZ_QUOTE(      int  result;                               )
        CHAZ_QUOTE(      result = snprintf(buf, 4, "%s", "12345");  )
        CHAZ_QUOTE(      printf("%d", result);                      )
        CHAZ_QUOTE(      return 0;                                  )
        CHAZ_QUOTE(  }                                              );
    char   *output = NULL;
    size_t  output_len;

    /* If the buffer passed to snprintf is too small, verify that snprintf
     * returns the length of the untruncated string which would have been
     * written to a large enough buffer.
     */
    output = chaz_CC_capture_output(snprintf_code, &output_len);
    if (output != NULL) {
        long result = strtol(output, NULL, 10);
        if (result == 5) {
            chaz_ConfWriter_add_def("HAS_C99_SNPRINTF", NULL);
        }
        free(output);
    }

    /* Test for _scprintf and _snprintf found in the MSVCRT.
     */
    if (chaz_HeadCheck_defines_symbol("_scprintf", "#include <stdio.h>")) {
        chaz_ConfWriter_add_def("HAS__SCPRINTF", NULL);
    }
    if (chaz_HeadCheck_defines_symbol("_snprintf", "#include <stdio.h>")) {
        chaz_ConfWriter_add_def("HAS__SNPRINTF", NULL);
    }
}


/***************************************************************************/

#line 17 "src/Charmonizer/Probe/SymbolVisibility.c"
/* #include "Charmonizer/Probe/SymbolVisibility.h" */
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const char chaz_SymbolVisibility_symbol_exporting_code[] =
    CHAZ_QUOTE(  %s int exported_function() {   )
    CHAZ_QUOTE(      return 42;                 )
    CHAZ_QUOTE(  }                              )
    CHAZ_QUOTE(  int main() {                   )
    CHAZ_QUOTE(      return 0;                  )
    CHAZ_QUOTE(  }                              );

void
chaz_SymbolVisibility_run(void) {
    chaz_CFlags *temp_cflags = chaz_CC_get_temp_cflags();
    int can_control_visibility = false;
    char code_buf[sizeof(chaz_SymbolVisibility_symbol_exporting_code) + 100];

    chaz_ConfWriter_start_module("SymbolVisibility");
    chaz_CFlags_set_warnings_as_errors(temp_cflags);

    /* Sun C. */
    if (!can_control_visibility) {
        char export_sun[] = "__global";
        sprintf(code_buf, chaz_SymbolVisibility_symbol_exporting_code,
                export_sun);
        if (chaz_CC_test_compile(code_buf)) {
            can_control_visibility = true;
            chaz_ConfWriter_add_def("EXPORT", export_sun);
            chaz_ConfWriter_add_def("IMPORT", export_sun);
        }
    }

    /* Windows. */
    if (!can_control_visibility) {
        char export_win[] = "__declspec(dllexport)";
        sprintf(code_buf, chaz_SymbolVisibility_symbol_exporting_code,
                export_win);
        if (chaz_CC_test_compile(code_buf)) {
            can_control_visibility = true;
            chaz_ConfWriter_add_def("EXPORT", export_win);
            if (chaz_CC_is_gcc()) {
                /*
                 * Under MinGW, symbols with dllimport storage class aren't
                 * constant. If a global variable is initialized to such a
                 * symbol, an "initializer element is not constant" error
                 * results. Omitting dllimport works, but has a small
                 * performance penalty.
                 */
                chaz_ConfWriter_add_def("IMPORT", NULL);
            }
            else {
                chaz_ConfWriter_add_def("IMPORT", "__declspec(dllimport)");
            }
        }
    }

    /* GCC. */
    if (!can_control_visibility) {
        char export_gcc[] = "__attribute__ ((visibility (\"default\")))";
        sprintf(code_buf, chaz_SymbolVisibility_symbol_exporting_code,
                export_gcc);
        if (chaz_CC_test_compile(code_buf)) {
            can_control_visibility = true;
            chaz_ConfWriter_add_def("EXPORT", export_gcc);
            chaz_ConfWriter_add_def("IMPORT", NULL);
        }
    }

    chaz_CFlags_clear(temp_cflags);

    /* Default. */
    if (!can_control_visibility) {
        chaz_ConfWriter_add_def("EXPORT", NULL);
        chaz_ConfWriter_add_def("IMPORT", NULL);
    }

    chaz_ConfWriter_end_module();
}



/***************************************************************************/

#line 17 "src/Charmonizer/Probe/UnusedVars.c"
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/UnusedVars.h" */
#include <string.h>
#include <stdio.h>


void
chaz_UnusedVars_run(void) {
    chaz_ConfWriter_start_module("UnusedVars");

    /* Write the macros (no test, these are the same everywhere). */
    chaz_ConfWriter_add_def("UNUSED_VAR(x)", "((void)x)");
    chaz_ConfWriter_add_def("UNREACHABLE_RETURN(type)", "return (type)0");

    chaz_ConfWriter_end_module();
}




/***************************************************************************/

#line 17 "src/Charmonizer/Probe/VariadicMacros.c"
/* #include "Charmonizer/Core/Compiler.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/Util.h" */
/* #include "Charmonizer/Probe/VariadicMacros.h" */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/* Code for verifying ISO-style variadic macros. */
static const char chaz_VariadicMacros_iso_code[] =
    CHAZ_QUOTE(  #include <stdio.h>                                    )
                "#define ISO_TEST(fmt, ...) printf(fmt, __VA_ARGS__)\n"
    CHAZ_QUOTE(  void f() { ISO_TEST("%d %d", 1, 1); }                 );

/* Code for verifying GNU-style variadic macros. */
static const char chaz_VariadicMacros_gnuc_code[] =
    CHAZ_QUOTE(  #include <stdio.h>                                    )
    CHAZ_QUOTE(  #define GNU_TEST(fmt, args...) printf(fmt, ##args)    )
    CHAZ_QUOTE(  void f() { GNU_TEST("%d %d", 1, 1); }                 );

void
chaz_VariadicMacros_run(void) {
    int has_varmacros = false;

    chaz_ConfWriter_start_module("VariadicMacros");

    /* Test for ISO-style variadic macros. */
    if (chaz_CC_test_compile(chaz_VariadicMacros_iso_code)) {
        has_varmacros = true;
        chaz_ConfWriter_add_def("HAS_VARIADIC_MACROS", NULL);
        chaz_ConfWriter_add_def("HAS_ISO_VARIADIC_MACROS", NULL);
    }

    /* Test for GNU-style variadic macros. */
    if (chaz_CC_test_compile(chaz_VariadicMacros_gnuc_code)) {
        if (has_varmacros == false) {
            has_varmacros = true;
            chaz_ConfWriter_add_def("HAS_VARIADIC_MACROS", NULL);
        }
        chaz_ConfWriter_add_def("HAS_GNUC_VARIADIC_MACROS", NULL);
    }

    chaz_ConfWriter_end_module();
}




#line 1 "common/charmonizer.main"
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

/* Source fragment for Lucy's charmonizer.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "Charmonizer/Probe.h" */
/* #include "Charmonizer/Probe/AtomicOps.h" */
/* #include "Charmonizer/Probe/DirManip.h" */
/* #include "Charmonizer/Probe/Floats.h" */
/* #include "Charmonizer/Probe/FuncMacro.h" */
/* #include "Charmonizer/Probe/Headers.h" */
/* #include "Charmonizer/Probe/Integers.h" */
/* #include "Charmonizer/Probe/LargeFiles.h" */
/* #include "Charmonizer/Probe/Memory.h" */
/* #include "Charmonizer/Probe/SymbolVisibility.h" */
/* #include "Charmonizer/Probe/VariadicMacros.h" */
/* #include "Charmonizer/Core/HeaderChecker.h" */
/* #include "Charmonizer/Core/ConfWriter.h" */
/* #include "Charmonizer/Core/ConfWriterC.h" */
/* #include "Charmonizer/Core/ConfWriterPerl.h" */
/* #include "Charmonizer/Core/ConfWriterRuby.h" */

typedef struct lucy_MakeFile {
    chaz_CLI        *cli;
    chaz_MakeFile   *makefile;
    chaz_MakeBinary *lib;
    chaz_MakeBinary *test_lib;

    /* Directories. */
    const char *base_dir;
    char       *core_dir;
    char       *test_dir;
    const char *host_src_dir;
    char       *autogen_src_dir;
    char       *autogen_inc_dir;
    char       *lemon_dir;
    char       *modules_dir;
    char       *snowstem_dir;
    char       *snowstem_inc_dir;
    char       *snowstop_dir;
    char       *ucd_dir;
    char       *utf8proc_dir;
    char       *json_dir;

    /* Targets. */
    char *autogen_target;

    /* Clownfish library. */
    char       *cfish_lib_dir;
    const char *cfish_lib_name;
} lucy_MakeFile;

typedef struct SourceFileContext {
    chaz_MakeVar *var;
} SourceFileContext;

static const char lucy_version[]        = "0.6.0";
static const char lucy_major_version[]  = "0.6";

static void
S_add_compiler_flags(struct chaz_CLI *cli);

static lucy_MakeFile*
lucy_MakeFile_new(chaz_CLI *cli);

static void
lucy_MakeFile_destroy(lucy_MakeFile *self);

static void
lucy_MakeFile_write(lucy_MakeFile *self);

static void
lucy_MakeFile_write_c_cfc_rules(lucy_MakeFile *self);

static void
lucy_MakeFile_write_c_test_rules(lucy_MakeFile *self);

static void
lucy_MakeFile_write_c_install_rules(lucy_MakeFile *self);

static int
S_core_dir_filter(const char *dir, char *file, void *context);

static void
S_cfh_file_callback(const char *dir, char *file, void *context);

static int
S_ends_with(const char *string, const char *postfix);

int main(int argc, const char **argv) {
    /* Initialize. */
    chaz_CLI *cli
        = chaz_CLI_new(argv[0], "charmonizer: Probe C build environment");
    chaz_CLI_register(cli, "host", "specify host binding language",
                      CHAZ_CLI_ARG_REQUIRED);
    chaz_CLI_register(cli, "disable-threads", "whether to disable threads",
                      CHAZ_CLI_NO_ARG);
    chaz_CLI_register(cli, "clownfish-prefix",
                      "prefix of Clownfish installation",
                      CHAZ_CLI_ARG_OPTIONAL);
    chaz_CLI_register(cli, "enable-go", "enable Go bindings",
                      CHAZ_CLI_NO_ARG);
    chaz_CLI_set_usage(cli, "Usage: charmonizer [OPTIONS] [-- [CFLAGS]]");
    if (!chaz_Probe_parse_cli_args(argc, argv, cli)) {
        chaz_Probe_die_usage();
    }
    chaz_Probe_init(cli);
    S_add_compiler_flags(cli);

    /* Employ integer features but don't define stdint types in charmony.h. */
    chaz_ConfWriter_append_conf(
        "#define CHY_EMPLOY_INTEGERLIMITS\n"
        "#define CHY_EMPLOY_INTEGERLITERALS\n"
        "#define CHY_EMPLOY_INTEGERFORMATSTRINGS\n\n"
    );

    /* Run probe modules. Booleans is only needed for the Charmonizer tests. */
    chaz_BuildEnv_run();
    chaz_DirManip_run();
    chaz_Headers_run();
    chaz_FuncMacro_run();
    chaz_Booleans_run();
    chaz_Integers_run();
    chaz_Floats_run();
    chaz_LargeFiles_run();
    chaz_Memory_run();
    chaz_RegularExpressions_run();
    chaz_SymbolVisibility_run();
    chaz_VariadicMacros_run();

    chaz_ConfWriter_start_module("Lucy");

    {
        /*
         * Check for flock() with BSD semantics that doesn't simply wrap
         * fcntl().
         */
        static const char flock_code[] =
            CHAZ_QUOTE(  #include <errno.h>                               )
            CHAZ_QUOTE(  #include <fcntl.h>                               )
            CHAZ_QUOTE(  #include <stdio.h>                               )
            CHAZ_QUOTE(  #include <sys/file.h>                            )
            CHAZ_QUOTE(  int main() {                                     )
            CHAZ_QUOTE(      const char *path = "_charm_testlock";        )
            CHAZ_QUOTE(      int fd1;                                     )
            CHAZ_QUOTE(      int fd2;                                     )
            CHAZ_QUOTE(      fd1 = open(path, O_CREAT|O_RDONLY, 0600);    )
            CHAZ_QUOTE(      if (flock(fd1, LOCK_EX|LOCK_NB)) return 1;   )
            CHAZ_QUOTE(      fd2 = open(path, O_RDONLY, 0600);            )
            CHAZ_QUOTE(      if (!flock(fd2, LOCK_EX|LOCK_NB)) return 1;  )
            CHAZ_QUOTE(      if (errno != EWOULDBLOCK) return 1;          )
            CHAZ_QUOTE(      printf("success");                           )
            CHAZ_QUOTE(      return 0;                                    )
            CHAZ_QUOTE(  }                                                );
        size_t output_len;
        char *output = chaz_CC_capture_output(flock_code, &output_len);

        if (output != NULL && strcmp(output, "success") == 0) {
            chaz_ConfWriter_add_def("HAS_FLOCK", NULL);
        }

        chaz_Util_remove_and_verify("_charm_testlock");
        free(output);
    }

    chaz_ConfWriter_end_module();

    /* Write custom postamble. */
    chaz_ConfWriter_append_conf(
        "#ifdef CHY_HAS_SYS_TYPES_H\n"
        "  #include <sys/types.h>\n"
        "#endif\n\n"
    );
    chaz_ConfWriter_append_conf(
        "#ifdef CHY_HAS_ALLOCA_H\n"
        "  #include <alloca.h>\n"
        "#elif defined(CHY_HAS_MALLOC_H)\n"
        "  #include <malloc.h>\n"
        "#elif defined(CHY_ALLOCA_IN_STDLIB_H)\n"
        "  #include <stdlib.h>\n"
        "#endif\n\n"
    );
    chaz_ConfWriter_append_conf(
        "#ifdef CHY_HAS_WINDOWS_H\n"
        "  /* Target Windows XP. */\n"
        "  #ifndef WINVER\n"
        "    #define WINVER 0x0500\n"
        "  #endif\n"
        "  #ifndef _WIN32_WINNT\n"
        "    #define _WIN32_WINNT 0x0500\n"
        "  #endif\n"
        "#endif\n\n"
    );

    if (chaz_CLI_defined(cli, "enable-makefile")) {
        lucy_MakeFile *mf = lucy_MakeFile_new(cli);
        lucy_MakeFile_write(mf);
        lucy_MakeFile_destroy(mf);
    }

    /* Clean up. */
    chaz_CLI_destroy(cli);
    chaz_Probe_clean_up();

    return 0;
}

static void
S_add_compiler_flags(struct chaz_CLI *cli) {
    chaz_CFlags *extra_cflags = chaz_CC_get_extra_cflags();

    if (getenv("LUCY_DEBUG")) {
        chaz_CFlags_add_define(extra_cflags, "LUCY_DEBUG", NULL);
    }

    if (chaz_CC_is_gcc()) {
        chaz_CFlags_append(extra_cflags,
            "-pedantic -Wall -Wextra -Wno-variadic-macros");
        if (chaz_CLI_defined(cli, "enable-perl")) {
            chaz_CFlags_append(extra_cflags, "-DPERL_GCC_PEDANTIC");
        }

        /* Only core source files require this -- not our headers and
         * autogenerated files. */
        chaz_CFlags_append(extra_cflags, "-std=gnu99 -D_GNU_SOURCE");
    }
    else if (chaz_CC_is_msvc()) {
        if (chaz_CC_test_msvc_version("< 1800")) {
            /* Compile as C++ under MSVC11 and below. */
            chaz_CFlags_append(extra_cflags, "/TP");
        }

        chaz_CFlags_append(extra_cflags, "/W3");
        /* Thwart stupid warnings. */
        chaz_CFlags_append(extra_cflags,
	    "/D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS /wd4996");
    }

    chaz_CFlags_hide_symbols(extra_cflags);
}

static lucy_MakeFile*
lucy_MakeFile_new(chaz_CLI *cli) {
    const char *dir_sep      = chaz_OS_dir_sep();
    const char *host         = chaz_CLI_strval(cli, "host");
    const char *cfish_prefix = chaz_CLI_strval(cli, "clownfish-prefix");
    char *cfcore_filename = chaz_Util_join(dir_sep, "cfcore", "Lucy.cfp",
                                           NULL);
    lucy_MakeFile *self = malloc(sizeof(lucy_MakeFile));

    self->cli      = cli;
    self->makefile = chaz_MakeFile_new();
    self->lib      = NULL;
    self->test_lib = NULL;

    /* Initialize directories. */
    if (chaz_Util_can_open_file(cfcore_filename)) {
        self->base_dir = ".";
        self->core_dir = chaz_Util_strdup("cfcore");
        self->test_dir = chaz_Util_strdup("cftest");
    }
    else {
        self->base_dir = "..";
        self->core_dir = chaz_Util_join(dir_sep, self->base_dir, "core", NULL);
        self->test_dir = chaz_Util_join(dir_sep, self->base_dir, "test", NULL);
    }
    if (strcmp(host, "go") == 0) {
        self->host_src_dir = "cfext";
    }
    else if (strcmp(host, "c") == 0) {
        self->host_src_dir = "src";
    }
    else {
        self->host_src_dir = NULL;
    }
    self->autogen_src_dir = chaz_Util_join(dir_sep, "autogen", "source", NULL);
    self->autogen_inc_dir
        = chaz_Util_join(dir_sep, "autogen", "include", NULL);
    self->lemon_dir = chaz_Util_join(dir_sep, self->base_dir, "lemon", NULL);
    self->modules_dir
        = chaz_Util_join(dir_sep, self->base_dir, "modules", NULL);
    self->snowstem_dir
        = chaz_Util_join(dir_sep, self->modules_dir, "analysis", "snowstem",
                         "source", NULL);
    self->snowstem_inc_dir
        = chaz_Util_join(dir_sep, self->snowstem_dir, "include", NULL);
    self->snowstop_dir
        = chaz_Util_join(dir_sep, self->modules_dir, "analysis", "snowstop",
                         "source", NULL);
    self->ucd_dir
        = chaz_Util_join(dir_sep, self->modules_dir, "unicode", "ucd", NULL);
    self->utf8proc_dir
        = chaz_Util_join(dir_sep, self->modules_dir, "unicode", "utf8proc",
                         NULL);
    self->json_dir
        = chaz_Util_join(dir_sep, self->core_dir, "Lucy", "Util", "Json",
                         NULL);

    /* Initialize targets. */
    self->autogen_target
        = chaz_Util_join(dir_sep, "autogen", "hierarchy.json", NULL);

    /* Clownfish library. */
    if (cfish_prefix) {
        self->cfish_lib_dir
            = chaz_Util_join(dir_sep, cfish_prefix, "lib", NULL);
    }
    else {
        self->cfish_lib_dir = NULL;
    }
    if (chaz_CC_binary_format() == CHAZ_CC_BINFMT_PE) {
        self->cfish_lib_name = "clownfish-0.6";
    }
    else {
        self->cfish_lib_name = "clownfish";
    }

    free(cfcore_filename);
    return self;
}

static void
lucy_MakeFile_destroy(lucy_MakeFile *self) {
    chaz_MakeFile_destroy(self->makefile);

    free(self->core_dir);
    free(self->test_dir);
    free(self->autogen_inc_dir);
    free(self->autogen_src_dir);
    free(self->lemon_dir);
    free(self->modules_dir);
    free(self->snowstem_dir);
    free(self->snowstem_inc_dir);
    free(self->snowstop_dir);
    free(self->ucd_dir);
    free(self->utf8proc_dir);
    free(self->json_dir);

    free(self->autogen_target);

    free(self->cfish_lib_dir);

    free(self);
}

static void
lucy_MakeFile_write(lucy_MakeFile *self) {
    const char *dir_sep  = chaz_OS_dir_sep();
    const char *host     = chaz_CLI_strval(self->cli, "host");
    const char *math_lib = chaz_Floats_math_library();

    int is_c = strcmp(host, "c") == 0;

    const char *lib_objs      = NULL;
    const char *test_lib_objs = NULL;

    chaz_MakeVar  *var;
    chaz_MakeRule *rule;

    chaz_CFlags *extra_cflags = chaz_CC_get_extra_cflags();
    chaz_CFlags *makefile_cflags;
    chaz_CFlags *compile_flags;
    chaz_CFlags *link_flags;

    char *scratch;

    printf("Creating Makefile...\n");

    /* Directories */

    chaz_MakeFile_add_var(self->makefile, "BASE_DIR", self->base_dir);

    /* C compiler */

    makefile_cflags = chaz_CC_new_cflags();

    chaz_CFlags_enable_optimization(makefile_cflags);
    chaz_CFlags_enable_debugging(makefile_cflags);
    chaz_CFlags_disable_strict_aliasing(makefile_cflags);
    if (chaz_CLI_defined(self->cli, "enable-coverage")) {
        chaz_CFlags_enable_code_coverage(makefile_cflags);
    }

    chaz_CFlags_add_include_dir(makefile_cflags, ".");
    chaz_CFlags_add_include_dir(makefile_cflags, self->core_dir);
    chaz_CFlags_add_include_dir(makefile_cflags, self->autogen_inc_dir);
    chaz_CFlags_add_include_dir(makefile_cflags, self->snowstem_inc_dir);
    chaz_CFlags_add_include_dir(makefile_cflags, self->ucd_dir);
    chaz_CFlags_add_include_dir(makefile_cflags, self->utf8proc_dir);

    var = chaz_MakeFile_add_var(self->makefile, "LUCY_CFLAGS", NULL);
    chaz_MakeVar_append(var, chaz_CFlags_get_string(extra_cflags));
    chaz_MakeVar_append(var, chaz_CFlags_get_string(makefile_cflags));
    chaz_MakeVar_append(var, chaz_CC_get_cflags());

    chaz_CFlags_destroy(makefile_cflags);

    /* Core library. */

    if (is_c || strcmp(host, "perl") == 0) {
        /* Shared library for C and Perl. */

        chaz_MakeFile_add_rule(self->makefile, "all", "$(LUCY_SHARED_LIB)");

        self->lib
            = chaz_MakeFile_add_shared_lib(self->makefile, NULL, "lucy",
                                           lucy_version, lucy_major_version,
                                           is_c);
        lib_objs = "$(LUCY_SHARED_LIB_OBJS)";

        compile_flags = chaz_MakeBinary_get_compile_flags(self->lib);
        chaz_CFlags_append(compile_flags, "$(LUCY_CFLAGS)");
        chaz_CFlags_add_define(compile_flags, "CFP_LUCY", NULL);

        link_flags = chaz_MakeBinary_get_link_flags(self->lib);
        chaz_CFlags_enable_debugging(link_flags);
        if (self->cfish_lib_dir) {
            chaz_CFlags_add_library_path(link_flags, self->cfish_lib_dir);
        }
        if (math_lib) {
            chaz_CFlags_add_external_lib(link_flags, math_lib);
        }
        chaz_CFlags_add_external_lib(link_flags, self->cfish_lib_name);
        if (chaz_HeadCheck_check_header("pcre.h")) {
            chaz_CFlags_add_external_lib(link_flags, "pcre");
        }
        if (chaz_CLI_defined(self->cli, "enable-coverage")) {
            chaz_CFlags_enable_code_coverage(link_flags);
        }
    }
    else {
        /* Static library for Go and Python. */

        chaz_MakeFile_add_rule(self->makefile, "static",
                               "$(LUCY_STATIC_LIB) $(TESTLUCY_STATIC_LIB)");

        self->lib
            = chaz_MakeFile_add_static_lib(self->makefile, NULL, "lucy", 0);
        lib_objs = "$(LUCY_STATIC_LIB_OBJS)";

        compile_flags = chaz_MakeBinary_get_compile_flags(self->lib);
        chaz_CFlags_append(compile_flags, "$(LUCY_CFLAGS)");

        if (strcmp(host, "python") == 0) {
            /* For Python, the static library is linked into a shared
             * library.
             */
            chaz_CFlags_compile_shared_library(compile_flags);
            chaz_CFlags_add_define(compile_flags, "CFP_CFISH", NULL);
        }
    }

    if (self->host_src_dir != NULL) {
        chaz_MakeBinary_add_src_dir(self->lib, self->host_src_dir);
    }
    chaz_MakeBinary_add_filtered_src_dir(self->lib, self->core_dir,
                                         S_core_dir_filter, NULL);
    chaz_MakeBinary_add_src_dir(self->lib, self->snowstem_dir);
    chaz_MakeBinary_add_src_dir(self->lib, self->snowstop_dir);
    chaz_MakeBinary_add_src_dir(self->lib, self->utf8proc_dir);
    chaz_MakeBinary_add_src_file(self->lib, self->json_dir, "JsonParser.c");
    chaz_MakeBinary_add_src_file(self->lib, self->autogen_src_dir,
                                 "lucy_parcel.c");

    /* Test library. */

    if (is_c || strcmp(host, "perl") == 0) {
        /* Shared library for C and Perl. */

        self->test_lib
            = chaz_MakeFile_add_shared_lib(self->makefile, NULL, "testlucy",
                                           lucy_version, lucy_major_version,
                                           0);
        test_lib_objs = "$(TESTLUCY_SHARED_LIB_OBJS)";

        compile_flags = chaz_MakeBinary_get_compile_flags(self->test_lib);
        chaz_CFlags_append(compile_flags, "$(LUCY_CFLAGS)");
        chaz_CFlags_add_define(compile_flags, "CFP_TESTLUCY", NULL);

        link_flags = chaz_MakeBinary_get_link_flags(self->test_lib);
        chaz_CFlags_enable_debugging(link_flags);
        if (self->cfish_lib_dir) {
            chaz_CFlags_add_library_path(link_flags, self->cfish_lib_dir);
        }
        chaz_CFlags_add_shared_lib(link_flags, NULL, "lucy",
                                   lucy_major_version);
        chaz_CFlags_add_external_lib(link_flags, self->cfish_lib_name);
        if (math_lib) {
            chaz_CFlags_add_external_lib(link_flags, math_lib);
        }
        if (chaz_CLI_defined(self->cli, "enable-coverage")) {
            chaz_CFlags_enable_code_coverage(link_flags);
        }

        chaz_MakeBinary_add_prereq(self->test_lib, "$(LUCY_SHARED_LIB)");
    }
    else {
        /* Static library for Go and Python. */

        self->test_lib = chaz_MakeFile_add_static_lib(self->makefile, NULL,
                                                      "testlucy", 0);
        test_lib_objs = "$(TESTLUCY_STATIC_LIB_OBJS)";

        compile_flags = chaz_MakeBinary_get_compile_flags(self->test_lib);
        chaz_CFlags_append(compile_flags, "$(LUCY_CFLAGS)");

        if (strcmp(host, "python") == 0) {
            /* For Python, the static library is linked into a shared
             * library.
             */
            chaz_CFlags_compile_shared_library(compile_flags);
            chaz_CFlags_add_define(compile_flags, "CFP_TESTLUCY", NULL);
        }
    }

    chaz_MakeBinary_add_src_dir(self->test_lib, self->test_dir);
    chaz_MakeBinary_add_src_file(self->test_lib, self->autogen_src_dir,
                                 "testlucy_parcel.c");

    /* Additional rules. */

    chaz_MakeFile_add_lemon_exe(self->makefile, self->lemon_dir);
    scratch = chaz_Util_join(dir_sep, self->json_dir, "JsonParser", NULL);
    chaz_MakeFile_add_lemon_grammar(self->makefile, scratch);
    free(scratch);

    /* Object files depend on autogenerated headers. */
    rule = chaz_MakeFile_add_rule(self->makefile, lib_objs,
                                  self->autogen_target);
    /*
     * The dependency is actually on JsonParser.h, but make doesn't cope
     * well with multiple output files.
     */
    scratch = chaz_Util_join(dir_sep, self->json_dir, "JsonParser.c",
                             NULL);
    chaz_MakeRule_add_prereq(rule, scratch);
    free(scratch);
    chaz_MakeFile_add_rule(self->makefile, test_lib_objs,
                           self->autogen_target);

    if (is_c) {
        lucy_MakeFile_write_c_cfc_rules(self);
        lucy_MakeFile_write_c_test_rules(self);
        lucy_MakeFile_write_c_install_rules(self);
    }

    /* Targets to compile object files for Perl. */
    if (strcmp(host, "perl") == 0) {
        char *objects;

        chaz_MakeFile_add_rule(self->makefile, "core_objects",
                               "$(LUCY_SHARED_LIB_OBJS)");
        objects = chaz_MakeBinary_obj_string(self->lib);
        chaz_ConfWriter_add_def("CORE_OBJECTS", objects);
        free(objects);

        chaz_MakeFile_add_rule(self->makefile, "test_objects",
                               "$(TESTLUCY_SHARED_LIB_OBJS)");
        objects = chaz_MakeBinary_obj_string(self->test_lib);
        chaz_ConfWriter_add_def("TEST_OBJECTS", objects);
        free(objects);
    }

    chaz_MakeFile_write(self->makefile);
}

static void
lucy_MakeFile_write_c_cfc_rules(lucy_MakeFile *self) {
    static const char *const autogen_src_files[] = {
        "lucy_parcel.c",
        "testlucy_parcel.c",
        NULL
    };

    SourceFileContext sfc;
    chaz_MakeRule *rule;

    const char *dir_sep      = chaz_OS_dir_sep();
    const char *cfish_prefix = chaz_CLI_strval(self->cli, "clownfish-prefix");

    char *cfc_command;

    int i;

    sfc.var = chaz_MakeFile_add_var(self->makefile, "CLOWNFISH_HEADERS", NULL);
    chaz_Make_list_files(self->core_dir, "cfh", S_cfh_file_callback, &sfc);
    chaz_Make_list_files(self->test_dir, "cfh", S_cfh_file_callback, &sfc);

    rule = chaz_MakeFile_add_rule(self->makefile, self->autogen_target, NULL);
    chaz_MakeRule_add_prereq(rule, "$(CLOWNFISH_HEADERS)");
    if (cfish_prefix == NULL) {
        cfc_command
            = chaz_Util_join("", "cfc --charmonic --source=", self->core_dir,
                             " --source=", self->test_dir,
                             " --dest=autogen --header=cfc_header", NULL);
    }
    else {
        cfc_command
            = chaz_Util_join("", cfish_prefix, dir_sep, "bin", dir_sep,
                             "cfc --source=", self->core_dir, " --source=",
                             self->test_dir, " --include=", cfish_prefix,
                             dir_sep, "share", dir_sep, "clownfish", dir_sep,
                             "include --dest=autogen --header=cfc_header",
                             NULL);
    }
    chaz_MakeRule_add_command(rule, cfc_command);

    /* Tell make how autogenerated source files are built. */
    for (i = 0; autogen_src_files[i] != NULL; ++i) {
        char *path = chaz_Util_join("", self->autogen_src_dir, dir_sep,
                                    autogen_src_files[i], NULL);
        rule = chaz_MakeFile_add_rule(self->makefile, path,
                                      self->autogen_target);
        free(path);
    }

    rule = chaz_MakeFile_clean_rule(self->makefile);
    chaz_MakeRule_add_recursive_rm_command(rule, "autogen");

    free(cfc_command);
}

static void
lucy_MakeFile_write_c_test_rules(lucy_MakeFile *self) {
    chaz_MakeBinary *exe;
    chaz_CFlags     *compile_flags;
    chaz_CFlags     *link_flags;
    chaz_MakeRule   *rule;

    exe = chaz_MakeFile_add_exe(self->makefile, "t", "test_lucy", 0);
    chaz_MakeBinary_add_src_file(exe, "t", "test_lucy.c");

    compile_flags = chaz_MakeBinary_get_compile_flags(exe);
    chaz_CFlags_append(compile_flags, "$(LUCY_CFLAGS)");

    link_flags = chaz_MakeBinary_get_link_flags(exe);
    if (self->cfish_lib_dir) {
        chaz_CFlags_add_library_path(link_flags, self->cfish_lib_dir);
    }
    chaz_CFlags_add_rpath(link_flags, "\"$$PWD\"");
    if (self->cfish_lib_dir) {
        chaz_CFlags_add_rpath(link_flags, self->cfish_lib_dir);
    }
    chaz_CFlags_add_shared_lib(link_flags, NULL, "testlucy",
                               lucy_major_version);
    chaz_CFlags_add_shared_lib(link_flags, NULL, "lucy", lucy_major_version);
    chaz_CFlags_add_external_lib(link_flags, self->cfish_lib_name);

    chaz_MakeBinary_add_prereq(exe, "$(TESTLUCY_SHARED_LIB)");
    chaz_MakeBinary_add_prereq(exe, "$(LUCY_SHARED_LIB)");

    chaz_MakeFile_add_rule(self->makefile, "$(TEST_LUCY_EXE_OBJS)",
                           self->autogen_target);

    rule = chaz_MakeFile_add_rule(self->makefile, "test", "$(TEST_LUCY_EXE)");
    chaz_MakeRule_add_command(rule, "$(TEST_LUCY_EXE)");

    if (chaz_CLI_defined(self->cli, "enable-coverage")) {
        rule = chaz_MakeFile_add_rule(self->makefile, "coverage",
                                      "$(TEST_LUCY_EXE)");
        chaz_MakeRule_add_command(rule,
                                  "lcov"
                                  " --zerocounters"
                                  " --directory $(BASE_DIR)");
        chaz_MakeRule_add_command(rule, "$(TEST_LUCY_EXE)");
        chaz_MakeRule_add_command(rule,
                                  "lcov"
                                  " --capture"
                                  " --directory $(BASE_DIR)"
                                  " --base-directory ."
                                  " --rc lcov_branch_coverage=1"
                                  " --output-file lucy.info");
        chaz_MakeRule_add_command(rule,
                                  "genhtml"
                                  " --branch-coverage"
                                  " --output-directory coverage"
                                  " lucy.info");

        rule = chaz_MakeFile_clean_rule(self->makefile);
        chaz_MakeRule_add_rm_command(rule, "lucy.info");
        chaz_MakeRule_add_recursive_rm_command(rule, "coverage");
    }
}

static void
lucy_MakeFile_write_c_install_rules(lucy_MakeFile *self) {
    const char *dir_sep = chaz_OS_dir_sep();
    char *src;

    src = chaz_Util_join(dir_sep, "autogen", "share", NULL);
    chaz_MakeFile_install_dir(self->makefile, src, "$(DATADIR)", NULL);
    free(src);

    src = chaz_Util_join(dir_sep, "autogen", "man", NULL);
    chaz_MakeFile_install_dir(self->makefile, src, "$(MANDIR)", NULL);
    free(src);

    chaz_MakeFile_install_pkgconfig(self->makefile, "lucy", lucy_version,
        "Name: Apache Lucy\n"
        "Description: Full-text search for dynamic languages\n"
        "URL: http://lucy.apache.org/\n"
        "Version: $${version}\n"
        "Requires: clownfish\n"
        "Libs: -L$${libdir} -llucy\n"
    );
}

static int
S_core_dir_filter(const char *dir, char *file, void *context) {
    (void)dir;
    (void)context;
    return !S_ends_with(file, "JsonParser.c");
}

static void
S_cfh_file_callback(const char *dir, char *file, void *context) {
    SourceFileContext *sfc = (SourceFileContext*)context;
    const char *dir_sep = chaz_OS_dir_sep();
    char *cfh_file;

    if (!S_ends_with(file, ".cfh")) {
        chaz_Util_warn("Unexpected Clownfish header filename: %s", file);
        return;
    }

    cfh_file = chaz_Util_join(dir_sep, dir, file, NULL);
    chaz_MakeVar_append(sfc->var, cfh_file);
    free(cfh_file);
}

static int
S_ends_with(const char *string, const char *postfix) {
    size_t len         = strlen(string);
    size_t postfix_len = strlen(postfix);
    return len >= postfix_len
           && memcmp(string + len - postfix_len, postfix, postfix_len) == 0;
}


