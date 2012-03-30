#include "config.h"

#include <sys/mman.h>
#include <sys/types.h>

#include "conv/flags_mmap_prot.h"
#include "mcsyscall.h"
#include "reerrno.h"

ssize_t MC_mprotect(const void *addr, size_t len, ssize_t prot)
{
    int ret;
    REERRNO(ret, mprotect, -1, (addr, len, MC_mmap_prot_g2h(prot)));
    return ret;
}
