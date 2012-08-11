#include "config.h"

#include <stdio.h>
#include <sys/ioctl.h>
/* FIXME: check for termios.h */
#include <termios.h>

#include "conv/enum_ioctl_request.h"
#include "conv/struct_termios.h"
#include "conv/struct_winsize.h"
#include "mcerrno.h"
#include "reerrno.h"

ssize_t MC_ioctl(ssize_t fd, ssize_t request, ssize_t c, ssize_t d, ssize_t e, ssize_t f)
{
    ssize_t hrequest = MC_ioctl_request_g2h(request);
    ssize_t ret = -MC_ENOSYS;

    (void) hrequest; /* to be used later */

    /* switch off the args on the type of request */
    switch (request) {
        case MC_TCGETS: /* 0x5401 */
        {
#ifdef TCGETS
            struct MC_struct_termios *gt = (struct MC_struct_termios *) c;
            struct termios ht;
            REERRNO(ret, ioctl, -1, (fd, TCGETS, &ht));
            if (ret >= 0)
                MC_struct_termios_h2g(gt, &ht);
#endif
            break;
        }

        case MC_TIOCGWINSZ: /* 0x5413 */
        {
#ifdef TIOCGWINSZ
            struct MC_struct_winsize *gw = (struct MC_struct_winsize *) c;
            struct winsize hw;
            REERRNO(ret, ioctl, -1, (fd, TIOCGWINSZ, &hw));
            if (ret >= 0)
                MC_struct_winsize_h2g(gw, &hw);
#endif
            break;
        }

        default:
            fprintf(stderr, "[microcosm] Unsupported ioctl request %ld.\n", (long) request);
    }

    return ret;
}
