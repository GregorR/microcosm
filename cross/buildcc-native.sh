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

# Switch to the native prefix for all of this
PREFIX="$MICROCOSM_NATIVE_PREFIX"

BINUTILS_VERSION=2.22
GCC_VERSION=4.7.0

# binutils
fetchextract http://ftp.gnu.org/gnu/binutils/ binutils-$BINUTILS_VERSION .tar.bz2
buildinstall n1 binutils-$BINUTILS_VERSION --host=$TRIPLE --target=$TRIPLE

# gcc 1
fetchextract http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/ gcc-$GCC_VERSION .tar.bz2
buildinstall n1 gcc-$GCC_VERSION --host=$TRIPLE --target=$TRIPLE \
    --enable-languages=c
