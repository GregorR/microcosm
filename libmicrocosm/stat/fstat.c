#include <sys/stat.h>

#include "reerrno.h"
#include "vfs/vfs.h"

long MC_fstat(int fd, struct MC_struct_stat *buf)
{
    int ret;
    struct stat hbuf;
    REERRNO(ret, fstat, -1, (fd, &hbuf));
    if (ret >= 0)
        MC_struct_stat_h2g(buf, &hbuf);
    return ret;
}
