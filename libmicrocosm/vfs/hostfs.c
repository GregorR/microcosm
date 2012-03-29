#define _POSIX_C_SOURCE 200809L /* for struct timespec in struct stat */

#include "config.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "constructor.h"
#include "conv/flags_access.h"
#include "conv/flags_open.h"
#include "conv/helpers.h"
#include "vfs/vfs.h"

/* FIXME: this is a gross way to handle this */
#if defined(__STDC__)
# define PREDEF_STANDARD_C_1989
# if defined(__STDC_VERSION__)
#  define PREDEF_STANDARD_C_1990
#  if (__STDC_VERSION__ >= 199409L)
#   define PREDEF_STANDARD_C_1994
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define PREDEF_STANDARD_C_1999
#  endif
# endif
#endif
#ifdef PREDEF_STANDARD_C_1999
#define STRUCT_INIT(nm, val) .nm = val

#else
#define STRUCT_INIT(nm, val) val

#endif

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

static int hostFs_lstat(void *ignore, const char *path, struct MC_struct_stat *buf)
{
    struct stat hbuf;
    int ret = lstat(path, &hbuf);
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

static int hostFs_unlink(void *ignore, const char *pathname)
{
    return unlink(pathname);
}

static int hostFs_chmod(void *ignore, const char *path, mode_t mode)
{
    return chmod(path, mode);
}

static struct MC_VFS_FS hostFs = {
    STRUCT_INIT(name, "hostfs"),
    STRUCT_INIT(info, hostFs_info),
    STRUCT_INIT(stat, hostFs_stat),
    STRUCT_INIT(lstat, hostFs_lstat),
    STRUCT_INIT(open, hostFs_open),
    STRUCT_INIT(readlink, hostFs_readlink),
    STRUCT_INIT(access, hostFs_access),
    STRUCT_INIT(unlink, hostFs_unlink),
    STRUCT_INIT(chmod, hostFs_chmod)
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
