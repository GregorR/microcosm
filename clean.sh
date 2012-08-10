#!/bin/sh

if [ ! "$MICROCOSM_BASE" ]
then
    MICROCOSM_BASE=`dirname "$0"`
fi

# Show commands:
set -x

. "$MICROCOSM_BASE"/defs.sh

# 1) Cross-compiler
#rm -rf binutils-*/ gcc-*/ gmp-*/ mpfr-*/ mpc-*/

# 2) Host components of libmicrocosm
rm -rf libmicrocosm/buildhost libmicrocosm/builthost libmicrocosm/installedhost

# 3) Dynamic loader
(
cd gelfload
make distclean
)
rm -f gelfload/built gelfload/installed

# 4) musl
(
cd musl
make clean
)
rm -f musl/built musl/installed

# 5) libmicrocosm
rm -rf libmicrocosm/buildfull libmicrocosm/builtfull libmicrocosm/installedfull
rm -rf libmicrocosm/buildnhost libmicrocosm/builtnhost libmicrocosm/installednhost

echo 'Done!'
