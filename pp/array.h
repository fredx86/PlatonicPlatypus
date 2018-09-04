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
  @return      Parameter `array` or NULL on error
  @description Initialize `array` as an array of member size `membsz`
*/
array_t* array_init(array_t* array, size_t membsz);

/*
  @description Remove all values in `array`
*/
void array_clear(array_t* array);

/*
  @return      The value at position `index` in the array
*/
void* array_at(const array_t* array, size_t index);

/*
  @return       Parameter `value`
  @description  Find the first value of the node that matches `value` using the `cmp` function
                If `cmp` is NULL, it will compares pointers
*/
void* array_find(const array_t* array, const void* value, int(*cmp)(const void*, const void*));

/*
  @return       The first emplaced value or NULL on error
  @description  Emplace `values` at position `index` of array
                Do a deep copy of values into `array`
  @warning      Undefined behaviour if `index` is greater than the array size
*/
void* array_emplace(array_t* array, size_t index, const void* values, size_t nmember);

/*
  @return       The first emplaced value or NULL on error
  @description  Emplace `values` at the beginning of array
                Do a deep copy of `values` into `array`
*/
void* array_emplace_front(array_t* array, const void* values, size_t nmember);

/*
  @return       The first emplaced value or NULL on error
  @description  Emplace `values` at the end of array
                Do a deep copy of `values` into `array`
*/
void* array_emplace_back(array_t* array, const void* values, size_t nmember);

/*
  @return       The value inserted or NULL on error
  @description  Insert `value` at position `index` of array
                Do a deep copy of `value` into `array`
  @warning      Undefined behaviour if `index` is greater than the array size
*/
void* array_insert(array_t* array, size_t index, const void* value);

/*
  @return       The value inserted or NULL on error
  @description  Insert `value` at the beginning of array
                Do a deep copy of `value` into `array`
*/
void* array_push_front(array_t* array, const void* value);

/*
  @return       The value inserted or NULL on error
  @description  Insert `value` at the end of array
                Do a deep copy of `value` into `array`
*/
void* array_push_back(array_t* array, const void* value);

/*
  @return       The value added or NULL on error
  @description  Add an value at position `index` of array
  @warning      Undefined behaviour if `index` is greater than the array size
                The value is not initialized
*/
void* array_add(array_t* array, size_t index);

/*
  @return       The value added or NULL on error
  @description  Add an value at position `index` of array
  @warning      The value is not initialized
*/
void* array_add_front(array_t* array);

/*
  @return       The value added or NULL on error
  @description  Add an value at the beginning of array
  @warning      The value is not initialized
*/
void* array_add_back(array_t* array);

/*
  @description  Remove values at position `index` of array for `nmember`
  @warning      Undefined behaviour if `index` is greater than the array size
                Undefined behaviour if `nmember` + `index` is greater than the array size
*/
void array_erase(array_t* array, size_t index, size_t nmember);

/*
  @description  Remove value at position `index` of array
  @warning      Undefined behaviour if `index` is greater than the array size
*/
void array_erase_at(array_t* array, size_t index);

/*
  @description  Remove `value` from array
  @warning      Undefined behaviour if `value` is not in array
*/
void array_remove(array_t* array, const void* value);

/*
  @return       The first created value or NULL on error
  @description  Create `n` values at position `index` of array
  @warning      Undefined behaviour if `index` is greater than the array size
                The values are not initialized
*/
void* array_create_at(array_t* array, size_t index, size_t n);

/*
  @return       Parameter `array` or NULL on error
  @description  Allocate memory for at least `n` values in array
*/
array_t* array_allocate(array_t* array, size_t n);

#endif
