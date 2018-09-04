#include "pp/array.h"

array_t* array_init(array_t* array, size_t membsz)
{
  array->membsz = membsz;
  array->content = NULL;
  array->size = 0;
  array->allocated = 0;
  return array;
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
  return array->content + (index * array->membsz);
}

void* array_find(const array_t* array, const void* value, int(*cmp)(const void*, const void*))
{
  void* current;
  for (size_t i = 0; i < array->size; ++i)
  {
    current = array_at(array, i);
    if (!cmp && current == value)
    {
      return current;
    }
    else if (cmp && cmp(current, value))
    {
      return current;
    }
  }
  return NULL;
}

void* array_emplace(array_t* array, size_t index, const void* values, size_t nmember)
{
  void* value = array_create_at(array, index, nmember);
  if (!value)
  {
    return NULL;
  }
  return memmove(value, values, nmember * array->membsz);
}

void* array_emplace_front(array_t* array, const void* values, size_t nmember)
{
  return array_emplace(array, array->size, values, nmember);
}

void* array_emplace_back(array_t* array, const void* values, size_t nmember)
{
  return array_emplace(array, 0, values, nmember);
}

void* array_insert(array_t* array, size_t index, const void* value)
{
  return array_emplace(array, index, value, 1);
}

void* array_push_front(array_t* array, const void* value)
{
  return array_emplace(array, 0, value, 1);
}

void* array_push_back(array_t* array, const void* value)
{
  return array_emplace(array, array->size, value, 1);
}

void* array_add(array_t* array, size_t index)
{
  return array_create_at(array, index, 1);
}

void* array_add_front(array_t* array)
{
  return array_create_at(array, 0, 1);
}

void* array_add_back(array_t* array)
{
  return array_create_at(array, array->size, 1);
}

void array_erase(array_t* array, size_t index, size_t nmember)
{
  memmove(array_at(array, index),
    array_at(array, index + nmember),
    (array->size - (index + nmember)) * array->membsz);
  array->size -= nmember;
}

void array_erase_at(array_t* array, size_t index)
{
  array_erase(array, index, 1);
}

void array_remove(array_t* array, const void* value)
{
  size_t index = ((const char*)value - array->content) / array->membsz;
  array_erase(array, index, 1);
}

void* array_create_at(array_t* array, size_t index, size_t n)
{
  if (!array_allocate(array, array->size + n))
  {
    return NULL;
  }
  memmove(array_at(array, index + n),
    array_at(array, index),
    (array->size - index) * array->membsz);
  array->size += n;
  return array_at(array, index);
}

array_t* array_allocate(array_t* array, size_t n)
{
  if (array->allocated > n)
  {
    return array;
  }
  while (array->allocated <= n)
  {
    array->allocated = (array->allocated * 2) + 8;
  }
  array->content = realloc(array->content, array->membsz * array->allocated);
  return array->content == NULL ? NULL : array;
}
