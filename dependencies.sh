#!/bin/bash

DEPENDENCY_FILE="config.dat"

get_files()
{
  ls -l "$1" | grep ^- | tr -s ' ' | cut -d ' ' -f 9
}

get_dependency()
{
  while read LINE; do
    KEY=$(echo "$LINE" | cut -d '=' -f 1)
    if [ "$KEY" == "$1" ]; then
      echo "$LINE" | cut -d '=' -f 2 ; return
    fi
  done < "$DEPENDENCY_FILE"
}

add_dependencies()
{
  DIRS=$(get_dependency "$1")
  if [ ! "$DIRS" ]; then
    return 0
  fi
  for DIR in $DIRS; do
    info "Resolving dependencies from $DIR"
    cp "$DIR"/*.* "$2" || return 1
    add_dependencies "$DIR" "$2"
  done
  return 0
}

clean_dependencies()
{
  DIRS=$(get_dependency "$1")
  if [ ! "$DIRS" ]; then
    return 0
  fi
  for DIR in $DIRS; do
    info "Removing dependencies from $DIR"
    FILES=$(get_files "$DIR")
    for FILE in $FILES; do
      rm -f "$2/$FILE"
    done
    clean_dependencies "$DIR" "$2"
  done
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

if [ ! $1 ] || [ $1 == "--help" ]; then
  echo "Usage: $0 <module> | --clean" > /dev/stderr
  echo -e "\tmodule\t\tResolve dependencies and run unit tests for module" > /dev/stderr
  echo -e "\t--clean\t\tClean all dependencies" > /dev/stderr
  exit 1
fi

if [ $1 == "--clean" ]; then
  while read LINE; do
    KEY=$(echo "$LINE" | cut -d '=' -f 1)
    clean_dependencies "$KEY" "$KEY"
  done < "$DEPENDENCY_FILE"
  info "Cleaning done"
  exit 0
fi

TARGET=${1%/}

test -d "$TARGET" || err "Module $TARGET does not exists"
add_dependencies "$TARGET" "$TARGET" || err "Failed to recover dependencies for $TARGET"
run_tests "$TARGET" && BUILD=1
if [ $BUILD ]; then
  info "Build OK for $TARGET"
else
  err "Build KO for $TARGET"
fi