#!/bin/bash
dir=$(dirname "$(readlink -f "$0")")

for build in "$dir"/build_debug_*san.sh 
do
    if [ ! -f "$build" ]; then
        echo No sanitizers build scripts!
        exit 2
    fi

    short_name="$(basename "$build")"
    echo "Checking $short_name"
    if ! "$build"; then
        echo "Failed build with $short_name"
        exit 1
    fi
    
    if ! "$dir"/func_tests/scripts/func_tests.sh "$1"
    then 
        echo "Failed func testing with $short_name"
        exit 1
    fi
done