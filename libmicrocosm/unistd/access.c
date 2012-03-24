#include <stdlib.h>
#include <unistd.h>

#include "reerrno.h"
#include "vfs/vfs.h"

long MC_access(const char *pathname, long mode)
{
    long ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, pathname);
    REERRNO(ret, mount->fs->access, -1, (mount->fsData, cpath, mode));
    free(cpath);
    return ret;
}
