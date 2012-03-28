#define _SVID_SOURCE /* for strdup */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conv/buffer.h"
#include "vfs/vfs.h"

struct MC_VFS_Mount *MC_mounts = NULL;

/* canonicalize a pathname (allocates!) */
char *MC_canonicalize(struct MC_VFS_Mount **mount, const char *path)
{
    /* FIXME: do something */
    char *ret;

    SF(ret, strdup, NULL, (path));
    if (mount) *mount = MC_mounts;

    return ret;
}
