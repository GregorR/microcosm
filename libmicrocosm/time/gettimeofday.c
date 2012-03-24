#include <sys/time.h>

#include "conv/struct_timeval.h"
#include "mcerrno.h"
#include "reerrno.h"

long MC_gettimeofday(struct MC_struct_timeval *tv, void *tz)
{
    long ret;
    struct timeval htv;
    if (tz) return -MC_ENOSYS;;
    REERRNO(ret, gettimeofday, -1, (&htv, NULL));
    if (ret >= 0)
        MC_struct_timeval_h2g(tv, &htv);
    return ret;
}
