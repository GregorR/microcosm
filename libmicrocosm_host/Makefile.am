AUTOMAKE_OPTIONS = foreign
SUBDIRS = structs

BUILT_SOURCES = mcsyscall.h mcerrno.h
CLEANFILES = $(BUILT_SOURCES) libmicrocosm_host.so

blibdir = $(libdir)
noinst_PROGRAMS = hostlib
blib_DATA = libmicrocosm_host.so

hostlib_SOURCES = syscall.c \
    \
    stat/stat.c \
    \
    unistd/getcwd.c unistd/getgid.c unistd/getuid.c unistd/setgid.c \
    unistd/setuid.c unistd/writev.c

hostlib_CFLAGS = -fPIC -fvisibility=hidden
hostlib_LDFLAGS = -shared -Wl,-soname,libmicrocosm_host.so

# FIXME: This is plainly wrong, but I don't know how to fix it
mcsyscall.h: target-syscall.h
	$(target)-gcc -E -dD $< | grep '^#[^ ]* SYS_' | sed 's/ / MC_/' > $@

mcerrno.h: target-errno.h
	$(target)-gcc -E -dD $< | grep '#[^ ]* E' | sed 's/ / MC_/' > $@

libmicrocosm_host.so: hostlib$(EXEEXT)
	cp -f hostlib$(EXEEXT) libmicrocosm_host.so
