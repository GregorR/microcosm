#include <sys/types.h>
#include <unistd.h>

#include "conv/enum_seek.h"
#include "mcsyscall.h"
#include "reerrno.h"

ssize_t MC_lseek(ssize_t fd, ssize_t offset, ssize_t whence)
{
    off_t ret;
    REERRNO(ret, lseek, -1, (fd, offset, MC_seek_g2h(whence)));
    return ret;
}

#ifdef MC_SYS__llseek
ssize_t MC__llseek(size_t fd, size_t offset_high, size_t offset_low,
    long long *result, size_t whence)
{
    long long offset;
    off_t ret;

    /* get the real offset */
    offset = offset_high;
    offset <<= 32;
    offset += offset_low;

    REERRNO(ret, lseek, -1, (fd, offset, MC_seek_g2h(whence)));

    if (ret >= 0 && result) {
        *result = ret;
        ret = 0;
    }

    return ret;
}
#endif
