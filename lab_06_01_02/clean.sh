#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")

for file in "$dir"/*.exe "$dir"/*.o "$dir"/out.tmp
do
    if [ -f "$file" ]; then
        rm "$file"
    fi
done