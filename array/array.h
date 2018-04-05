#ifndef PP_ARRAY_H_
#define PP_ARRAY_H_

#include <stdlib.h>
#include <string.h>

typedef struct array
{
  char* content;
  size_t size;
  size_t membsz;
  size_t allocated;
} array_t;

/*
  @return      Parameter array or NULL on error
  @description Initialize array as an array of member size membsz
*/
array_t* array_init(array_t* array, size_t membsz);

/*
  @description Remove all values in array
*/
void array_clear(array_t* array);

/*
  @return      The element at position index in the array
*/
void* array_at(const array_t*, size_t index);

/*
  @return       The inserted element
  @description  Append values at position index of array
  @warning      Undefined behaviour if index is greater than the array size
*/
void* array_append_at(array_t* array, size_t index, void* values, size_t nmember);

/*
  @return       The inserted element
  @description  Append values at the end of array
*/
void* array_append(array_t* array, void* values, size_t nmember);

/*
  @return       The element inserted
  @description  Insert value at position index of array
  @warning      Undefined behaviour if index is greater than the array size
*/
void* array_insert(array_t* array, size_t index, void* value);

/*
  @return       The element inserted
  @description  Insert value at the beginning of array
*/
void* array_push_front(array_t* array, void* value);

/*
  @return       The element inserted
  @description  Insert value at the end of array
*/
void* array_push_back(array_t* array, void* value);

/*
  @description  Remove element at position index of array
  @warning      Undefined behaviour if index is greater than the array size
*/
void array_erase(array_t* array, size_t index);

/*
  @return       Parameter array or NULL on error
  @description  Allocate memory for at least n elements in array
*/
array_t* array_alloca(array_t* array, size_t n);

#endif
