/** This file is part of the Mingw32 package.

unistd.h maps (roughly) to io.h
*/
#ifndef _UNISTD_H
#define _UNISTD_H

#if defined( __APPLE__) || defined(__linux__)
#include <unistd.h>
#else
#include <io.h>
#include <process.h>
#endif
#endif /* _UNISTD_H */
