#ifndef BYTE_UTILS_H_
#define BYTE_UTILS_H_

#include <stdlib.h>
#include <string.h>

void* find_byte(const void*, size_t, char);
void* find_bytes(const void* haystack, size_t, const void* needle, size_t); /* Find needle in the haystack */
void insert_bytes(void* dest, size_t dest_len, const void* src, size_t src_len); /* Insert bytes src into dest */

#endif