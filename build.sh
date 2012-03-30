#!/bin/bash -x

# Fail on any command failing
set -e

. defs.sh

# 1) Cross-compiler
pushd cross
./buildcc.sh
popd

# 2) Host components of libmicrocosm
PREFIX="$CC_PREFIX"
OMAKEFLAGS="$MAKEFLAGS"
MAKEFLAGS="$MAKEFLAGS libmicrocosm.so libmicrocosm.so.1"
if [ ! -e libmicrocosm/configure ]
then
    pushd libmicrocosm
    autoreconf
    popd
fi
build host libmicrocosm --target="$TRIPLE"
cp libmicrocosm/buildhost/libmicrocosm.so* "$CC_PREFIX"/"$TRIPLE"/lib
MAKEFLAGS="$OMAKEFLAGS"

# 3) Dynamic loader
PREFIX="$MICROCOSM_PREFIX"
if [ ! -e gelfload/configure ]
then
    pushd gelfload
    autoreconf
    popd
fi
buildinstall '' gelfload

# 4) musl
PREFIX="$CC_PREFIX/$TRIPLE"
export PREFIX
cp musl.config.mak musl/config.mak
buildmake musl
doinstall '' musl
unset PREFIX

# 5) libmicrocosm
PREFIX="$CC_PREFIX"
buildinstall full libmicrocosm --target="$TRIPLE"

# 6) Symlink wrappers
mkdir -p "$MICROCOSM_PREFIX"/lib/microcosm
ln -sf "$CC_PREFIX"/"$TRIPLE"/lib/lib*.so* "$MICROCOSM_PREFIX"/lib/microcosm/

echo 'Done!'
