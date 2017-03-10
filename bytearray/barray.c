#include "barray.h"

ba_t* ba_create(const void* bytes, size_t size)
{
  ba_t* barray;

  if ((barray = mem_get(sizeof(*barray))) == NULL)
    return (NULL);
  barray->size = 0;
  barray->alloc = 0;
  barray->bytes = NULL;
  return (ba_set(barray, bytes, size));
}

ba_t* ba_set(ba_t* barray, const void* bytes, size_t size)
{
  if (barray == NULL)
    return (NULL);
  barray->size = 0;
  return (ba_app(barray, bytes, size));
}

ba_t* ba_app(ba_t* barray, const void* bytes, size_t size)
{
  if (!ba_memory_for(barray, size))
    return (NULL);
  memcpy(barray->bytes + barray->size, bytes, size);
  barray->size += size;
  return (barray);
}

ba_t* ba_app_byte(ba_t* barray, char byte)
{
  if (!ba_memory_for(barray, 1))
    return (NULL);
  barray->bytes[barray->size] = byte;
  barray->size += 1;
  return (barray);
}

void* ba_find(const ba_t* barray, const void* bytes, size_t size)
{
  size_t i, j, k;

  if (barray == NULL)
    return (NULL);
  for (i = 0; i < barray->size; ++i)
  {
    k = i;
    for (j = 0; j < size && k < barray->size && barray->bytes[k] == ((const char*)bytes)[j]; ++j)
      ++k;
    if (j == size)
      return ((void*)&barray->bytes[i]);
  }
  return (NULL);
}

void* ba_find_byte(const ba_t* barray, char byte)
{
  if (barray == NULL)
    return (NULL);
  for (size_t i = 0; i < barray->size; ++i)
  {
    if (barray->bytes[i] == byte)
      return ((void*)&barray->bytes[i]);
  }
  return (NULL);
}

void ba_destroy(ba_t* barray)
{
  if (barray == NULL)
    return;

  mem_release(barray->bytes);
  mem_release(barray);
}

int ba_memory_for(ba_t* barray, size_t size)
{
  size_t alloc_size;

  if (barray == NULL)
    return (0);
  if (barray->alloc >= barray->size + size) //If we are still good on memory
    return (1);
  alloc_size = ba_alloc_size(barray->size + size);
  if ((barray->bytes = mem_get_from(barray->bytes, alloc_size)) == NULL)
    return (0);
  barray->alloc = alloc_size;
  return (1);
}

size_t ba_alloc_size(size_t size)
{
  return (20 + (size / 2) * 4);
}