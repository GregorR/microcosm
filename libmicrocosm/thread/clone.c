#define _GNU_SOURCE /* for clone */

#include "config.h"

#include <sched.h>
#include <stdio.h>

#include "conv/flags_clone.h"
#include "mcerrno.h"
#include "reerrno.h"

/* FIXME: This makes TONS of musl assumptions */

struct pthread {
    struct pthread *self;
    pid_t tid;
    /* don't care about the rest */
};

ssize_t MC_clone(int (*fn)(void *), void *child_stack, int flags, void *arg,
#ifdef __linux__
    struct pthread *ptls, struct pthread *ctls
#else
    void *ptls, void *ctls
#endif
    )
{
#if defined(__linux__) && defined(CLONE_THREAD)
    int ret;
    /* makin' the flags all kinds of broken */
    flags &= ~CLONE_PARENT_SETTID;
    flags &= ~CLONE_SETTLS;
    flags &= ~CLONE_CHILD_CLEARTID;
    flags &= ~CLONE_CHILD_SETTID;
    /* we can probably use host clone */
    fprintf(stderr, "[microcosm] Host clone call: %p %p %lX %p %p %p\n",
        (void *) (ssize_t) fn, child_stack, (long) flags, arg, ptls, ctls); 
    REERRNO(ret, clone, -1, (fn, child_stack, flags, arg));
    fprintf(stderr, "[microcosm] clone returned %d\n", ret);
    return ret;
#else
    return -MC_ENOSYS;
#endif
}
