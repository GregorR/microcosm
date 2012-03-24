#include <alloca.h>
#include <sys/uio.h>

#include "reerrno.h"
#include "conv/struct_iovec.h"
#include "visibility.h"

VISIBLE ssize_t MC_writev(long fd, const struct MC_struct_iovec *iov, long iovcnt)
{
    ssize_t ret;
    struct iovec *h_iov = alloca(sizeof(struct iovec) * iovcnt);
    int i;
    for (i = 0; i < iovcnt; i++) {
        MC_struct_iovec_g2h(h_iov + i, iov + i);
    }
    REERRNO(ret, writev, -1, (fd, h_iov, iovcnt));
    return ret;
}
