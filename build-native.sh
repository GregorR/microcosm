#!/bin/bash -x

GMP_VERSION=5.0.4
MPFR_VERSION=3.1.0
MPC_VERSION=0.9

# Fail on any command failing
set -e

. defs.sh

# 1) Cross-compiler prereqs
PREFIX="$CC_PREFIX/$TRIPLE"
pushd cross
fetchextract ftp://ftp.gmplib.org/pub/gmp-$GMP_VERSION/ gmp-$GMP_VERSION .tar.bz2
cp -f config.sub gmp-$GMP_VERSION/configfsf.sub
buildinstall '' gmp-$GMP_VERSION --host="$TRIPLE" --enable-static --disable-shared
fetchextract http://www.mpfr.org/mpfr-current/ mpfr-$MPFR_VERSION .tar.bz2
cp -f config.sub mpfr-$MPFR_VERSION/config.sub
buildinstall '' mpfr-$MPFR_VERSION --host="$TRIPLE" --enable-static --disable-shared CC="$TRIPLE-gcc"
fetchextract http://www.multiprecision.org/mpc/download/ mpc-$MPC_VERSION .tar.gz
cp -f config.sub mpc-$MPC_VERSION/config.sub
buildinstall '' mpc-$MPC_VERSION --host="$TRIPLE" --enable-static --disable-shared
popd

# 2) Cross-compiler
pushd cross
./buildcc-native.sh
popd

# 3) Host components of libmicrocosm
PREFIX="$MICROCOSM_NATIVE_PREFIX"
OMAKEFLAGS="$MAKEFLAGS"
MAKEFLAGS="$MAKEFLAGS libmicrocosm.so libmicrocosm.so.1"
build nhost libmicrocosm --target="$TRIPLE"
cp libmicrocosm/buildnhost/libmicrocosm.so* "$MICROCOSM_NATIVE_PREFIX"/lib
MAKEFLAGS="$OMAKEFLAGS"

# 4) musl
PREFIX="$MICROCOSM_NATIVE_PREFIX"
export PREFIX
cp musl.config.mak musl/config.mak
buildmake musl
doinstall '' musl
unset PREFIX

echo 'Done!'
