#include "pp/array.h"

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

void* array_append_at(array_t* array, size_t index, const void* values, size_t nmember)
{
  void* element = array_allocate_at(array, index, nmember);
  if (!element)
  {
    return NULL;
  }
  return (memmove(element, values, nmember * array->membsz));
}

void* array_append(array_t* array, const void* values, size_t nmember)
{
  return (array_append_at(array, array->size, values, nmember));
}

void* array_insert(array_t* array, size_t index, const void* value)
{
  return (array_append_at(array, index, value, 1));
}

void* array_push_front(array_t* array, const void* value)
{
  return (array_append_at(array, 0, value, 1));
}

void* array_push_back(array_t* array, const void* value)
{
  return (array_append_at(array, array->size, value, 1));
}

void* array_create_at(array_t* array, size_t index)
{
  return (array_allocate_at(array, index, 1));
}

void* array_create_front(array_t* array)
{
  return (array_allocate_at(array, 0, 1));
}

void* array_create_back(array_t* array)
{
  return (array_allocate_at(array, array->size, 1));
}

void array_erase_at(array_t* array, size_t index)
{
  memmove(array_at(array, index),
    array_at(array, index + 1),
    (array->size - index) * array->membsz);
  array->size -= 1;
}

void array_erase(array_t* array, const void* element)
{
  size_t index = ((const char*)element - array->content) / array->membsz;
  array_erase_at(array, index);
}

void* array_find(const array_t* array, const void* value, int(*cmp)(const void*, const void*))
{
  void* element;
  for (size_t i = 0; i < array->size; ++i)
  {
    element = array_at(array, i);
    if (!cmp && element == value)
    {
      return element;
    }
    else if (cmp && cmp(element, value))
    {
      return element;
    }
  }
  return NULL;
}

void* array_allocate_at(array_t* array, size_t index, size_t nmember)
{
  if (!array_allocate(array, array->size + nmember))
  {
    return (NULL);
  }
  memmove(array_at(array, index + nmember),
    array_at(array, index),
    (array->size - index) * array->membsz);
  array->size += nmember;
  return (array_at(array, index));
}

array_t* array_allocate(array_t* array, size_t n)
{
  if (array->allocated > n)
  {
    return (array);
  }
  while (array->allocated <= n)
  {
    array->allocated = (array->allocated * 2) + 8;
  }
  array->content = realloc(array->content, array->membsz * array->allocated);
  if (array->content == NULL)
  {
    return (NULL);
  }
  return (array);
}
