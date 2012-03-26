#include <sys/types.h>
#include <sys/wait.h>

#include "conv/flags_wait.h"
#include "reerrno.h"

/* FIXME: use rusage */
/* FIXME: abstraction layer for pids */

ssize_t MC_wait4(ssize_t pid, int *status, ssize_t options, void *ignored)
{
    pid_t ret;
    REERRNO(ret, waitpid, -1, (pid, status, MC_wait_g2h(options)));
    return ret;
}
