#include "config.h"

#include <sys/types.h>

/* our IDs are fake */
ssize_t MC_getegid() { return 1; }
