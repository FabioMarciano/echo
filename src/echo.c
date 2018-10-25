/*
 * Echo - C log library
 * -----------------------------------------------------------------------------
 * Licensed under the ISC license, see LICENSE in root for details.
 *
 * echo.c - Echo main source file
 *
 * Copyright (c) 2018 Fábio Marciano
 *
 */

#include "echo.h"

void __lib_echo_init__() {
	__echo_stdout__ = stdout;
	__echo_stderr__ = stderr;

	__echo__.level = LOG_LEVEL_ALL;
	__echo__.file.out = NULL;
	__echo__.file.err = NULL;

	__echo__.set.level = &__lib_echo_level__;
	__echo__.set.stdout = &__lib_echo_set_stdout__;
	__echo__.set.stderr = &__lib_echo_set_stderr__;

	__echo__.reset.stdout = &__lib_echo_reset_stdout__;
	__echo__.reset.stderr = &__lib_echo_reset_stderr__;

	__echo__.debug = &__lib_echo_debug__;
	__echo__.trace = &__lib_echo_trace__;
	__echo__.info = &__lib_echo_info__;
	__echo__.notice = &__lib_echo_notice__;
	__echo__.warning = &__lib_echo_warning__;
	__echo__.error = &__lib_echo_error__;
}

void __lib_echo_quit__() {
	__lib_echo_quit_stream__();
	__lib_echo_clean_data_stdout__();
	__lib_echo_clean_data_stderr__();
}

void __lib_echo_init_stream__(int level) {
	int output = __LIB_ECHO_GET_LEVEL_TYPE__(level);
	if (output && (__echo__.file.err != NULL)) {
		__echo_stderr__ = fopen(__echo__.file.err, "a+");
	}
	if (!output && (__echo__.file.out != NULL)) {
		__echo_stdout__ = fopen(__echo__.file.out, "a+");
	}
}

void __lib_echo_quit_stream__() {
	if (__echo_stdout__ != stdout) {
		fclose(__echo_stdout__);
		__echo_stdout__ = stdout;
	}
	if (__echo_stderr__ != stderr) {
		fclose(__echo_stderr__);
		__echo_stderr__ = stderr;
	}
}

void __lib_echo_level__(int level) {
	__echo__.level = level;
}

void __lib_echo_clean_data_stdout__() {
	if (__echo__.file.out != NULL) {
		free(__echo__.file.out);
	}
	__echo__.file.out = NULL;
}

void __lib_echo_clean_data_stderr__() {
	if (__echo__.file.err != NULL) {
		free(__echo__.file.err);
	}
	__echo__.file.err = NULL;
}

void __lib_echo_set_stdout__(const char *file) {
	__lib_echo_clean_data_stdout__();

	if (file == NULL) return;

	size_t len = strlen(file);

	__echo__.file.out = (char *) malloc(sizeof(char) * (len + 1));

	if (__echo__.file.out != NULL) {
		strcpy(__echo__.file.out, file);
		__echo__.file.out[len] = '\0';
	}
}

void __lib_echo_set_stderr__(const char *file) {
	__lib_echo_clean_data_stderr__();

	if (file == NULL) return;

	size_t len = strlen(file);

	__echo__.file.err = (char *) malloc(sizeof(char) * (len + 1));

	if (__echo__.file.err != NULL) {
		strcpy(__echo__.file.err, file);
		__echo__.file.err[len] = '\0';
	}
}

void __lib_echo_reset_stdout__(const char *file) {
	__lib_echo_set_stdout__(NULL);
}

void __lib_echo_reset_stderr__(const char *file) {
	__lib_echo_set_stderr__(NULL);
}

void __lib_echo_debug__(const char *fmt, ...) {
	__LIB_ECHO_EXECUTE__(LOG_LEVEL_DEBUG, "DEBUG", __echo_stdout__);
}

void __lib_echo_trace__(const char *fmt, ...) {
	__LIB_ECHO_EXECUTE__(LOG_LEVEL_TRACE, "TRACE", __echo_stdout__);
}

void __lib_echo_info__(const char *fmt, ...) {
	__LIB_ECHO_EXECUTE__(LOG_LEVEL_INFO, "INFO", __echo_stdout__);
}

void __lib_echo_notice__(const char *fmt, ...) {
	__LIB_ECHO_EXECUTE__(LOG_LEVEL_NOTICE, "NOTICE", __echo_stderr__);
}

void __lib_echo_warning__(const char *fmt, ...) {
	__LIB_ECHO_EXECUTE__(LOG_LEVEL_WARNING, "WARNING", __echo_stderr__);
}

void __lib_echo_error__(const char *fmt, ...) {
	__LIB_ECHO_EXECUTE__(LOG_LEVEL_ERROR, "ERROR", __echo_stderr__);
}
