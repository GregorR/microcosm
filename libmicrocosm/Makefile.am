AUTOMAKE_OPTIONS = foreign
SUBDIRS = conv

BUILT_SOURCES = mcsyscall.h mcerrno.h
CLEANFILES = $(BUILT_SOURCES) @hostlib_soname@ libmicrocosm.so libmicrocosm.so.1 libhost.so

blibdir = $(libdir)
tlibdir = $(prefix)/$(target)/lib
noinst_PROGRAMS = hostlib
blib_DATA = @hostlib_soname@
tlib_DATA = libmicrocosm.so libmicrocosm.so.1

hostlib_SOURCES = syscall.c \
    \
    stat/stat.c \
    \
    unistd/getcwd.c unistd/getgid.c unistd/getuid.c unistd/setgid.c \
    unistd/setuid.c unistd/writev.c \
    \
    vfs/hostfs.c vfs/vfs.c

hostlib_CFLAGS = -fPIC -fvisibility=hidden
hostlib_LDFLAGS = -shared -Wl,-soname,@hostlib_soname@

# FIXME: This is plainly wrong, but I don't know how to fix it
mcsyscall.h: target-syscall.h
	$(target)-gcc -E -dD $< | grep '^#[^ ]* SYS_' | sed 's/ / MC_/' > $@

mcerrno.h: target-errno.h
	$(target)-gcc -E -dD $< | grep '#[^ ]* E' | sed 's/ / MC_/' > $@

@hostlib_soname@: hostlib$(EXEEXT)
	cp -f hostlib$(EXEEXT) @hostlib_soname@

libmicrocosm.so: names.c
	$(target)-gcc -shared -nostdlib -fPIC $< -Wl,-soname,libmicrocosm.so.1 -o $@

libhost.so: empty.c
	$(target)-gcc -shared -nostdlib -fPIC $< -Wl,-soname,libhost_@hostlib_soname@ -o $@

libmicrocosm.so.1: empty.c libhost.so
	$(target)-gcc -shared -nostdlib -fPIC $< libhost.so -Wl,-soname,$@ -o $@
