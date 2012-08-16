/* most important mmap flags are unspecified */
#define _GNU_SOURCE
#define _BSD_SOURCE

#include "config.h"

#include <sys/mman.h>
#include <sys/types.h>

#include "conv/flags_mmap.h"
#include "conv/flags_mmap_prot.h"
#include "mcsyscall.h"
#include "reerrno.h"

void *MC_mmap(void *addr, size_t length, ssize_t prot, ssize_t flags, ssize_t fd, ssize_t offset)
{
    ssize_t ret;
    REERRNO(ret, (ssize_t) mmap, -1, (addr, length, MC_mmap_prot_g2h(prot),
        MC_mmap_g2h(flags), fd, offset));
    return (void *) ret;
}

#ifdef MC_SYS_mmap2
void *MC_mmap2(void *addr, size_t length, ssize_t prot, ssize_t flags, ssize_t fd,
    ssize_t pgoffset)
{
    long long offset = pgoffset * 4096; /* syscall is defined in terms of 4096-byte units, NOT pages */
    ssize_t ret;
    REERRNO(ret, (ssize_t) mmap, -1, (addr, length, MC_mmap_prot_g2h(prot),
        MC_mmap_g2h(flags), fd, offset));
    return (void *) ret;
}
#endif
