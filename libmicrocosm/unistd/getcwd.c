#include <unistd.h>

#include "reerrno.h"

char *MC_getcwd(char *buf, size_t size)
{
    size_t ret;
    REERRNO(ret, (size_t) getcwd, 0, (buf, size));
    return (char *) ret;
}
