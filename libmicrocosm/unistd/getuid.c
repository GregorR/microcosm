#include <sys/types.h>

/* our IDs are fake */
ssize_t MC_getuid() { return 1; }
