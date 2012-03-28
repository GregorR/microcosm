#include "config.h"

#include <sys/types.h>

/* our IDs are fake */
#include "mcerrno.h"

ssize_t MC_setuid(ssize_t id) {
    if (id == 1) return 0;
    return -MC_EPERM;
}
