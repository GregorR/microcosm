#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

#include "reerrno.h"
#include "vfs/vfs.h"

ssize_t MC_open(const char *path, ssize_t flags, ssize_t mode)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, path);
    REERRNO(ret, mount->fs->open, -1, (mount->fsData, cpath, flags, mode));
    free(cpath);
    return ret;
}
