#ifdef __linux__
#define _GNU_SOURCE /* for syscall() */
#endif

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/syscall.h>
#endif

#include "mcerrno.h"
#include "mcsyscall.h"
#include "microcosmabi.h"
#include "reerrno.h"

/* FIXME: this is a gross way to handle this */
#define FW(nm) ssize_t MC_##nm(ssize_t, ...)
FW(read); /* 0 */
FW(write); /* 1 */
FW(open); /* 2 */
FW(close); /* 3 */
FW(stat); /* 4 */
FW(fstat); /* 5 */
FW(lstat); /* 6 */
FW(poll); /* 7 */
FW(lseek); /* 8 */
FW(mmap); /* 9 */
FW(mprotect); /* 10 */
FW(readv); /* 19 */
FW(writev); /* 20 */
FW(access); /* 21 */
FW(dup2); /* 33 */
FW(getpid); /* 39 */
FW(pipe); /* 42 */
FW(ioctl); /* 54 */
FW(clone); /* 56 */
FW(fork); /* 57 */
FW(execve); /* 59 */
FW(wait4); /* 61 */
FW(getppid); /* 64 */
FW(fcntl); /* 72 */
FW(getcwd); /* 79 */
FW(unlink); /* 87 */
FW(readlink); /* 89 */
FW(chmod); /* 90 */
FW(umask); /* 95 */
FW(gettimeofday); /* 96 */
FW(times); /* 100 */
FW(getuid); /* 102 */
FW(getgid); /* 104 */
FW(setuid); /* 105 */
FW(setgid); /* 106 */
FW(geteuid); /* 107 */
FW(getegid); /* 108 */
#ifdef MC_SYS__llseek
FW(_llseek);
#endif
#ifdef MC_SYS_mmap2
FW(mmap2); /* 192 */
#endif
FW(clock_gettime); /* 228 */
#undef FW

/* wrapped syscalls (simple case) */
#define W(nm) case MC_SYS_##nm: return MC_##nm(a, b, c, d, e, f)

VISIBLE MC_ABI ssize_t microcosm____syscall(ssize_t n, ssize_t a, ssize_t b, ssize_t c, ssize_t d, ssize_t e, ssize_t f)
{
    ssize_t ret;

    /* FIXME: autogen in some way */
#ifdef MICROCOSM_DEBUG
    fprintf(stderr, "[microcosm] Syscall %ld.\n", n);
#endif
    switch (n) {
        case -1:
            fprintf(stderr, "[microcosm] Generic debug: %ld %ld %ld %ld %ld %ld!\n", (long) a, (long) b, (long) c, (long) d, (long) e, (long) f);
            break;

        /* wrapped calls */
        W(read);
        W(write);
        W(open);
        W(close);
        W(stat);
        W(fstat);
        W(lstat);
        W(poll);
        W(lseek);
        W(mmap);
        W(mprotect);
        W(readv);
        W(writev);
        W(access);
        W(dup2);
        W(getpid);
        W(pipe);
        W(ioctl);
        W(clone);
        W(fork);
        W(execve);
        W(wait4);
        W(getppid);
        W(fcntl);
        W(getcwd);
        W(unlink);
        W(readlink);
        W(chmod);
        W(umask);
        W(gettimeofday);
        W(times);
        W(getuid);
        W(getgid);
        W(setuid);
        W(setgid);
        W(geteuid);
        W(getegid);
#ifdef MC_SYS__llseek
        W(_llseek);
#endif
#ifdef MC_SYS_mmap2
        W(mmap2);
#endif
        W(clock_gettime);

        case MC_SYS_exit_group: /* 231 */
            /* generally just exit: FIXME, exit doesn't really work */
            exit(a);
            abort();
            *((int *) 0) = 0;
            while (1);
            break;

        /* unsupported syscalls */
        case MC_SYS_brk: /* 12 */
        case MC_SYS_rt_sigaction: /* 13 */
        case MC_SYS_rt_sigprocmask: /* 14 */
        case MC_SYS_getrlimit: /* 97 */
        case MC_SYS_getrusage: /* 98 */
        case MC_SYS_set_thread_area: /* 205 */
        case MC_SYS_set_tid_address: /* 218 */
        case MC_SYS_prlimit64: /* 302 */
            return -MC_ENOSYS;

        default:
            fprintf(stderr, "[microcosm] Unsupported syscall %ld.\n", (long) n);
#ifdef __linux__
            ret = syscall(n, a, b, c, d, e, f);
            if (ret == -1) ret = -errno;
            fprintf(stderr, "[microcosm] %ld(%lX, %lX, %lX, %lX, %lX, %lX) = %lX\n", (long) n, (long) a, (long) b, (long) c, (long) d, (long) e, (long) f, (long) ret);
            return ret;
#else
            fprintf(stderr, "[microcosm] Returning ENOSYS.\n");
            return -MC_ENOSYS;
#endif
    }

    return -MC_ENOSYS;
}

VISIBLE MC_ABI ssize_t microcosm____syscall_cp(ssize_t n, ssize_t a, ssize_t b, ssize_t c, ssize_t d, ssize_t e, ssize_t f)
{
    /* FIXME: really do the _cp part */
    return microcosm____syscall(n, a, b, c, d, e, f);
}
