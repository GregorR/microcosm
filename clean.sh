#!/bin/bash -x

. defs.sh

# 1) Cross-compiler
pushd cross || die 'Failed to pushd cross'
rm -rf binutils-*/ gcc-*/ gmp-*/ mpfr-*/ mpc-*/
popd || die 'Failed to popd'

# 2) Host components of libmicrocosm
rm -rf libmicrocosm/buil{d,t}host libmicrocosm/installedhost

# 3) Dynamic loader
pushd gelfload || die 'Failed to pushd gelfload'
make distclean
popd || die 'Failed to popd'
rm -f gelfload/{built,installed}

# 4) musl
pushd musl || die 'Failed to pushd musl'
make clean
popd
rm -f musl/{built,installed}

# 5) libmicrocosm
rm -rf libmicrocosm/buil{d,t}full libmicrocosm/installedfull
rm -rf libmicrocosm/buil{d,t}nhost libmicrocosm/installednhost

echo 'Done!'
