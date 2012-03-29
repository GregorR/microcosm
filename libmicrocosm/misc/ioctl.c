#include "config.h"

#include <stdio.h>
#include <sys/ioctl.h>

#include "conv/enum_ioctl_request.h"
#include "mcerrno.h"
#include "reerrno.h"

ssize_t MC_ioctl(ssize_t fd, ssize_t request, ssize_t c, ssize_t d, ssize_t e, ssize_t f)
{
    ssize_t hrequest = MC_ioctl_request_g2h(request);
    ssize_t ret = -MC_ENOSYS;

    (void) hrequest; /* to be used later */

    /* switch off the args on the type of request */
    switch (request) {
        default:
            fprintf(stderr, "[microcosm] Unsupported ioctl request %ld.\n", (long) request);
    }

    return ret;
}
