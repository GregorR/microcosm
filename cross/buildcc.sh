#!/bin/bash -x
# Build a cross-compiler

if [ ! "$MICROCOSM_BASE" ]
then
    MICROCOSM_BASE="$PWD/.."
fi
SRCDIR="$MICROCOSM_BASE/cross"

# Fail on any command failing:
set -e

. "$MICROCOSM_BASE"/defs.sh

# Switch to the CC prefix for all of this
PREFIX="$CC_PREFIX"

BINUTILS_VERSION=2.22
GCC_VERSION=4.7.0

export PATH="$PREFIX/bin:$PATH"

# binutils
fetchextract http://ftp.gnu.org/gnu/binutils/ binutils-$BINUTILS_VERSION .tar.bz2
buildinstall 1 binutils-$BINUTILS_VERSION --target=$TRIPLE

# gcc 1
fetchextract http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/ gcc-$GCC_VERSION .tar.bz2
buildinstall 1 gcc-$GCC_VERSION --target=$TRIPLE \
    --enable-languages=c --with-newlib --disable-libssp --disable-libquadmath
