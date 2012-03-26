#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

ssize_t MC_read(ssize_t fd, void *buf, size_t count)
{
    ssize_t ret;
    REERRNO(ret, read, -1, (fd, buf, count));
    return ret;
}
