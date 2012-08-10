#!/bin/sh

if [ ! "$MICROCOSM_BASE" ]
then
    MICROCOSM_BASE=`dirname "$0"`
fi

# Fail on any command failing, show commands:
set -ex

. "$MICROCOSM_BASE"/defs.sh

# 1) Cross-compiler
"$MICROCOSM_BASE"/buildcc.sh

# 2) Host components of libmicrocosm
PREFIX="$CC_PREFIX"
OMAKEFLAGS="$MAKEFLAGS"
MAKEFLAGS="$MAKEFLAGS libmicrocosm.so libmicrocosm.so.1"
if [ ! -e "$MICROCOSM_BASE"/libmicrocosm/configure ]
then
    (
    cd "$MICROCOSM_BASE"/libmicrocosm
    autoreconf
    )
fi
[ ! -e libmicrocosm ] && ln -s "$MICROCOSM_BASE"/libmicrocosm .
build host libmicrocosm --target="$TRIPLE"
cp libmicrocosm/buildhost/libmicrocosm.so* "$CC_PREFIX"/"$TRIPLE"/lib
MAKEFLAGS="$OMAKEFLAGS"

# 3) Dynamic loader
PREFIX="$MICROCOSM_PREFIX"
if [ ! -e "$MICROCOSM_BASE"/gelfload/configure ]
then
    (
    cd "$MICROCOSM_BASE"/gelfload
    autoreconf
    )
fi
[ ! -e gelfload ] && ln -s "$MICROCOSM_BASE"/gelfload .
buildinstall '' gelfload

# 4) musl
PREFIX="$CC_PREFIX/$TRIPLE"
[ ! -e musl ] && ln -s "$MICROCOSM_BASE"/musl .
buildinstall '' musl CC="$TRIPLE-gcc"

# 5) libmicrocosm
PREFIX="$CC_PREFIX"
buildinstall full libmicrocosm --target="$TRIPLE"

# 6) Symlink wrappers
mkdir -p "$MICROCOSM_PREFIX"/lib/microcosm
ln -sf "$CC_PREFIX"/"$TRIPLE"/lib/lib*.so* "$MICROCOSM_PREFIX"/lib/microcosm/

echo 'Done!'
