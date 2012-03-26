#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "reerrno.h"
#include "vfs/vfs.h"

ssize_t MC_realstat(const char *path, struct MC_struct_stat *buf)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, path);
    REERRNO(ret, mount->fs->realstat, -1, (mount->fsData, cpath, buf));
    free(cpath);
    return ret;
}
