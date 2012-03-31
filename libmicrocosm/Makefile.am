AUTOMAKE_OPTIONS = foreign
SUBDIRS = conv

BUILT_SOURCES = mcsyscall.h mcerrno.h
CLEANFILES = $(BUILT_SOURCES) @hostlib_soname@ libmicrocosm.so libmicrocosm.so.1 libhost.so

blibdir = $(libdir)
tlibdir = $(prefix)/$(target)/lib
noinst_PROGRAMS = hostlib
blib_DATA = @hostlib_soname@
tlib_DATA = libmicrocosm.so libmicrocosm.so.1

hostlib_SOURCES = malloc.c syscall.c \
    \
    clock/clock_gettime.c \
    \
    fcntl/fcntl.c fcntl/open.c \
    \
    misc/ioctl.c \
    \
    mman/mmap.c mman/mprotect.c \
    \
    process/execve.c process/fork.c process/wait4.c \
    \
    select/poll.c \
    \
    stat/chmod.c stat/fstat.c stat/lstat.c stat/stat.c stat/umask.c \
    \
    thread/clone.c \
    \
    time/gettimeofday.c time/times.c \
    \
    unistd/access.c unistd/close.c unistd/dup2.c unistd/getcwd.c \
    unistd/getegid.c unistd/geteuid.c unistd/getgid.c unistd/getpid.c \
    unistd/getppid.c unistd/getuid.c unistd/lseek.c unistd/pipe.c unistd/read.c \
    unistd/readlink.c unistd/readv.c unistd/setgid.c unistd/setuid.c \
    unistd/unlink.c unistd/write.c unistd/writev.c \
    \
    vfs/hostfs.c vfs/vfs.c

hostlib_CFLAGS = -fPIC
#hostlib_LDFLAGS = -shared -Wl,-soname,@hostlib_soname@
# FIXME: I'd like to have the soname right, although it doesn't matter. Need to
# check in configure if we can use -soname.
hostlib_LDFLAGS = -shared

# FIXME: This is plainly wrong, but I don't know how to fix it
mcsyscall.h: target-syscall.h
	$(target)-gcc -E -dD $< | grep '^#[^ ]* SYS_' | sed 's/ / MC_/ ; s/\([ (]\)SYS/\1MC_SYS/g' > $@

mcerrno.h: target-errno.h
	$(target)-gcc -E -dD $< | grep '#[^ ]* E' | sed 's/ / MC_/' > $@

@hostlib_soname@: hostlib$(EXEEXT)
	cp -f hostlib$(EXEEXT) @hostlib_soname@
	-chmod a+x @hostlib_soname@

TARGET_CFLAGS=-shared -nostdlib -ffreestanding -fPIC

libmicrocosm.so: names.c
	$(CC_FOR_TARGET) $(TARGET_CFLAGS) $< -Wl,-soname,libmicrocosm.so.1 -o $@

libhost.so: empty.c
	$(CC_FOR_TARGET) $(TARGET_CFLAGS) $< -Wl,-soname,libhost_@hostlib_soname@ -o $@

libmicrocosm.so.1: empty.c libhost.so
	$(CC_FOR_TARGET) $(TARGET_CFLAGS) $< libhost.so -Wl,-soname,$@ -o $@
