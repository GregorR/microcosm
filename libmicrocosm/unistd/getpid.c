#include "config.h"

#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

/* FIXME: need an abstraction layer for pids */
ssize_t MC_getpid()
{
    pid_t ret;
    REERRNO(ret, getpid, -1, ());
    return ret;
}
