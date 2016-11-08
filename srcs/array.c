#include "pp/array.h"

array_t* arcrt(array_t* array, size_t size, void** items)
{
  size_t i;

  array->item = NULL;
  array->_alloc = 0;
  array->size = 0;
  if ((array->item = malloc(sizeof(*array->item))) == NULL)
    return (NULL);
  if (!_arrealloc(array, size))
  {
    free(array->item);
    return (NULL);
  }
  for (i = 0; i < size; ++i)
    array->item[i] = items[i];
  array->size = size;
  return (array);
}

array_t* aradd(array_t* array, void* item)
{
  if (!_arrealloc(array, 1))
    return (NULL);
  array->item[array->size++] = item;
  return (array);
}

void arrmvv(array_t* array, const void* item)
{
  //TODO
  (void)array; (void)item;
}

void arrmvi(array_t* array, size_t i)
{
  //TODO
  (void)array; (void)i;
}

void ardel(array_t* array)
{
  free(array->item);
}

int _arrealloc(array_t* array, size_t size)
{
  struct allocator alloc;

  alloc = (struct allocator) {
    .data = (void**)&array->item,
    .type_size = sizeof(*array->item),
    .alloc_size = &array->_alloc
  };
  return (alloc_pow2(&alloc, array->size + size, 4));
}