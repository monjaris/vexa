#!/usr/bin/env sh
cd "$(dirname "$0")" || exit 1

MODE="release"  # or debug

PROJ="vexa"
OS="$(xmake lua -c 'print(os.host())')"
PLAT="$(xmake lua -c 'print(os.arch())')"


if [ "$1" = "dev" ]; then
    MODE="debug"
    shift
fi
copy_bin="./build/${OS}/${PLAT}/${MODE}/${PROJ}"


xmake config --mode="$MODE" -y

nproc="$(getconf _NPROCESSORS_ONLN)"
xmake build -j"$(nproc)" "${PROJ}" || exit $?

command cp "$(dirname "$copy_bin")"/libvexa.so ./libvexa.so
