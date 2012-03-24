#ifndef REERRNO_H
#define REERRNO_H

#include <errno.h>

#define REERRNO(into, func, bad, args) \
do { \
    (into) = func args; \
    if ((into) == (bad)) { \
        (into) = -errno; \
    } \
} while (0)

#endif
