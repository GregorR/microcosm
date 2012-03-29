#include "config.h"

#include <poll.h>
#include <sys/types.h>

#include "conv/struct_pollfd.h"
#include "halloca.h"
#include "reerrno.h"

ssize_t MC_poll(struct MC_struct_pollfd *fds, size_t nfds, ssize_t timeout)
{
    struct pollfd *hfds;
    int ret;
    size_t si;

    /* convert the structs */
    hfds = alloca(sizeof(struct pollfd) * nfds);
    for (si = 0; si < nfds; si++) {
        MC_struct_pollfd_g2h(hfds + si, fds + si);
    }
    REERRNO(ret, poll, -1, (hfds, nfds, timeout));
    return ret;
}
