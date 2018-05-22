# PlatonicPlatypus
### _Personal C library_

## Guidelines
* Documentation of every function MUST BE available in the header file
* Functional tests of every component SHOULD BE available in the directory `tests`
* Examples of every component MAY BE available in the directory `examples`
* `#define` SHOULD NOT be used as "functions" ; use `inline` keyword instead
* Functions _XXXX\_clear()_ MUST perform a complete clean-up of the entity, and MAY BE re-usable afterwards without having to call _XXXX\_init()_

## Tests
Just run `reg.sh` in order to start all the functional tests available in the directory `tests`

```
$ ./reg.sh
### array.c ###
[ TEST ] Running...     PASSED
### socket.c ###
[ TEST ] Running...     PASSED
### thpool.c ###
[ TEST ] Running...     PASSED
### utils.c ###
[ TEST ] Running...     PASSED

Total:
        4 Passed
        0 Failed
Dump in ./.tests/reg.log
```

## Current implementations
* Array
* Linked list
* TCP Socket (Unix)
* Thread pool
* Logger
* Fatal assert

## Futures implementations
* Hashmaps
* sock_recv_timeout()
* UDP Socket
* Socket (Windows)
* array_sort()
* generic_t -> array_t, void*, double
* ...

## Notes
* [thpool](./thpool) is using c11 _threads.h_
