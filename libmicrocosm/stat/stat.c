#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "reerrno.h"
#include "vfs/vfs.h"

long MC_stat(const char *path, struct MC_struct_stat *buf)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, path);
    REERRNO(ret, mount->fs->stat, -1, (mount->fsData, cpath, buf));
    free(cpath);
    return ret;
}
