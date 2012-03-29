#define _POSIX_C_SOURCE 200809L /* for struct timespec in struct stat */

#include "config.h"

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"
#include "vfs/vfs.h"

ssize_t MC_unlink(const char *pathname)
{
    int ret;
    char *cpath;
    struct MC_VFS_Mount *mount;
    cpath = MC_canonicalize(&mount, pathname);
    REERRNO(ret, mount->fs->unlink, -1, (mount->fsData, cpath));
    free(cpath);
    return ret;
}
