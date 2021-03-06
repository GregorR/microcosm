#include "config.h"

#include <sys/types.h>
#include <sys/uio.h>

#include "conv/struct_iovec.h"
#include "halloca.h"
#include "reerrno.h"

ssize_t MC_readv(ssize_t fd, const struct MC_struct_iovec *iov, ssize_t iovcnt)
{
    ssize_t ret;
    struct iovec *h_iov = alloca(sizeof(struct iovec) * iovcnt);
    int i;
    for (i = 0; i < iovcnt; i++) {
        MC_struct_iovec_g2h(h_iov + i, iov + i);
    }
    REERRNO(ret, readv, -1, (fd, h_iov, iovcnt));
    return ret;
}
