# PlatonicPlatypus
### _Personal C library_

## How to use ?
Run `./dependencies.sh <module>` where `module` is the directory you want (Ex: _tcpserver_)

It will resolve possible dependencies, build the library and run the unit tests.

You can both use the sources files (.c & .h) directly, or use the static library generated in the directory.

## Example

```
$ ./dependencies.sh tcpserver/
[INFO] Resolving dependencies from select
[INFO] Resolving dependencies from linkedlist
[INFO] Resolving dependencies from socket
[INFO] Resolving dependencies from timeutils
[INFO] Resolving dependencies from packet
[INFO] Resolving dependencies from bytearray
[INFO] Resolving dependencies from byteutils
[INFO] Resolved all dependencies for tcpserver
gcc -Wall -Wextra -pedantic   -c -o tserver.o tserver.c
gcc -Wall -Wextra -pedantic   -c -o select.o select.c
gcc -Wall -Wextra -pedantic   -c -o llist.o llist.c
gcc -Wall -Wextra -pedantic   -c -o timeutils.o timeutils.c
gcc -Wall -Wextra -pedantic   -c -o socket.o socket.c
gcc -Wall -Wextra -pedantic   -c -o packet.o packet.c
gcc -Wall -Wextra -pedantic   -c -o barray.o barray.c
gcc -Wall -Wextra -pedantic   -c -o byteutils.o byteutils.c
ar rc libppts.a tserver.o select.o llist.o timeutils.o socket.o packet.o barray.o byteutils.o
rm -f tserver.o select.o llist.o timeutils.o socket.o packet.o barray.o byteutils.o
[INFO] Build OK
gcc -Wall -Wextra -pedantic   -c -o unit.o unit.c
gcc -o unitary unit.o ../libppts.a
[INFO] Tests OK
[INFO] All set up for tcpserver!
```

It resolved all the dependencies (sources files), and generates the library as _libppts.a_ (as _Platonic Platypus Tcp Server_) in the _tcpserver/_ directory.

```
$ ls
barray.c      byteutils.c  libppts.a  Makefile  select.c  socket.h      timeutils.c  tserver.h
barray.h      byteutils.h  llist.c    packet.c  select.h  tests/        timeutils.h  tserver_event.h
byte_utils.o  examples/    llist.h    packet.h  socket.c  time_utils.o  tserver.c
```
