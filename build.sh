#!/bin/sh

if [ ! "$MICROCOSM_BASE" ]
then
    MICROCOSM_BASE=`dirname "$0"`
fi

# Fail on any command failing, show commands:
set -ex

. "$MICROCOSM_BASE"/defs.sh

[ ! -e scripts ] && ln -s "$MICROCOSM_BASE"/scripts .

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
linkdirs "$MICROCOSM_BASE"/libmicrocosm libmicrocosm
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
linkdirs "$MICROCOSM_BASE"/gelfload gelfload
buildinstall '' gelfload

# 4) musl
PREFIX="$CC_PREFIX/$TRIPLE"
linkdirs "$MICROCOSM_BASE"/musl musl
buildinstall '' musl CC="$TRIPLE-gcc"

# 5) libmicrocosm
PREFIX="$CC_PREFIX"
buildinstall full libmicrocosm --target="$TRIPLE"

# 6) Symlink wrappers
mkdir -p "$MICROCOSM_PREFIX"/lib/microcosm
ln -sf "$CC_PREFIX"/"$TRIPLE"/lib/lib*.so* "$MICROCOSM_PREFIX"/lib/microcosm/

echo 'Done!'
