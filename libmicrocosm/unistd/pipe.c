#include "config.h"

#include <sys/types.h>
#include <unistd.h>

#include "reerrno.h"

ssize_t MC_pipe(int *pipefd)
{
    int ret;
    REERRNO(ret, pipe, -1, (pipefd));
    return ret;
}
