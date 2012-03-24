#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mcerrno.h"
#include "mcsyscall.h"
#include "reerrno.h"
#include "visibility.h"

/* FIXME: this is a gross way to handle this */
#define FW(nm) long MC_##nm(long, ...)
FW(writev);
#undef FW

/* wrapped syscalls (simple case) */
#define W(nm) case MC_SYS_##nm: return MC_##nm(a, b, c, d, e, f)

/* direct syscalls (simple case) */
#define D(nm, bad) case MC_SYS_##nm: REERRNO(ret, nm, bad, (a, b, c, d, e, f)); return ret

VISIBLE long __syscall(long n, long a, long b, long c, long d, long e, long f)
{
    long ret;

    /* FIXME: autogen in some way */
    fprintf(stderr, "[microcosm] Syscall %ld.\n", n);
    switch (n) {
        /* wrapped calls */
        W(writev);

        case MC_SYS_exit_group: /* 231 */
            /* generally just exit: FIXME, exit doesn't really work */
            _exit(a);
            abort();
            *((int *) 0) = 0;
            while (1);
            break;

        /* unsupported syscalls */
        case MC_SYS_brk: /* 12 */
        case MC_SYS_ioctl: /* 16 */
        case MC_SYS_set_tid_address: /* 218 */
            return -MC_ENOSYS;

        default:
            fprintf(stderr, "[microcosm] Unsupported syscall %ld.\n", n);
#ifdef __linux__
            ret = syscall(n, a, b, c, d, e, f);
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
