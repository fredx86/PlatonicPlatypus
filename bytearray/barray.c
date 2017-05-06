#include "barray.h"

ba_t* ba_create(const void* bytes, size_t size)
{
  ba_t* barray;

  if ((barray = malloc(sizeof(*barray))) == NULL)
    return (NULL);
  barray->bytes = NULL;
  barray->size = 0;
  barray->alloc = 0;
  return (ba_app(barray, bytes, size));
}

void ba_clear(ba_t* barray)
{
  if (barray == NULL)
    return;
  free(barray->bytes);
  barray->bytes = NULL;
  barray->size = 0;
  barray->alloc = 0;
}

ba_t* ba_app(ba_t* barray, const void* bytes, size_t size)
{
  if (barray == NULL || !ba_memory_for(barray, size))
    return (NULL);
  memcpy(barray->bytes + barray->size, bytes, size);
  barray->size += size;
  return (barray);
}

ba_t* ba_app_byte(ba_t* barray, char byte)
{
  if (barray == NULL || !ba_memory_for(barray, 1))
    return (NULL);
  barray->bytes[barray->size] = byte;
  barray->size += 1;
  return (barray);
}

ba_t* ba_app_format(ba_t* barray, const char *format, ...)
{
  char* ptr;
  va_list ap;
  int available;
  int n = strlen(format);

  if (barray == NULL)
    return (NULL);
  do
  {
    if (!ba_memory_for(barray, n + 1))
      return (NULL);
    ptr = barray->bytes + barray->size;
    available = barray->alloc - barray->size;
    va_start(ap, format);
    n = vsnprintf(ptr, available, format, ap);
    if (n < 0)
      return (NULL);
    va_end(ap);
  }
  while (n >= available);
  barray->size += n;
  return (barray);
}

ba_t* ba_insert(ba_t* barray, size_t pos, const void* bytes, size_t size)
{
  if (barray == NULL || pos > barray->size)
    return (NULL);
  if (!ba_memory_for(barray, size))
    return (NULL);
  insert_bytes(barray->bytes + pos, barray->size - pos, bytes, size);
  barray->size += size;
  return (barray);
}

ba_t* ba_replace(ba_t* barray, size_t pos, const void* bytes, size_t size)
{
  if (barray == NULL || pos + size > barray->size)
    return (NULL);
  memcpy(barray->bytes + pos, bytes, size);
  return (barray);
}

ba_t* ba_erase(ba_t* barray, size_t pos, size_t len)
{
  if (barray == NULL || pos + len > barray->size)
    return (NULL);
  memmove(barray->bytes + pos, barray->bytes + pos + len, barray->size - (pos + len));
  barray->size -= len;
  return (barray);
}

void* ba_find(const ba_t* barray, const void* bytes, size_t size)
{
  if (barray == NULL)
    return (NULL);
  return (find_bytes(barray->bytes, barray->size, bytes, size));
}

void* ba_find_byte(const ba_t* barray, char byte)
{
  if (barray == NULL)
    return (NULL);
  return (find_byte(barray->bytes, barray->size, byte));
}

void ba_destroy(ba_t* barray)
{
  if (barray == NULL)
    return;
  free(barray->bytes);
  free(barray);
}

int ba_memory_for(ba_t* barray, size_t size)
{
  size_t alloc_size;

  if (barray->alloc >= barray->size + size) //If we are still good on memory
    return (1);
  alloc_size = ba_alloc_size(barray->size + size);
  if ((barray->bytes = realloc(barray->bytes, alloc_size)) == NULL)
    return (0);
  barray->alloc = alloc_size;
  return (1);
}

size_t ba_alloc_size(size_t size)
{
  return (20 + (size / 2) * 4);
}
