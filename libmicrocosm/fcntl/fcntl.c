#include "config.h"

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "conv/enum_fcntl_cmd.h"
#include "conv/flags_open.h"
#include "conv/struct_flock.h"
#include "mcerrno.h"
#include "reerrno.h"

ssize_t MC_fcntl(ssize_t fd, ssize_t cmd, ssize_t arg)
{
    int ret;
    ssize_t hcmd = MC_fcntl_cmd_g2h(cmd);
    switch (cmd) {
        case MC_F_DUPFD:
        case MC_F_GETFD:
        case MC_F_SETFD:
        case MC_F_GETOWN:
        case MC_F_SETOWN:
            /* generic, no conversion needed */
            REERRNO(ret, fcntl, -1, (fd, hcmd, arg));
            break;

        case MC_F_GETFL:
            /* convert the flags on the way out */
            REERRNO(ret, fcntl, -1, (fd, hcmd, 0));
            if (ret >= 0)
                ret = MC_open_g2h(ret);
            break;

        case MC_F_SETFL:
            arg = MC_open_h2g(arg);
            REERRNO(ret, fcntl, -1, (fd, hcmd, arg));
            break;

        case MC_F_GETLK:
        case MC_F_SETLK:
        case MC_F_SETLKW:
        {
            /* each of these take a lock structure */
            struct flock hflock;
            MC_struct_flock_g2h(&hflock, (void *) arg);
            REERRNO(ret, fcntl, -1, (fd, hcmd, arg));
            if (ret >= 0)
                MC_struct_flock_h2g((void *) arg, &hflock);
            break;
        }

        default:
            ret = -MC_ENOSYS;
    }

    return ret;
}
