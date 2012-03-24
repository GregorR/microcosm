#include <stdlib.h>

#include "constructor.h"
#include "conv/flags_access.h"
#include "conv/flags_open.h"
#include "conv/helpers.h"
#include "vfs/vfs.h"

static void hostFs_info(void *ignore, char *buf, int len)
{
    buf[0] = '\0';
}

static int hostFs_stat(void *ignore, const char *path, struct MC_struct_stat *buf)
{
    struct stat hbuf;
    int ret = stat(path, &hbuf);
    if (ret == 0)
        MC_struct_stat_h2g(buf, &hbuf);
    return ret;
}

static int hostFs_open(void *ignore, const char *path, int flags, int mode)
{
    int hflags = MC_open_g2h(flags);
    return open(path, hflags, mode);
}

static ssize_t hostFs_readlink(void *ignore, const char *path, char *buf, size_t bufsiz)
{
    return readlink(path, buf, bufsiz);
}

static int hostFs_access(void *ignore, const char *pathname, int mode)
{
    return access(pathname, MC_access_g2h(mode));
}

static struct MC_VFS_FS hostFs = {
    .name = "hostfs",
    .info = hostFs_info,
    .stat = hostFs_stat,
    .open = hostFs_open,
    .readlink = hostFs_readlink,
    .access = hostFs_access
};

CONSTRUCTOR static void hostfsInit()
{
    /* FIXME: only one mount right now */
    struct MC_VFS_Mount *mount;

    SF(mount, calloc, NULL, (1, sizeof(struct MC_VFS_Mount)));
    strcpy(mount->path, "/");
    mount->pathlen = 1;
    mount->fs = &hostFs;

    MC_mounts = mount;
}
