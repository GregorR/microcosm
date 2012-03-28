#include "config.h"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

ssize_t MC_fork()
{
    pid_t ret;
    REERRNO(ret, fork, -1, ());
    return ret;
}
