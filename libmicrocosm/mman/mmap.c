#include <sys/mman.h>

#include "conv/flags_mmap.h"
#include "conv/flags_mmap_prot.h"
#include "reerrno.h"

void *MC_mmap(void *addr, size_t length, long prot, long flags, long fd, off_t offset)
{
    long ret;
    REERRNO(ret, (long) mmap, -1, (addr, length, MC_mmap_prot_g2h(prot),
        MC_mmap_g2h(flags), fd, offset));
    return (void *) ret;
}
