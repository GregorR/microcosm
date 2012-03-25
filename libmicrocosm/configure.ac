#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.6])
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

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([execvpe execvp])

AC_CONFIG_FILES([
Makefile
conv/Makefile
])
AC_OUTPUT
