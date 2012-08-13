# Definitions for build scripts
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

ORIGPWD="$PWD"
cd "$MICROCOSM_BASE"
MICROCOSM_BASE="$PWD"
export MICROCOSM_BASE
cd "$ORIGPWD"
unset ORIGPWD

if [ -z "$MUSL_CC_BASE" ]
then
    MUSL_CC_BASE="$MICROCOSM_BASE"
fi

if [ ! -e config.sh ]
then
    echo 'Create a config.sh file.'
    exit 1
fi
. ./config.sh

# Auto-detect an ARCH if not specified
if [ -z "$ARCH" ]
then
    for MAYBECC in cc gcc clang
    do
        $MAYBECC -dumpmachine > /dev/null 2> /dev/null &&
        ARCH=`$MAYBECC -dumpmachine | sed 's/-.*//'` &&
        break
    done
    unset MAYBECC

    [ -z "$ARCH" ] && ARCH=`uname -m`
fi

# Auto-detect a TRIPLE if not specified
if [ -z "$TRIPLE" ]
then
    case "$ARCH" in
        arm*)
            TRIPLE="$ARCH-microcosmeabi"
            ;;
        *)
            TRIPLE="$ARCH-microcosm"
            ;;
    esac
fi

# Include musl-cross's defs.sh
. "$MUSL_CC_BASE/musl-cross/defs.sh"

# Use ginstall if it exists
if [ -z "$INSTALL_PROG" ]
then
    ginstall --help > /dev/null 2>&1
    if [ "$?" = "0" ]
    then
        INSTALL_PROG=ginstall
    else
        INSTALL_PROG=make
    fi
fi

PATH="$MICROCOSM_PREFIX/bin:$PATH"
export PATH

# Something like lndir
semilndir() {
    (
    LNDIR_TARGET="$PWD"
    cd "$1" || exit 1
    [ "$LNDIR_TARGET" = "$PWD" ] && exit 0
    find . -type d -exec mkdir -m 0755 -p "$LNDIR_TARGET"'/{}' ';'
    find . '(' -type f -o -type l ')' -exec ln -s "$PWD"'/{}' "$LNDIR_TARGET"'/{}' ';'
    )
}

linkdirs() {
    if [ ! -e "$2/linked" ]
    then
        mkdir -p "$2"
        (
        cd "$2"
        semilndir "$1"
        touch linked
        )
    fi
}
