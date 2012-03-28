#include "config.h"

#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

/* FIXME: need an abstraction layer for pids */
ssize_t MC_getppid()
{
    pid_t ret;
    REERRNO(ret, getppid, -1, ());
    return ret;
}
