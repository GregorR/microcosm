#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mcerrno.h"
#include "mcsyscall.h"
#include "reerrno.h"
#include "visibility.h"

/* FIXME: this is a gross way to handle this */
#define FW(nm) long MC_##nm(long, ...)
FW(read); /* 0 */
FW(open); /* 2 */
FW(close); /* 3 */
FW(stat); /* 4 */
FW(fstat); /* 5 */
FW(lstat); /* 6 */
FW(lseek); /* 8 */
FW(mmap); /* 9 */
FW(readv); /* 19 */
FW(writev); /* 20 */
FW(access); /* 21 */
FW(dup2); /* 33 */
FW(getpid); /* 39 */
FW(execve); /* 59 */
FW(wait4); /* 61 */
FW(fcntl); /* 72 */
FW(getcwd); /* 79 */
FW(unlink); /* 87 */
FW(readlink); /* 89 */
FW(chmod); /* 90 */
FW(umask); /* 95 */
FW(gettimeofday); /* 96 */
FW(getuid); /* 102 */
FW(getgid); /* 104 */
FW(setuid); /* 105 */
FW(setgid); /* 106 */
FW(geteuid); /* 107 */
FW(getegid); /* 108 */
#undef FW

/* wrapped syscalls (simple case) */
#define W(nm) case MC_SYS_##nm: return MC_##nm(a, b, c, d, e, f)

VISIBLE long microcosm____syscall(long n, long a, long b, long c, long d, long e, long f)
{
    long ret;

    /* FIXME: autogen in some way */
#ifdef MICROCOSM_DEBUG
    fprintf(stderr, "[microcosm] Syscall %ld.\n", n);
#endif
    switch (n) {
        case -1:
            fprintf(stderr, "[microcosm] Generic debug: %ld %ld %ld %ld %ld %ld!\n", a, b, c, d, e, f);
            break;

        /* wrapped calls */
        W(read);
        W(open);
        W(close);
        W(stat);
        W(fstat);
        W(lstat);
        W(lseek);
        W(mmap);
        W(readv);
        W(writev);
        W(access);
        W(dup2);
        W(getpid);
        W(execve);
        W(wait4);
        W(fcntl);
        W(getcwd);
        W(unlink);
        W(readlink);
        W(chmod);
        W(umask);
        W(gettimeofday);
        W(getuid);
        W(getgid);
        W(setuid);
        W(setgid);
        W(geteuid);
        W(getegid);

        case MC_SYS_exit_group: /* 231 */
            /* generally just exit: FIXME, exit doesn't really work */
            _exit(a);
            abort();
            *((int *) 0) = 0;
            while (1);
            break;

        /* unsupported syscalls */
        case MC_SYS_brk: /* 12 */
        case MC_SYS_rt_sigaction: /* 13 */
        case MC_SYS_ioctl: /* 16 */
        case MC_SYS_getrlimit: /* 97 */
        case MC_SYS_getrusage: /* 98 */
        case MC_SYS_set_tid_address: /* 218 */
        case MC_SYS_clock_gettime: /* 228 */
        case MC_SYS_prlimit64: /* 302 */
            return -MC_ENOSYS;

        default:
            fprintf(stderr, "[microcosm] Unsupported syscall %ld.\n", n);
#ifdef __linux__
            ret = syscall(n, a, b, c, d, e, f);
            if (ret == -1) ret = -errno;
            fprintf(stderr, "[microcosm] %ld(%lX, %lX, %lX, %lX, %lX, %lX) = %lX\n", n, a, b, c, d, e, f, ret);
            return ret;
#else
            fprintf(stderr, "[microcosm] Returning ENOSYS.\n");
            return -MC_ENOSYS;
#endif
    }
}

VISIBLE long microcosm____syscall_cp(long n, long a, long b, long c, long d, long e, long f)
{
    /* FIXME: really do the _cp part */
    return microcosm____syscall(n, a, b, c, d, e, f);
}
