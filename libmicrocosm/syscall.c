#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mcerrno.h"
#include "mcsyscall.h"
#include "reerrno.h"
#include "visibility.h"

/* FIXME: this is a gross way to handle this */
#define FW(nm) long MC_##nm(long, ...)
FW(open); /* 2 */
FW(close); /* 3 */
FW(stat); /* 4 */
FW(fstat); /* 5 */
FW(writev); /* 20 */
FW(access); /* 21 */
FW(getcwd); /* 79 */
FW(readlink); /* 89 */
FW(getuid); /* 102 */
FW(getgid); /* 104 */
FW(setuid); /* 105 */
FW(setgid); /* 106 */
FW(geteuid); /* 107 */
FW(getegid); /* 108 */
#undef FW

/* wrapped syscalls (simple case) */
#define W(nm) case MC_SYS_##nm: return MC_##nm(a, b, c, d, e, f)

VISIBLE long __syscall(long n, long a, long b, long c, long d, long e, long f)
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
        W(open);
        W(close);
        W(stat);
        W(fstat);
        W(writev);
        W(access);
        W(getcwd);
        W(readlink);
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
        case MC_SYS_set_tid_address: /* 218 */
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

VISIBLE long __syscall_cp(long n, long a, long b, long c, long d, long e, long f)
{
    /* FIXME: really do the _cp part */
    return __syscall(n, a, b, c, d, e, f);
}
