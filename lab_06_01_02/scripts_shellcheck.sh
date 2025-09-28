#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")

failed=0
for file in "$dir"/*.sh "$dir"/func_tests/scripts/*.sh; do
    if [ ! -f "$file" ]; then
        continue
    fi
    if ! shellcheck "$file"; then
        failed=$((failed + 1))
    fi
done

exit "$failed"