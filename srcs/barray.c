#include "pp/barray.h"

barray_t* bacrt(barray_t* barray, const void* bytes, size_t size)
{
  barray->size = 0;
  barray->_alloc = 0;
  barray->bytes = NULL;
  return (bacpy(barray, bytes, size));
}

barray_t* bacpy(barray_t* barray, const void* bytes, size_t size)
{
  barray->size = 0;
  return (baapp(barray, bytes, size));
}

barray_t* baapp(barray_t* barray, const void* bytes, size_t size)
{
  if (!_barealloc(barray, size))
    return (NULL);
  memcpy(barray->bytes + barray->size, bytes, size);
  barray->size += size;
  return (barray);
}

barray_t* baappc(barray_t* barray, char c)
{
  if (!_barealloc(barray, 1))
    return (NULL);
  barray->bytes[barray->size] = c;
  barray->size += 1;
  return (barray);
}

barray_t* baappv(barray_t* barray, size_t count, ...)
{
  size_t i;
  void* bytes;
  size_t size;
  va_list args;
  
  va_start(args, count);
  for (i = 0; i < count; ++i)
  {
    bytes = va_arg(args, void*);
    size = va_arg(args, size_t);
    if (baapp(barray, bytes, size) == NULL)
      return (NULL);
  }
  va_end(args);
  return (barray);
}

barray_t* bainsrt(barray_t* barray, size_t pos, const void* bytes, size_t size)
{
  if (!_barealloc(barray, size) || pos > barray->size)
    return (NULL);
  memmove(barray->bytes + pos + size, barray->bytes + pos, barray->size - pos);
  memcpy(barray->bytes + pos, bytes, size);
  barray->size += size;
  return (barray);
}

barray_t* barplc(barray_t* barray, size_t pos, const void* bytes, size_t size)
{
  if (pos + size > barray->size)
    return (NULL);
  memcpy(barray->bytes + pos, bytes, size);
  return (barray);
}

barray_t* basub(barray_t* barray, barray_t* sub, size_t pos, size_t size)
{
  if (!_batransform(barray, &pos, &size))
    return (NULL);
  bacpy(sub, barray->bytes + pos, size);
  return (barray);
}

barray_t* barmv(barray_t* barray, size_t pos, size_t size)
{
  if (!_batransform(barray, &pos, &size))
    return (NULL);
  memmove(barray->bytes + pos, barray->bytes + pos + size, barray->size - pos + size);
  barray->size -= size;
  return (barray);
}

int bacmp(barray_t* barray, const void* bytes, size_t size)
{
  size_t i;

  if (barray->size != size)
    return (0);
  for (i = 0; i < size; ++i)
  {
    if (barray->bytes[i] != ((const char*)bytes)[i])
      return (0);
  }
  return (1);
}

size_t bafnd(barray_t* barray, const void* bytes, size_t size)
{
  size_t i, j, k;

  for (i = 0; i < barray->size; ++i)
  {
    k = i;
    for (j = 0; j < size && k < barray->size && barray->bytes[k] == ((const char*)bytes)[j]; ++j)
      ++k;
    if (j == size)
      return (i);
  }
  return (PP_NPOS);
}

void badel(barray_t* barray)
{
  free(barray->bytes);
}

int _batransform(barray_t* barray, size_t* pos, size_t* size)
{
  if (*pos + *size < barray->size)
    return (1);
  if (*pos >= barray->size)
    return (0);
  *size = barray->size - *pos;
  return (1);
}

int _barealloc(barray_t* barray, size_t size)
{
  struct allocator alloc;

  alloc = (struct allocator) {
    .data = (void**)&barray->bytes,
    .type_size = sizeof(*barray->bytes),
    .alloc_size = &barray->_alloc
  };
  return (allocator_re(&alloc, barray->size + size, 16));
}