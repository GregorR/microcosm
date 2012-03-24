PREFIX=/opt/cross/x86_64-pc-microcosm/x86_64-pc-microcosm
CROSS_COMPILE=x86_64-pc-microcosm-
CC=$(CROSS_COMPILE)gcc

all: libmicrocosm.so

libmicrocosm.so: syscall.c
	$(CC) -shared -nostdlib -fPIC -Wl,-soname,libhost_libmicrocosm_host.so $< -o $@

clean:
	rm -f libmicrocosm.so

install:
	install -d $(PREFIX)/lib
	install -m 0755 libmicrocosm.so $(PREFIX)/lib/libmicrocosm.so
