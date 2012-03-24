#include <stdlib.h>
#include <unistd.h>

#include "reerrno.h"
#include "vfs/vfs.h"

long MC_unlink(const char *pathname)
{
    long ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, pathname);
    REERRNO(ret, mount->fs->unlink, -1, (mount->fsData, cpath));
    free(cpath);
    return ret;
}
