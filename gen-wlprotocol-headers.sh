#!/usr/bin/env bash

mkdir -p vendor/SDL3/src/video/wayland/generated
for xml in vendor/SDL3/wayland-protocols/*.xml; do
  b=$(basename "$xml" .xml)
  wayland-scanner client-header "$xml" vendor/SDL3/src/video/wayland/generated/${b}-client-protocol.h
  wayland-scanner private-code "$xml" vendor/SDL3/src/video/wayland/generated/${b}-protocol.c
done
