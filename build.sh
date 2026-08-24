#!/usr/bin/env bash
cd "$(dirname "$0")" || exit 1

PROJ="game"
debug_bin="./build/linux/x86_64/debug/${PROJ}"
release_bin="./build/linux/x86_64/release/${PROJ}"

VIDEO="wayland"  # or "x11"

if [[ "$VIDEO" = "wayland" ]]; then
    ./gen-wlprotocol-headers.sh
fi

if [[ "$1" == "dev" ]]; then
    xmake config --mode=debug --backend="$VIDEO"
    copy_bin="$debug_bin"
    shift
else
    xmake config --mode=release --backend="$VIDEO"
    copy_bin="$release_bin"
fi

xmake build -j$(nproc) "${PROJ}" || exit $?
command cp "$copy_bin" ./"${PROJ}"
command cp "$(dirname "$copy_bin")"/libvexa.so ./libvexa.so
./"${PROJ}" "$@"
