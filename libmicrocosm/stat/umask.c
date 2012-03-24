#include <sys/types.h>
#include <sys/stat.h>

#include "reerrno.h"

long MC_umask(long mask)
{
    long ret;
    REERRNO(ret, umask, -1, (mask));
    return ret;
}
