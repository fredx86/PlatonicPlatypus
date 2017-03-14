#!/bin/bash

declare -A DEPENDENCIES
DEPENDENCIES=(["packet"]="bytearray" ["hashmap"]="linkedlist")

get_dependencies()
{
    DIR=$(echo "${DEPENDENCIES[$1]}")
    if [ $DIR ]; then
	cp "$DIR"/* "$1"
    fi
}

run_tests()
{
    cd "$1"/tests || return 1
    make || return 1
    ./unitary || return 1
    make fclean 1> /dev/null
    return 0
}

if [ ! $1 ]; then
    echo "Usage: $0 <module - directory>" > /dev/stderr
    exit 1
fi
if [ $1 == "--help" ]; then
    echo "Resolve dependencies and run unit tests for module given in parameter"
    echo -e "\tExample: '\$>$0 packet'"
    exit 0
fi
TARGET=${1%/}
get_dependencies "$TARGET"
run_tests "$TARGET" && BUILD=1
if [ $BUILD ]; then
    echo -e "[\e[32mINFO\e[0m] Build OK for '$TARGET'"
else
    echo -e "[\e[31mINFO\e[0m] Build KO for '$TARGET'"
fi
