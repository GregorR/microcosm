#define _POSIX_C_SOURCE 200809L /* for dirfd, fdopendir */
#define _XOPEN_SOURCE 500 /* for seekdir, telldir */

/* Due to a bug on FreeBSD, it's impossible to see dirfd with any correct
 * visibility flags */
#define __BSD_VISIBLE 1

#include "config.h"

#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

#include "conv/struct_dirent.h"
#include "microcosmabi.h"
#include "reerrno.h"

VISIBLE MC_ABI int microcosm__closedir(void *dirp)
{
    return closedir(dirp);
}

VISIBLE MC_ABI int microcosm__dirfd(void *dirp)
{
    return dirfd((DIR *) dirp);
}

VISIBLE MC_ABI void *microcosm__fdopendir(int fd)
{
    return fdopendir(fd);
}

VISIBLE MC_ABI void *microcosm__opendir(const char *name)
{
    /* FIXME: VFS */
    return opendir(name);
}

VISIBLE MC_ABI int microcosm__readdir_r(void *dirp, struct MC_struct_dirent *gd, struct MC_struct_dirent **gr)
{
    struct dirent hd, *hr;
    int ret = readdir_r(dirp, &hd, &hr);
    if (ret == 0) {
        if (hr == NULL) {
            *gr = NULL;
        } else {
            MC_struct_dirent_h2g(gd, &hd);
            *gr = gd;
        }
    }
    return ret;
}

VISIBLE MC_ABI void *microcosm__readdir(void *dirp)
{
    static struct MC_struct_dirent gd;
    struct MC_struct_dirent *gr;
    int ret = microcosm__readdir_r(dirp, &gd, &gr);
    if (ret != 0 || gr == NULL) return NULL;
    return gr;
}

VISIBLE MC_ABI void microcosm__rewinddir(void *dirp)
{
    rewinddir(dirp);
}

VISIBLE MC_ABI void microcosm__seekdir(void *dirp, ssize_t offset)
{
    seekdir(dirp, offset);
}

VISIBLE MC_ABI ssize_t microcosm__telldir(void *dirp)
{
    return telldir(dirp);
}
