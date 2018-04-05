#include "array.h"

array_t* array_init(array_t* array, size_t membsz)
{
  array->membsz = membsz;
  array->content = NULL;
  array->size = 0;
  array->allocated = 0;
  return (array);
}

void array_clear(array_t* array)
{
  free(array->content);
  array->content = NULL;
  array->size = 0;
  array->allocated = 0;
}

inline void* array_at(const array_t* array, size_t index)
{
  return (array->content + (index * array->membsz));
}

void* array_append_at(array_t* array, size_t index, void* values, size_t nmember)
{
  if (!array_alloca(array, array->size + nmember))
  {
    return (NULL);
  }
  memmove(array_at(array, index + nmember),
    array_at(array, index),
    (array->size - index) * array->membsz);
  array->size += nmember;
  return (memmove(array_at(array, index), values, nmember * array->membsz));
}

void* array_append(array_t* array, void* values, size_t nmember)
{
  return (array_append_at(array, array->size, values, nmember));
}

void* array_insert(array_t* array, size_t index, void* value)
{
  return (array_append_at(array, index, value, 1));
}

void* array_push_front(array_t* array, void* value)
{
  return (array_append_at(array, 0, value, 1));
}

void* array_push_back(array_t* array, void* value)
{
  return (array_append_at(array, array->size, value, 1));
}

void array_erase(array_t* array, size_t index)
{
  memmove(array_at(array, index),
    array_at(array, index + 1),
    (array->size - index) * array->membsz);
  array->size -= 1;
}

array_t* array_alloca(array_t* array, size_t n)
{
  if (array->allocated * array->membsz > n * array->membsz)
  {
    return (array);
  }
  array->allocated = (array->allocated * 2) + 8;
  array->content = realloc(array->content, array->membsz * array->allocated);
  if (array->content == NULL)
  {
    return (NULL);
  }
  return (array);
}
