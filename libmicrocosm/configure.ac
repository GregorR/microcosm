#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([libmicrocosm_host], [0], [Richards@codu.org])
AC_CONFIG_SRCDIR([syscall.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([../scripts])

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP

# Figure out the backend name and location of non-shared files
case "$host" in
    *-*-mingw* | \
    *-*-cygwin*)
        hostlib_soname=microcosm_host-1.dll
        ;;
    *)
        hostlib_soname=libmicrocosm_host.so.1
        ;;
esac
AC_SUBST(hostlib_soname)

# Checks for libraries.
AC_SEARCH_LIBS([clock_gettime], [rt])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_SYS_LARGEFILE

# Can we do -fvisibility=hidden ?
AC_LANG([C])
OCFLAGS="$CFLAGS"
CFLAGS="$CFLAGS -fvisibility=hidden"
export CFLAGS
AC_COMPILE_IFELSE([], [], [
    CFLAGS="$OCFLAGS"
    export CFLAGS
])

# Checks for library functions.
AC_FUNC_ALLOCA
_AC_FUNC_MALLOC_IF([AC_DEFINE([HAVE_GOOD_MALLOC], 1, [Define if malloc(0) is non-NULL])], [])
_AC_FUNC_REALLOC_IF([AC_DEFINE([HAVE_GOOD_REALLOC], 1, [Define if realloc(?, 0) is non-NULL])], [])
AC_CHECK_FUNCS([clock_gettime execvp execvpe])

AC_CONFIG_FILES([
Makefile
conv/Makefile
])
AC_OUTPUT
