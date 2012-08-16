/* macro to get everything out of everyone w/ feature macros */
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600 /* do not set to 700: Solaris is awful */
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef __EXTENSIONS__
#define __EXTENSIONS__ 1
#endif
#ifndef __BSD_VISIBLE
#define __BSD_VISIBLE 1
#endif
