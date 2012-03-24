#include <sys/types.h>
#include <sys/wait.h>

#include "conv/flags_wait.h"
#include "reerrno.h"

/* FIXME: use rusage */
/* FIXME: abstraction layer for pids */

long MC_wait4(long pid, int *status, long options, void *ignored)
{
    pid_t ret;
    REERRNO(ret, waitpid, -1, (pid, status, MC_wait_g2h(options)));
    return ret;
}
