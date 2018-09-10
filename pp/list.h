#ifndef PP_LIST_H_
#define PP_LIST_H_

#include <stdlib.h>

typedef struct node
{
  void* value;
  struct node* next;
  struct node* prev;
} node_t;

typedef struct list
{
  node_t* begin;
  node_t* end;
  size_t size;
} list_t;

/*
  @return       Parameter `list` or NULL on error
  @description  Initialize the list
*/
list_t* list_init(list_t* list);

/*
  @description  Remove all values in `list`
*/
void list_clear(list_t* list);

/*
  @return       First element of `list`
  @description  Returns the first element of the list
  @warning      Undefined behaviour if `list` is empty
*/
void* list_front(const list_t* list);

/*
  @return       Last element of `list`
  @description  Returns the last element of the list
  @warning      Undefined behaviour if `list` is empty
*/
void* list_back(const list_t* list);

/*
  @return       The pointer to the first node value found or NULL otherwise
  @description  Find the first value that matches `value` using the `cmp` function
                If `cmp` is NULL, it will compares pointers
*/
node_t* list_find(list_t* list, void* value, int(*cmp)(const void*, const void*));

/*
  @return       Parameter `dest`
  @description  Swap the nodes `src` and `dest`
*/
node_t* list_swap(node_t* dest, node_t* src);

/*
  @return       Node created from `value`
  @description  Insert a node from `value` at the beginning of `list`
                Do a shallow copy of `value` into `list`
*/
node_t* list_push_front(list_t* list, void* value);

/*
  @return       Node created from `value`
  @description  Insert a node from `value` at the end of `list`
                Do a shallow copy of `value` into `list`
*/
node_t* list_push_back(list_t* list, void* value);

/*
  @return       Parameter `node`
  @description  Insert `node` after `at` in `list`
                Do a shallow copy of `value` into `list`
*/
node_t* list_insert_back(list_t* list, node_t* at, node_t* node);

/*
  @return       Parameter `node`
  @description  Insert `node` before `at` in `list`
                Do a shallow copy of `value` into `list`
*/
node_t* list_insert_front(list_t* list, node_t* at, node_t* node);

/*
  @return       The first value of list
  @description  Remove the first element of `list`
  @warning      Undefined behaviour if list is empty`
*/
void* list_pop(list_t* list);

/*
  @return       Parameter node->next
  @description  Erase `node`
  @warning      Undefined behaviour if `node` not in `list`
*/
node_t* list_erase(list_t* list, node_t* node);

/*
  @return       Parameter `value`
  @description  Remove matching node from `value` in `list`
  @warning      Undefined behaviour if node->value not in `list`
*/
void* list_remove(list_t* list, void* value);

/*
  @return       Created node or NULL on error
  @description  Create and allocate a node from `value` and assign its list
*/
node_t* list_make_node(void* value);

#endif
