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

#ifndef EB_PLATFORM_H
#define EB_PLATFORM_H

/*
 * DOS-style file paths are used on Windows.
 */
#ifdef _WIN32
#define DOS_FILE_PATH
#endif

/*
 * Common system headers.
 */
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
 * <unistd.h> is a POSIX header; on Windows the equivalent declarations
 * live in <io.h> and <process.h>.
 */
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <process.h>
#define getcwd _getcwd
#define getdcwd _getdcwd
#else
#include <unistd.h>
#endif

/*
 * Provide ssize_t for platforms that lack it (e.g. MSVC).
 * POSIX defines ssize_t as the signed counterpart of size_t; we use
 * intptr_t so the width matches the platform pointer size on both
 * 32-bit and 64-bit builds.
 */
#if defined(_MSC_VER) && !defined(_SSIZE_T_DEFINED) && !defined(_SSIZE_T) &&   \
    !defined(__ssize_t_defined)
#define _SSIZE_T_DEFINED
#define _SSIZE_T
#define __ssize_t_defined
typedef intptr_t ssize_t;
#endif

/*
 * Pthreads support.  When ENABLE_PTHREAD is not defined, the lock
 * primitives become no-ops so callers don't need conditional code.
 */
#ifdef ENABLE_PTHREAD
#include <pthread.h>
#else
#define pthread_mutex_lock(m)
#define pthread_mutex_unlock(m)
#endif

/*
 * On POSIX, open() has no O_BINARY flag; define it to 0 there so
 * callers can pass it unconditionally.
 */
#ifndef O_BINARY
#define O_BINARY 0
#endif

/*
 * Test whether `off_t' is a large integer (64-bit).  Uses uint64_t
 * casts so the shift is well-defined even when off_t itself is 32-bit.
 */
#define off_t_is_large                                                         \
  (((off_t)((uint64_t)1 << 41) + (off_t)((uint64_t)1 << 40) + 1) % 9999991 ==  \
   7852006)

/*
 * ASCII character classification and case conversion.  Avoid <ctype.h>
 * to remain locale-independent.
 */
#define ASCII_ISDIGIT(c) ('0' <= (c) && (c) <= '9')
#define ASCII_ISUPPER(c) ('A' <= (c) && (c) <= 'Z')
#define ASCII_ISLOWER(c) ('a' <= (c) && (c) <= 'z')
#define ASCII_ISALPHA(c) (ASCII_ISUPPER(c) || ASCII_ISLOWER(c))
#define ASCII_ISALNUM(c)                                                       \
  (ASCII_ISUPPER(c) || ASCII_ISLOWER(c) || ASCII_ISDIGIT(c))
#define ASCII_ISXDIGIT(c)                                                      \
  (ASCII_ISDIGIT(c) || ('A' <= (c) && (c) <= 'F') || ('a' <= (c) && (c) <= 'f'))
#define ASCII_TOUPPER(c) (('a' <= (c) && (c) <= 'z') ? (c) - 0x20 : (c))
#define ASCII_TOLOWER(c) (('A' <= (c) && (c) <= 'Z') ? (c) + 0x20 : (c))

/*
 * gettext shims (NLS is not supported) live in eb_internal.h so they do not
 * leak to library consumers via the public zio.h -> eb_platform.h chain.
 */

/*
 * Route strcasecmp/strncasecmp to the EB-provided fallbacks when the
 * platform doesn't expose them.
 */
#ifndef HAVE_STRCASECMP
#define strcasecmp eb_strcasecmp
#define strncasecmp eb_strncasecmp
#endif

#endif /* EB_PLATFORM_H */
