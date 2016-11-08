#include "pp/utils.h"

void putb(const char* bytes, size_t size)
{
  fputb(bytes, size, stdout);
  putchar('\n');
}

void fputb(const char* bytes, size_t size, FILE* file)
{
  size_t i;
  for (i = 0; i < size; ++i)
    fprintf(file, "%c0x%X", i == 0 ? 0 : ' ', bytes[i]);
}