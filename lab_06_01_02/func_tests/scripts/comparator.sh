#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Args must be more than one"
    exit 2
fi

if [ ! -f "$1" ] && [ ! -L "$1" ]; then
    echo "First arg must be valid file!"
    exit 2
fi

if [ ! -f "$2" ] && [ ! -L "$2" ]; then
    echo "Second arg must be valid file!"
    exit 2
fi

if ! diff -q "$1" "$2" > /dev/null
then
    exit 1
fi
exit 0