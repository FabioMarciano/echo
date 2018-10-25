/*
 * Echo - C log library
 * -----------------------------------------------------------------------------
 * Licensed under the ISC license, see LICENSE in root for details.
 *
 * echo.h - Echo library main header file
 *
 * Copyright (c) 2018 Fábio Marciano
 *
 */

#ifndef __LIB_ECHO_H__
	#define __LIB_ECHO_H__ 1

	/**
	 * Include section
	 */
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <string.h>
	#include <unistd.h>

	/**
	 * Start Of File (__SOF__) and End Of File (__EOF__) definition.
	 * Set up to C function definitions even when using C++.
	 */
	#ifdef	__cplusplus
		#ifndef __SOF__
			#define __SOF__	extern "C" {
		#endif
		#ifndef
			#define __EOF__ }
		#endif
	#else
		#ifndef __SOF__
			#define __SOF__
		#endif
		#ifndef __EOF__
			#define __EOF__
		#endif
	#endif

	/**
	 * Echo library LOG levels
	 */
	#define LOG_LEVEL_NONE      0
	#define LOG_LEVEL_ERROR     1
	#define LOG_LEVEL_WARNING   2
	#define LOG_LEVEL_NOTICE    4
	#define LOG_LEVEL_INFO      8
	#define LOG_LEVEL_TRACE     16
	#define LOG_LEVEL_DEBUG     32

	#define LOG_LEVEL_ALL (LOG_LEVEL_DEBUG | LOG_LEVEL_TRACE | LOG_LEVEL_INFO | LOG_LEVEL_NOTICE | LOG_LEVEL_WARNING | LOG_LEVEL_ERROR)

	/**
	 * Echo main structure
	 */
	struct {
		int level;

		struct {
			char *out;
			char *err;
		} file;

		struct {
			void (*level)(int);
			void (*stdout)(const char *);
			void (*stderr)(const char *);
		} set;

		struct {
			void (*stdout)();
			void (*stderr)();
		} reset;

		void (*debug)(const char *, ...);
		void (*trace)(const char *, ...);
		void (*info)(const char *, ...);
		void (*notice)(const char *, ...);
		void (*warning)(const char *, ...);
		void (*error)(const char *, ...);

	} __echo__;

	/**
	 * Echo stdout and stderr stream pointer
	*/
	FILE *__echo_stdout__;
	FILE *__echo_stderr__;

	/**
	 * Redirects to any echo library function with the format __lib_echo_ ID __()
	 * @param {const char} ID - the log library function identifier
	 * @param {any} args... - variadic arguments
	 * @return {void}
	 */
	#define ECHO(ID, args...) ({\
		__lib_echo_ ## ID ## __(args);\
	})

	/**
	 * Get the type of the level: debug (0) or error (1)
	 * @param {int} level - the log level
	 * @return {int} - the type of the log level
	 */
	#define __LIB_ECHO_GET_LEVEL_TYPE__(level) (level < LOG_LEVEL_INFO)

	/**
	 * Prints the log
	 * @param {int} level - the log level
	 * @param {char *} prefix - the log prefix
	 * @param {FILE *} output - the log stream output
	 * @return {void}
	 */
	#define __LIB_ECHO_EXECUTE__(level, prefix, output) ({\
		__lib_echo_init_stream__(level);\
		FILE *stream = output;\
		va_list args;\
		va_start(args, fmt);\
		fprintf(stream, "%s: ", prefix);\
		vfprintf(stream, fmt, args);\
		fprintf(stream, "\n");\
		va_end(args);\
		__lib_echo_quit_stream__();\
	})

	__SOF__

	/**
	 * Init log
	 * @returns {void}
	 */
	void __lib_echo_init__(void);

	/**
	 * Quit log
	 * @returns {void}
	 */
	void __lib_echo_quit__(void);

	/**
	 * Clean and reset the stdout and stderr
	 * @returns {void}
	 */
	void __lib_echo_quit_stream__(void);

	/**
	 * Sets the log level
	 * @param {int} level
	 * @returns {void}
	 */
	void __lib_echo_level__(int);

	/**
	 * Cleans the stdout pointer
	 * @returns {void}
	 */
	void __lib_echo_clean_data_stdout__();

	/**
	 * Cleans the stderr pointer
	 * @returns {void}
	 */
	void __lib_echo_clean_data_stderr__();

	void __lib_echo_set_std__(char *, const char *);

	/**
	 * Sets the output pointer to the standard output (stdout)
	 * or to a specified file
	 * @param {const char} file
	 * @returns {void}
	 */
	void __lib_echo_set_stdout__(const char *);

	/**
	 * Sets the error pointer to the standard error (stderr)
	 * or to a specified file
	 * @param {const char} file
	 * @returns {void}
	 */
	void __lib_echo_set_stderr__(const char *);

	/**
	 * Sets the output pointer to the standard output (stdout)
	 * @returns {void}
	 */
	void __lib_echo_reset_stdout__(const char *);

	/**
	 * Sets the error pointer to the standard error (stderr)
	 * @returns {void}
	 */
	void __lib_echo_reset_stderr__(const char *);

	/**
	 * Trigger the debug log
	 * @param {const char} fmt - the message format
	 * @param {any} ... - variadic arguments
	 * @returns {void}
	 */
	void __lib_echo_debug__(const char *, ...);

	/**
	 * Trigger the trace log
	 * @param {const char} fmt - the message format
	 * @param {any} ... - variadic arguments
	 * @returns {void}
	 */
	void __lib_echo_trace__(const char *, ...);

	/**
	 * Trigger the info log
	 * @param {const char} fmt - the message format
	 * @param {any} ... - variadic arguments
	 * @returns {void}
	 */
	void __lib_echo_info__(const char *, ...);

	/**
	 * Trigger the notice log
	 * @param {const char} fmt - the message format
	 * @param {any} ... - variadic arguments
	 * @returns {void}
	 */
	void __lib_echo_notice__(const char *, ...);

	/**
	 * Trigger the warning log
	 * @param {const char} fmt - the message format
	 * @param {any} ... - variadic arguments
	 * @returns {void}
	 */
	void __lib_echo_warning__(const char *, ...);

	/**
	 * Trigger the error log
	 * @param {const char} fmt - the message format
	 * @param {any} ... - variadic arguments
	 * @returns {void}
	 */
	void __lib_echo_error__(const char *, ...);

	__EOF__

#endif
