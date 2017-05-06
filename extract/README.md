```c
#include "extract.h"

int extract(const char* string, const char* format, ...);
```

### Description

The __extract()__ function extract data from from a null-terminated _string_ using a _format_ as described below.
The datas are extracted through pointers given by the veriadic list (...).

Note: If you extract a string, the pointer given to extract that string MUST be to a pointer to a string and must be __free()__ afterwards.

### Return value

The function returns 0 on success, -1 on error.

### Format

Specifier | Input | Example
------------ | ------------- | -------------
i | Identifier | heLLo_42
d | Integer | -42
f | Floating point | 42.42
s | Alpha | heLLo
\_ | Space (_isspace_) |
l | Alpha-numeric (_isalnum_) | heLLo42
c | Lower character (_islower_) | hello
C | Upper character (_isupper_) | HELLO
g | Graphical (_isgraph_) | heLLo42#!^
. | Punctuation (_ispunct_) | #!^
p | Printable (_isprint_) | heLLo42#!^
% | % | %

### Examples

```c
extract("hello world!", "%s %s!", &str1, &str2);
```
> Success. String given matches format. 'hello' and 'world' are extracted to str1 and str2 respectively and must be **free()**

```c
extract("test", "test");
```
> Success. String given matches format. No extraction

```c
extract("test % 423", "test %% %d", 42, NULL, &int_val);
```
> Success. String given matches format. 'NULL' storage values are ignored