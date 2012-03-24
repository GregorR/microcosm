AUTOMAKE_OPTIONS = foreign

BUILT_SOURCES = \
    enum_fcntl_cmd.h \
    enum_seek.h \
    flags_access.h \
    flags_mmap.h \
    flags_mmap_prot.h \
    flags_open.h \
    flags_wait.h \
    struct_flock.h \
    struct_iovec.h \
    struct_stat.h \
    struct_timeval.h

CLEANFILES = $(BUILT_SOURCES)

noinst_PROGRAMS = convgen
convgen_SOURCES = convgen.c

%.h: %.conv convgen$(EXEEXT)
	$(target)-gcc -E - < $< | ./convgen$(EXEEXT) $(CC) $(CFLAGS) $(LDFLAGS) -c -o /dev/null -x c - > $@
