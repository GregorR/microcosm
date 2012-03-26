#include <sys/mman.h>
#include <sys/types.h>

#include "conv/flags_mmap.h"
#include "conv/flags_mmap_prot.h"
#include "reerrno.h"

void *MC_mmap(void *addr, size_t length, ssize_t prot, ssize_t flags, ssize_t fd, off_t offset)
{
    ssize_t ret;
    REERRNO(ret, (ssize_t) mmap, -1, (addr, length, MC_mmap_prot_g2h(prot),
        MC_mmap_g2h(flags), fd, offset));
    return (void *) ret;
}
