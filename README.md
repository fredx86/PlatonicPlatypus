# PlatonicPlatypus

## Guidelines
* Documentation of every function of every component MUST BE available in the header file
* Functional tests of every component SHOULD BE available in the directory `tests` of the said component
* Examples of every component MAY BE available in the directory `examples` of the said component
* `#define` MUST NOT be used as "functions" ; use `inline` keyword instead
* Functions _XXXX\_clear()_ MUST perform a complete clean-up of the entity, and MAY BE re-usable afterwards without having to call _XXXX\_init()_

## Futures implementations
* Hashmaps
* Whatever that suits me

## Notes
* [thpool](./thpool) is using c11 _threads.h_
