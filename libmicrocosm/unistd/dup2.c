#include <unistd.h>

#include "reerrno.h"

long MC_dup2(long oldfd, long newfd)
{
    long ret;
    REERRNO(ret, dup2, -1, (oldfd, newfd));
    return ret;
}
