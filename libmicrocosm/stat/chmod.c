#define _GNU_SOURCE /* for struct timespec in struct stat */

#include "config.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "reerrno.h"
#include "vfs/vfs.h"

ssize_t MC_chmod(const char *path, ssize_t mode)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, path);
    REERRNO(ret, mount->fs->chmod, -1, (mount->fsData, cpath, mode));
    free(cpath);
    return ret;
}
