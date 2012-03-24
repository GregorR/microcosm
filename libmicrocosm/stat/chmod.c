#include <stdlib.h>
#include <sys/stat.h>

#include "reerrno.h"
#include "vfs/vfs.h"

long MC_chmod(const char *path, long mode)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, path);
    REERRNO(ret, mount->fs->chmod, -1, (mount->fsData, chmod, mode));
    free(cpath);
    return ret;
}
