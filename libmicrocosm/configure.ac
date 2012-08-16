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

AC_ARG_VAR([CC_FOR_TARGET], [Target C compiler])
AC_CHECK_TARGET_TOOLS([CC_FOR_TARGET], [gcc cc])

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

# Can we do -std=c99 ?
AC_ARG_ENABLE(
    [std-c99],
    [AS_HELP_STRING(
        [--enable-std-c99],
        [Use -std=c99 compiler option [check]])],
    [use_std_c99=$enableval],
    [use_std_c99=check])
if test x$use_std_c99 = xcheck; then
    AC_LANG([C])
    OCFLAGS="$CFLAGS"
    CFLAGS="$CFLAGS -std=c99"
    export CFLAGS
    AC_COMPILE_IFELSE([AC_LANG_SOURCE([int foo;])], [
        use_std_c99=yes
    ], [
        use_std_c99=no
    ])
    CFLAGS="$OCFLAGS"
    export CFLAGS
fi
if test x$use_std_c99 = xyes; then
    CFLAGS="$CFLAGS -std=c99"
    export CFLAGS
fi

# Can we do -fvisibility=hidden ?
AC_ARG_ENABLE(
    [visibility-hidden],
    [AS_HELP_STRING(
        [--enable-visibility-hidden],
        [Use -fvisibility=hidden compiler option [check]])],
    [use_visibility_hidden=$enableval],
    [use_visibility_hidden=check])
if test x$use_visibility_hidden = xcheck; then
    AC_LANG([C])
    OCFLAGS="$CFLAGS"
    CFLAGS="$CFLAGS -fvisibility=hidden"
    export CFLAGS
    AC_COMPILE_IFELSE([AC_LANG_SOURCE([int foo;])], [
        use_visibility_hidden=yes
    ], [
        use_visibility_hidden=no
    ])
    CFLAGS="$OCFLAGS"
    export CFLAGS
fi
if test x$use_visibility_hidden = xyes; then
    CFLAGS="$CFLAGS -fvisibility=hidden"
    export CFLAGS
fi

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
