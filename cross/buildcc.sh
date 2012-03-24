#!/bin/bash -x
# Build a cross-compiler

# Fail on any command failing:
set -e

PREFIX="/opt/cross/x86_64-pc-microcosm"
if [ "$1" ]
then
    PREFIX="$1"
fi
MAKEFLAGS="-j8"
if [ "$2" ]
then
    MAKEFLAGS="$2"
fi
SRCDIR="$(pwd)"
if [ "$3" ]
then
    SRCDIR="$3"
fi
TRIPLET="x86_64-pc-microcosm"
if [ "$4" ]
then
    TRIPLET="$4"
fi

BINUTILS_VERSION=2.22
GCC_VERSION=4.7.0
#NEWLIB_VERSION=1.18.0

. ${SRCDIR}/builddefs.sh

export PATH="$PREFIX/bin:$PATH"

# binutils
fetchextract http://ftp.gnu.org/gnu/binutils/ binutils-$BINUTILS_VERSION .tar.bz2
buildinstall 1 binutils-$BINUTILS_VERSION --target=$TRIPLET

# gcc 1
fetchextract http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/ gcc-$GCC_VERSION .tar.bz2
buildinstall 1 gcc-$GCC_VERSION --target=$TRIPLET \
    --enable-languages=c --with-newlib --disable-libssp --disable-libquadmath
