#ifndef VFS_H
#define VFS_H

#include <sys/types.h>

#include "conv/struct_stat.h"

#define MC_VFS_MOUNT_PATH_MAX 255

struct MC_VFS_FS {
    char *name;
    void (*info)(void *, char *, int);
    int (*stat)(void *, const char *path, struct MC_struct_stat *buf);
    int (*open)(void *, const char *path, int flags, int mode);
    ssize_t (*readlink)(void *, const char *path, char *buf, size_t bufsiz);
    int (*access)(void *, const char *pathname, int mode);
};

struct MC_VFS_Mount {
    char path[MC_VFS_MOUNT_PATH_MAX];
    int pathlen;
    struct MC_VFS_FS *fs;
    void *fsData;
    struct MC_VFS_Mount *prev, *next;
};

extern struct MC_VFS_Mount *MC_mounts;

/* canonicalize a pathname and get its mount (allocates!) */
char *MC_canonicalize(struct MC_VFS_Mount **mount, const char *path);

#endif
