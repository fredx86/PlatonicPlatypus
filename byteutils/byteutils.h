#ifndef BYTEUTILS_H_
#define BYTEUTILS_H_

#include <stdlib.h>
#include <string.h>

void* find_byte(const void*, size_t, char);

/* Find needle of size s1 in the haystack of size s2 */
void* find_bytes(const void* haystack, size_t s1, const void* needle, size_t s2);

/* Insert bytes src into dest */
void insert_bytes(void* dest, size_t dest_len, const void* src, size_t src_len);

#endif
