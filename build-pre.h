/*
 * Copyright (c) 2000-2006  Motoyuki Kasahara
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef EB_BUILD_PRE_H
#define EB_BUILD_PRE_H
#ifdef _WIN32
  #define DOS_FILE_PATH
#endif

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
/*
 * Platform abstraction for unistd.h.
 * unistd.h maps (roughly) to io.h on Windows.
 */
#if defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#else
#include <io.h>
#include <process.h>
#endif
#include <fcntl.h>

#if defined( _WIN32 )
  #include <direct.h>
#endif

#if defined( _WIN32 )
#define getcwd _getcwd
#define getdcwd _getdcwd
#endif

/*
 * Provide ssize_t for platforms that lack it (e.g. MSVC on Windows).
 * ssize_t is the signed counterpart of size_t, defined by POSIX.
 * We use intptr_t to match the pointer-size width on both 32-bit and 64-bit.
 */
#ifndef HAVE_SSIZE_T
#if defined(_MSC_VER)
#include <stdint.h>
#if !defined(_SSIZE_T_DEFINED) && !defined(_SSIZE_T) &&                        \
    !defined(__ssize_t_defined)
#define _SSIZE_T_DEFINED
#define _SSIZE_T
#define __ssize_t_defined
typedef intptr_t ssize_t;
#endif
#endif
#endif

#ifdef ENABLE_PTHREAD
#include <pthread.h>
#endif

/*
 * Mutual exclusion lock of Pthreads.
 */
#ifndef ENABLE_PTHREAD
#define pthread_mutex_lock(m)
#define pthread_mutex_unlock(m)
#endif

/*
 * Flags for open().
 */
#ifndef O_BINARY
#define O_BINARY 0
#endif

/*
 * Character type tests and conversions.
 */
#define ASCII_ISDIGIT(c) ('0' <= (c) && (c) <= '9')
#define ASCII_ISUPPER(c) ('A' <= (c) && (c) <= 'Z')
#define ASCII_ISLOWER(c) ('a' <= (c) && (c) <= 'z')
#define ASCII_ISALPHA(c) \
 (ASCII_ISUPPER(c) || ASCII_ISLOWER(c))
#define ASCII_ISALNUM(c) \
 (ASCII_ISUPPER(c) || ASCII_ISLOWER(c) || ASCII_ISDIGIT(c))
#define ASCII_ISXDIGIT(c) \
 (ASCII_ISDIGIT(c) || ('A' <= (c) && (c) <= 'F') || ('a' <= (c) && (c) <= 'f'))
#define ASCII_TOUPPER(c) (('a' <= (c) && (c) <= 'z') ? (c) - 0x20 : (c))
#define ASCII_TOLOWER(c) (('A' <= (c) && (c) <= 'Z') ? (c) + 0x20 : (c))

/*
 * Macros for gettext (always disabled; NLS not supported).
 */
#define _(string) (string)
#define N_(string) (string)

/*
 * Fake missing function names.
 */
#ifndef HAVE_STRCASECMP
#define strcasecmp eb_strcasecmp
#define strncasecmp eb_strncasecmp
#endif

#endif /* EB_BUILD_PRE_H */
