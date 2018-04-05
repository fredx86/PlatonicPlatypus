#include "utils.h"

void* bytesfirst(const void* haystack, size_t hsize, const void* needle, size_t nsize)
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
