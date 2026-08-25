#!/usr/bin/env sh
cd "$(dirname "$0")" || exit 1

PROJ="vexa"
OS="linux"
PLAT="x86_64"
MODE="release"  # or debug
VIDEO="wayland"  # or x11
RENDERER="sdl"  # or gpu
LIBCPP="libstdc++"  # or libc++


if [ "$1" = "dev" ]; then
    MODE="debug"
    shift
fi
copy_bin="./build/${OS}/${PLAT}/${MODE}/${PROJ}"


xmake config \
    --mode="$MODE" \
    --window-backend="$VIDEO" \
    --renderer-backend="$RENDERER" \
    --libcxx="$LIBCPP" \
    -y

nproc="$(getconf _NPROCESSORS_ONLN)"
xmake build -j"$(nproc)" "${PROJ}" || exit $?

command cp "$(dirname "$copy_bin")"/libvexa.so ./libvexa.so
