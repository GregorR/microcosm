AUTOMAKE_OPTIONS = foreign

BUILT_SOURCES = \
    struct_iovec.h \
    struct_stat.h

CLEANFILES = $(BUILT_SOURCES)

noinst_PROGRAMS = convgen
convgen_SOURCES = convgen.c

%.h: %.struct convgen$(EXEEXT)
	$(CPP) - < $< | ./convgen$(EXEEXT) $(CC) $(CFLAGS) $(LDFLAGS) -x c - > $@
