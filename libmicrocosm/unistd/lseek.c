#include <sys/types.h>
#include <unistd.h>

#include "conv/enum_seek.h"
#include "reerrno.h"

off_t MC_lseek(long fd, off_t offset, long whence)
{
    off_t ret;
    REERRNO(ret, lseek, -1, (fd, offset, MC_seek_g2h(whence)));
    return ret;
}
