#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

ssize_t MC_dup2(ssize_t oldfd, ssize_t newfd)
{
    int ret;
    REERRNO(ret, dup2, -1, (oldfd, newfd));
    return ret;
}
