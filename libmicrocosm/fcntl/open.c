#include <fcntl.h>
#include <stdlib.h>

#include "reerrno.h"
#include "vfs/vfs.h"

long MC_open(const char *path, long flags, long mode)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, path);
    REERRNO(ret, mount->fs->open, -1, (mount->fsData, cpath, flags, mode));
    free(cpath);
    return ret;
}
