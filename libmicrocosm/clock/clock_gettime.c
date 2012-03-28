#include "config.h"

#include <sys/time.h>
#include <time.h>

#include "conv/enum_clockid.h"
#include "conv/struct_timespec.h"
#include "mcerrno.h"
#include "reerrno.h"

ssize_t MC_clock_gettime(ssize_t clk_id, struct MC_struct_timespec *tp)
{
    struct timeval tv;
    int ret;

    /* FIXME: use real clock_gettime */
    if (clk_id != MC_CLOCK_REALTIME) return -MC_ENOSYS;

    REERRNO(ret, gettimeofday, -1, (&tv, NULL));
    if (ret >= 0) {
        /* OK, convert it */
        tp->tv_sec = tv.tv_sec;
        tp->tv_nsec = tv.tv_usec * 1000L;
    }

    return ret;
}
