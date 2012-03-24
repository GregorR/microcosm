#include <alloca.h>
#include <stdio.h>
#include <unistd.h>

#include "reerrno.h"

/* FIXME: this should use VFS */

long MC_execve(const char *filename, char *const argv[], char *const envp[])
{
    int ret;
    char const **subargv;
    int argc;

    /* extend it to microcosm -m filename argv[1..] */
    for (argc = 0; argv[argc]; argc++);
    subargv = alloca((argc + 3) * sizeof(char *));
    subargv[0] = "microcosm";
    subargv[1] = "-m";
    subargv[2] = filename;
    for (argc = 1; argv[argc]; argc++) {
        subargv[argc+2] = argv[argc];
    }
    subargv[argc+2] = NULL;

    REERRNO(ret, execvpe, -1, (subargv[0], subargv, envp));

    return ret;
}
