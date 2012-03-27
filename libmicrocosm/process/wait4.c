#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "conv/flags_wait.h"
#include "conv/struct_timeval.h"
#include "reerrno.h"

/* FIXME: use rusage */
struct MC_struct_rusage
{
    struct MC_struct_timeval ru_utime;
    struct MC_struct_timeval ru_stime;
    ssize_t    ru_maxrss;
    ssize_t    ru_ixrss;
    ssize_t    ru_idrss;
    ssize_t    ru_isrss;
    ssize_t    ru_minflt;
    ssize_t    ru_majflt;
    ssize_t    ru_nswap;
    ssize_t    ru_inblock;
    ssize_t    ru_oublock;
    ssize_t    ru_msgsnd;
    ssize_t    ru_msgrcv;
    ssize_t    ru_nsignals;
    ssize_t    ru_nvcsw;
    ssize_t    ru_nivcsw;
    ssize_t    __reserved[16];
};

/* FIXME: abstraction layer for pids */

ssize_t MC_wait4(ssize_t pid, int *status, ssize_t options, void *rusage)
{
    pid_t ret;
    REERRNO(ret, waitpid, -1, (pid, status, MC_wait_g2h(options)));
    if (ret >= 0) {
        if (rusage)
            /* just blank it */
            memset(rusage, 0, sizeof(struct MC_struct_rusage));
    }
    return ret;
}
