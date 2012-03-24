#include <stdio.h>

#include "mcerrno.h"
#include "mcsyscall.h"
#include "visibility.h"

/* FIXME: this is a gross way to handle this */
#define F(nm) long MC_##nm(long, ...)
F(writev);
#undef F

#define W(nm) case MC_SYS_##nm: return MC_##nm(a, b, c, d, e, f)

VISIBLE long __syscall(long n, long a, long b, long c, long d, long e, long f)
{
    /* FIXME: autogen in some way */
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
        case MC_SYS_ioctl: /* 16 */
        case MC_SYS_set_tid_address: /* 218 */
            return -MC_ENOSYS;

        default:
            fprintf(stderr, "[microcosm] Unsupported syscall %ld.\n", n);
#ifdef __linux__
            fprintf(stderr, "[microcosm] Passing syscall to host.\n");
            return syscall(n, a, b, c, d, e, f);
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
