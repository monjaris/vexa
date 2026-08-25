#!/usr/bin/env sh
cd "$(dirname "$0")" || exit 1

PROJ="vexa"
OS="linux"
PLAT="x86_64"
MODE="release"  # or debug
VIDEO="x11"  # or x11
LIBCPP="libstdc++"  # or libc++


if [ "$1" = "dev" ]; then
    MODE="debug"
    shift
fi
copy_bin="./build/${OS}/${PLAT}/${MODE}/${PROJ}"


nproc="$(getconf _NPROCESSORS_ONLN)"
xmake config --mode=${MODE} --backend="$VIDEO" --stdcxx="$LIBCPP" -y
xmake build -j"$(nproc)" "${PROJ}" || exit $?

command cp "$(dirname "$copy_bin")"/libvexa.so ./libvexa.so
