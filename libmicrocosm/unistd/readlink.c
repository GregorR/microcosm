#include <stdlib.h>
#include <unistd.h>

#include "reerrno.h"
#include "vfs/vfs.h"

ssize_t MC_readlink(const char *path, char *buf, size_t bufsiz)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, path);
    REERRNO(ret, mount->fs->readlink, -1, (mount->fsData, cpath, buf, bufsiz));
    free(cpath);
    return ret;
}
