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

#include "eb.h"
#include "eb_internal.h"
#include "eb_platform.h"
#include "error.h"

#if defined(_WIN32)
#include <locale.h>
#endif

/*
 * Initialize the library.
 */
EB_Error_Code
eb_initialize_library(void)
{
    EB_Error_Code error_code;

    eb_initialize_log();

    LOG(("in: eb_initialize_library()"));
    LOG(("aux: EB Library version %s", EB_VERSION_STRING));

#if defined(_WIN32)
    /*
     * dirent's opendir() (tronkko/dirent, header-only) uses mbstowcs_s()
     * to convert narrow paths to wchar_t. mbstowcs_s() respects the
     * current LC_CTYPE locale, which defaults to the "C" locale on
     * Windows (ASCII-only). As a result, opendir() fails on any path
     * containing non-ASCII characters (e.g. CJK dictionary directories),
     * leading to EB_ERR_FAIL_OPEN_CAT at eb_bind() time.
     *
     * Switch LC_CTYPE to the ".utf-8" codepage so mbstowcs_s() treats
     * UTF-8 narrow strings correctly. This restores the behavior of the
     * previously-vendored win_dirent.h patch that did the same conversion
     * locally via _mbstowcs_s_l + _create_locale(".utf-8").
     */
    setlocale(LC_CTYPE, ".utf-8");
#endif

    eb_initialize_default_hookset();

    if (zio_initialize_library() < 0) {
	error_code = EB_ERR_MEMORY_EXHAUSTED;
	goto failed;
    }

    LOG(("out: eb_initialize_library() = %s", eb_error_string(EB_SUCCESS)));

    return EB_SUCCESS;

    /*
     * An error occurs...
     */
  failed:
    LOG(("out: eb_initialize_library() = %s", eb_error_string(error_code)));
    return error_code;
}


/*
 * Finalize the library.
 */
void
eb_finalize_library(void)
{
    LOG(("in: eb_finalize_library()"));

    zio_finalize_library();


    LOG(("out: eb_finalize_library()"));
}
