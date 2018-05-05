#include "pp/utils.h"

inline int is_little_endian()
{
  unsigned n = 1;
  return (*(char*)&n);
}

void* memfirst(const void* haystack, size_t hsize, const void* needle, size_t nsize)
{
  size_t i, j;
  const char* a = (const char*)haystack;
  const char* b = (const char*)needle;

  for (i = 0; i < hsize; ++i)
  {
    for (j = 0; i < hsize && j < nsize && a[i] == b[j]; ++j)
    {
      ++i;
    }
    i -= j;
    if (j == nsize)
    {
      return ((void*)a + i);
    }
  }
  return (NULL);
}

char* strset(char* dest, const char* src, size_t maxlen)
{
  size_t i = 0;
  for (; i < maxlen - 1 && src[i]; ++i)
  {
    dest[i] = src[i];
  }
  dest[i] = 0;
  return (dest);
}
