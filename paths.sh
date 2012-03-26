#!/bin/bash
if [ ! "$MICROCOSM_BASE" ]
then
    MICROCOSM_BASE="$PWD"
fi
export MICROCOSM_BASE

if [ ! -e "$MICROCOSM_BASE/config.sh" ]
then
    echo 'Create a config.sh file.'
    exit 1
fi

. "$MICROCOSM_BASE"/config.sh

echo "$MICROCOSM_PREFIX"/bin
echo "$CC_PREFIX"/bin
