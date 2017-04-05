#include "byteutils.h"

void* find_byte(const void* bytes, size_t len, char c)
{
  const char* a = (const char*)bytes;

  for (size_t i = 0; i < len; ++i)
  {
    if (a[i] == c)
      return ((void*)&a[i]);
  }
  return (NULL);
}

void* find_bytes(const void* bytes, size_t len, const void* cmp, size_t cmp_len)
{
  size_t j, k;
  const char* a = (const char*)bytes;
  const char* b = (const char*)cmp;

  for (size_t i = 0; i < len; ++i)
  {
    k = i;
    for (j = 0; j < cmp_len && k < len && a[k] == b[j]; ++j)
      ++k;
    if (j == cmp_len)
      return ((void*)&a[i]);
  }
  return (NULL);
}

/*
Example:
  insertbytes("CDE", 3, "AB", 2) -> "ABCDE"
*/
void insert_bytes(void* dest, size_t dest_len, const void* src, size_t src_len)
{
  memmove((char*)dest + src_len, dest, dest_len);
  memcpy(dest, src, src_len);
}
