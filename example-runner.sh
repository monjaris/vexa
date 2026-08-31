#!/usr/bin/env sh
# 
# xmake run "$1" > /dev/null 2>&1 || \
# echo "Example '$1' does not exist!"



xmake run "$1" || \
echo "Example '$1' does not exist!"
