#!/bin/sh

cleanup()
{
  pkill -P $$
}

# Server connection
yes "HELLO" | nc -k -l 1234 > /dev/null &
# Client connection
(yes "HELLO" | while ! nc localhost 1235 > /dev/null ; do sleep 1 ; done) &

# Wait for a SIGTERM, then kills all childrens and itself
trap cleanup TERM
tail -f /dev/null & wait
