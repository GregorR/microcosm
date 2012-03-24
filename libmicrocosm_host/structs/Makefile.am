AUTOMAKE_OPTIONS = foreign

BUILT_SOURCES = struct_iovec.h
CLEANFILES = $(BUILT_SOURCES)

noinst_PROGRAMS = structcgen
structcgen_SOURCES = structcgen.c

%.h: %.struct structcgen$(EXEEXT)
	$(CPP) - < $< | ./structcgen$(EXEEXT) $(CC) $(CFLAGS) $(LDFLAGS) -x c - > $@
