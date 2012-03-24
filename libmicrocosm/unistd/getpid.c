#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

/* FIXME: need an abstraction layer for pids */
long MC_getpid()
{
    long ret;
    REERRNO(ret, getpid, -1, ());
    return ret;
}
