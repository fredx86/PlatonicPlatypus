#!/bin/sh

CC=musl-gcc
LOGFILE=./tests/reg.log

KO='\033[1;31m'
OK='\033[1;32m'
TEST='\033[1m'
CL='\033[0m'

PASSED=0
FAILED=0

cleanup()
{
  killall setup.sh > /dev/null
}

cleanexit()
{
  cleanup
  exit 1
}

# $1  FILES
# $2  OUTPUT FILE
# $3  TEST NAME
test_run()
{
  printf "${TEST}### $3 ###${CL}\n"
  printf "[ TEST ] Running..."
  printf "[`date +'%D %H:%M:%S'`]\t$3\n" >> $LOGFILE
  $CC $1 -o $2 -I includes -Wall -Wextra >> $LOGFILE 2>&1 &&
  ./$2 >> $LOGFILE 2>&1 &&
  test_success $3 || test_failed $3
  rm -f $2
}

# $1  TEST NAME
test_success()
{
  printf "\t${OK}PASSED${CL}\n"
  PASSED=$((PASSED + 1))
}

# $1  TEST NAME
test_failed()
{
  printf "\t${KO}FAILED${CL}\n"
  FAILED=$((FAILED + 1))
}

LIB_FILES=`find ./srcs -type f -name '*.c'`
TESTS_FILES=`find ./tests -type f -name '*.c'`

trap cleanexit INT
./tests/setup.sh &
for FILE in $TESTS_FILES; do
  test_run "$FILE $LIB_FILES" "test" `basename $FILE`
done
cleanup
printf "\n"
printf "Total:\n"
printf "\t${PASSED} Passed${CL}\n"
printf "\t${FAILED} Failed${CL}\n"
printf "Dump in ${LOGFILE}\n"
