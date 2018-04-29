#!/bin/sh

yes "HELLO" | nc -k -l 4242 > /dev/null &

# Wait for a SIGTERM, then kills all childrens and itself
trap 'pkill -P $$' TERM
tail -f /dev/null & wait
