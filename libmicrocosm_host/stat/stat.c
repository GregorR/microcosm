#include <sys/stat.h>

#include "reerrno.h"
#include "conv/struct_stat.h"

long MC_stat(const char *path, struct MC_struct_stat *buf)
{
    struct stat hbuf;
    int ret;
    REERRNO(ret, stat, -1, (path, &hbuf));
    if (ret >= 0) {
        MC_struct_stat_h2g(buf, &hbuf);
    }
    return ret;
}
