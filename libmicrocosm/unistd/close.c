#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

ssize_t MC_close(ssize_t fd)
{
    int ret;
    REERRNO(ret, close, -1, (fd));
    return ret;
}
