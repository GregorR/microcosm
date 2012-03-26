#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

char *MC_getcwd(char *buf, size_t size)
{
    ssize_t ret;
    REERRNO(ret, (ssize_t) getcwd, 0, (buf, size));
    return (char *) ret;
}
