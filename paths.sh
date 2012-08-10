#!/bin/sh
if [ ! "$MICROCOSM_BASE" ]
then
    MICROCOSM_BASE=`dirname "$0"`
fi

# Fail on any command failing, show commands:
set -ex

. "$MICROCOSM_BASE"/defs.sh

echo "$MICROCOSM_PREFIX"/bin
echo "$CC_PREFIX"/bin
