#include "config.h"

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"
#include "vfs/vfs.h"

ssize_t MC_access(const char *pathname, ssize_t mode)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, pathname);
    REERRNO(ret, mount->fs->access, -1, (mount->fsData, cpath, mode));
    free(cpath);
    return ret;
}
