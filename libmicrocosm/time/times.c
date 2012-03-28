#include <sys/times.h>
#include <sys/types.h>

#include "conv/struct_tms.h"
#include "reerrno.h"

ssize_t MC_times(struct MC_struct_tms *buf)
{
    struct tms hbuf;
    clock_t ret;
    REERRNO(ret, times, -1, (&hbuf));
    if (ret >= 0)
        MC_struct_tms_h2g(buf, &hbuf);
    return ret;
}
