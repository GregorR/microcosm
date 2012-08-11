#!/bin/sh
# Build a native compiler for microcosm
# 
# Copyright (C) 2012 Gregor Richards
# 
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

if [ ! "$MICROCOSM_BASE" ]
then
    MICROCOSM_BASE=`dirname "$0"`
fi

# Fail on any command failing, show commands:
set -ex

BINUTILS_CONFFLAGS=
GCC_BOOTSTRAP_CONFFLAGS=
. "$MICROCOSM_BASE"/defs.sh

# 0) Mark musl as unbuilt so it'll build again
if [ ! -e libmicrocosm/builtnhost ]
then
    rm -f musl/built musl/installed
fi

# 1) Cross-compiler prereqs
"$MICROCOSM_BASE"/musl-cross/extra/build-gcc-deps.sh

# 2) Cross-compiler
PREFIX="$MICROCOSM_NATIVE_PREFIX"
fetchextract http://ftp.gnu.org/gnu/binutils/ binutils-$BINUTILS_VERSION .tar.bz2
buildinstall n1 binutils-$BINUTILS_VERSION --host=$TRIPLE --target=$TRIPLE \
    --with-sysroot="$MICROCOSM_NATIVE_PREFIX"
[ ! -e "$MICROCOSM_NATIVE_PREFIX"/usr ] && ln -sf . "$MICROCOSM_NATIVE_PREFIX"/usr
fetchextract http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/ gcc-$GCC_VERSION .tar.bz2
buildinstall n1 gcc-$GCC_VERSION --host=$TRIPLE --target=$TRIPLE \
    --enable-languages=c --with-sysroot="$MICROCOSM_NATIVE_PREFIX"

# 3) Host components of libmicrocosm
PREFIX="$CC_PREFIX"
OMAKEFLAGS="$MAKEFLAGS"
MAKEFLAGS="$MAKEFLAGS libmicrocosm.so libmicrocosm.so.1"
linkdirs "$MICROCOSM_BASE"/libmicrocosm libmicrocosm
build nhost libmicrocosm --target="$TRIPLE"
cp libmicrocosm/buildhost/libmicrocosm.so* "$MICROCOSM_NATIVE_PREFIX"/lib
MAKEFLAGS="$OMAKEFLAGS"

# 4) musl
PREFIX="$MICROCOSM_NATIVE_PREFIX"
linkdirs "$MICROCOSM_BASE"/musl musl
buildinstall '' musl CC="$TRIPLE-gcc"

echo 'Done!'
