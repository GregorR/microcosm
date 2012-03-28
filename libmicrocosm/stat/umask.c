#include "config.h"

#include <sys/types.h>
#include <sys/stat.h>

#include "reerrno.h"

ssize_t MC_umask(ssize_t mask)
{
    mode_t ret;
    REERRNO(ret, umask, -1, (mask));
    return ret;
}
