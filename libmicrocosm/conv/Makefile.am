AUTOMAKE_OPTIONS = foreign

BUILT_SOURCES = \
    flags_open.h \
    struct_iovec.h \
    struct_stat.h

CLEANFILES = $(BUILT_SOURCES)

noinst_PROGRAMS = convgen
convgen_SOURCES = convgen.c

%.h: %.conv convgen$(EXEEXT)
	$(target)-gcc -E - < $< | ./convgen$(EXEEXT) $(CC) $(CFLAGS) $(LDFLAGS) -x c - > $@
