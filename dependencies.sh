#!/bin/bash

declare -A DEPENDENCIES
DEPENDENCIES=(["bytearray"]="utils" ["hashmap"]="linkedlist" ["packet"]="bytearray" ["select"]="utils linkedlist socket" ["tcpserver"]="select packet")

get_dependencies()
{
  DIR=""
  DIRS=${DEPENDENCIES[$1]}
  if [ "$DIRS" ]; then
    for DIR in $DIRS; do
      cp "$DIR"/*.* "$1" || return 1
      info "Resolving dependencies from $DIR"
      get_dependencies "$DIR"
    done
  fi
  return 0
}

run_tests()
{
  cd "$1"/tests || return 1
  make || return 1
  ./unitary || return 1
  make fclean 1> /dev/null
  return 0
}

err()
{
  echo -e "[\e[31mINFO\e[0m] $1" > /dev/stderr
  exit 1
}

info()
{
  echo -e "[\e[32mINFO\e[0m] $1"
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

get_dependencies "$TARGET" || err "Failed to recover dependencies for $TARGET"
run_tests "$TARGET" && BUILD=1
if [ $BUILD ]; then
  info "Build OK for $TARGET"
else
  err "Build KO for $TARGET"
fi