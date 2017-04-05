#!/bin/bash

DEPENDENCY_FILE="config.dat"

# echo the list of source code files (.c and .h) from a directory
get_files()
{
  ls "$1" | grep .[hc]$
}

# echo the dependancies from a module
get_dependency()
{
  while read LINE; do
    KEY=$(echo "$LINE" | cut -d '=' -f 1)
    if [ "$KEY" == "$1" ]; then
      echo "$LINE" | cut -d '=' -f 2 ; return
    fi
  done < "$DEPENDENCY_FILE"
}

# resolve the dependencies from a module
# copy the needed files into the module directory
resolve_dependencies()
{
  DIRS=$(get_dependency "$1")
  if [ ! "$DIRS" ]; then
    return 0
  fi
  for DIR in $DIRS; do
    info "Resolving dependencies from $DIR"
    cp "$DIR"/*.c "$2" || return 1
    cp "$DIR"/*.h "$2" || return 1
    resolve_dependencies "$DIR" "$2"
  done
  return 0
}

# clean all dependencies from all modules
clean_dependencies()
{
  DIRS=$(get_dependency "$1")
  if [ ! "$DIRS" ]; then
    return 0
  fi
  for DIR in $DIRS; do
    FILES=$(get_files "$DIR")
    for FILE in $FILES; do
      rm -f "$2/$FILE"
    done
    clean_dependencies "$DIR" "$2"
  done
  return 0
}

build()
{
    cd "$1"
    make || return 1
    make clean
    cd - 1> /dev/null
    return 0
}

tests()
{
    cd "$1/tests" 2> /dev/null || return 1
    make || return 1
    ./unitary || return 1
    make fclean 1> /dev/null
    cd - 1> /dev/null
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

if [ ! $1 ] || [ $1 == "--help" ]; then
  echo "Usage: $0 <module> | --clean" > /dev/stderr
  echo -e "\tmodule\t\tResolve dependencies and run unit tests for module" > /dev/stderr
  echo -e "\t--clean\t\tClean all dependencies" > /dev/stderr
  exit 1
fi

if [ $1 == "--clean" ]; then
  while read LINE; do
    KEY=$(echo "$LINE" | cut -d '=' -f 1)
    info "Removing dependencies from $KEY"
    clean_dependencies "$KEY" "$KEY"
  done < "$DEPENDENCY_FILE"
  info "Cleaning done"
  exit 0
fi

TARGET="$(basename $1)"

test -d "$TARGET" || err "Module $TARGET does not exists"
resolve_dependencies "$TARGET" "$TARGET" || err "Failed to recover dependencies for $TARGET"
info "Resolved all dependencies for $TARGET"

build "$TARGET" || err "Build KO"
info "Build OK"

tests "$TARGET" || err "Tests KO"
info "Tests OK"

info "All set up for $TARGET!"
