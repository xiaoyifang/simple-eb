#ifndef WIN_MSVC_H
#define WIN_MSVC_H

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#endif /* WIN_MSVC_H */