#define _GNU_SOURCE /* for execvpe */

#include "config.h"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "halloca.h"
#include "reerrno.h"

extern char **environ;

/* FIXME: this should use VFS */

ssize_t MC_execve(char *filename, char *argv[], char *envp[])
{
    int ret;
    char **subargv;
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

#if defined(HAVE_EXECVPE)
    REERRNO(ret, execvpe, -1, (subargv[0], subargv, envp));
#elif defined(HAVE_EXECVP)
    /* FIXME: We don't pass the environment properly, and won't until I get a
     * proper implementation of path searching over the VFS */
    REERRNO(ret, execvp, -1, (subargv[0], subargv));
#else
#error No execvpe!
#endif

    return ret;
}
