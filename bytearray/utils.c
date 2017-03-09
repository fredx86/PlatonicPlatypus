#include "pp/utils.h"

void putb(const void* bytes, size_t size)
{
  fputb(bytes, size, stdout);
  putchar('\n');
}

void fputb(const void* bytes, size_t size, FILE* file)
{
  char* tmp = (char*)bytes;
  for (size_t i = 0; i < size; ++i)
  {
    if (i)
      fprintf(file, " ");
    fprintf(file, "0x%X", tmp[i]);
  }
}

int endianess()
{
  int little_endian = 1;
  return (*(char*)&little_endian == 1);
}

void* revbytes(void* bytes, size_t bsize)
{
  char cpy[bsize];
  char* tmp = (char*)bytes;

  memcpy(cpy, bytes, bsize);
  for (size_t i = 0; i < bsize; ++i)
    tmp[i] = cpy[bsize - i - 1];
  return (bytes);
}

void timems(struct timeval* time, float ms)
{
  time->tv_sec = ms / 1000;
  time->tv_usec = ms * 1000 - time->tv_usec * 1000000; 
}