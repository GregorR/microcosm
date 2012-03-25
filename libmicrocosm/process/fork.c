#include <stdio.h>
#include <unistd.h>

#include "reerrno.h"

long MC_fork()
{
    pid_t ret;
    REERRNO(ret, fork, -1, ());
    return ret;
}
