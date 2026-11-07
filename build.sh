#!/usr/bin/env sh
cd "$(dirname "$0")" || exit 1

MODE="release"  # or debug
LIB="shared"  # or static

if [ "$1" = "dev" ]; then MODE="debug"; shift; fi

xmake config --mode="$MODE" --lib="$LIB"
xmake build -j16 vexa || exit $?
