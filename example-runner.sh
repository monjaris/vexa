#!/usr/bin/env sh

# For an example to be runnable by this script, you need to satisfy this requirements:
# 1. the example should exists inside examples/ directory
# 2. the name($1) argument provided should match the base name of the example file
# 3. the example name(base part of the example file) should be added to array in examples.lua

example=${1:-"--list"}

if [ "$example" = "--list" ]; then
    printf "\033[32mAvailable examples to run:\033[0m\n"

    for file in ./examples/*; do
        basename "$file" .cpp
    done

    exit
fi

xmake run "$example" || \
echo "Example '$1' does not exist!"
