/* our IDs are fake */
#include "mcerrno.h"

long MC_setuid(long id) {
    if (id == 1) return 0;
    return -MC_EPERM;
}
