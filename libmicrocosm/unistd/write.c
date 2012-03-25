#include <unistd.h>

#include "reerrno.h"

ssize_t MC_write(long fd, void *buf, size_t count)
{
    ssize_t ret;
    REERRNO(ret, write, -1, (fd, buf, count));
    return ret;
}
