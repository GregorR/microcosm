#include <unistd.h>

#include "reerrno.h"

long MC_close(long fd)
{
    long ret;
    REERRNO(ret, close, -1, (fd));
    return ret;
}
