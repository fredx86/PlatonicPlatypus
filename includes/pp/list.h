#ifndef PP_LIST_H_
#define PP_LIST_H_

#include <stdlib.h>

typedef struct node node_t;
typedef struct list
{
  node_t* begin;
  node_t* end;
  size_t size;
} list_t;

typedef struct node
{
  void* value;
  list_t* list;
  node_t* next;
  node_t* prev;
} node_t;

/*
  @return      Parameter list or NULL on error
  @description Initialize the list
*/
list_t* list_init(list_t* list);

/*
  @description Remove all values in list
*/
void list_clear(list_t* list);

/*
  @return       Parameter dest
  @description  Swap the nodes src and dest
*/
node_t* list_swap(node_t* dest, node_t* src);

/*
  @return       Node created from value
  @description  Insert a node from value at the beginning of list
                Do a shallow copy of value into list
*/
node_t* list_push_front(list_t* list, void* value);

/*
  @return       Node created from value
  @description  Insert a node from value at the end of list
                Do a shallow copy of value into list
*/
node_t* list_push_back(list_t* list, void* value);

/*
  @return       Parameter node
  @description  Insert node after at in list
                Do a shallow copy of value into list
*/
node_t* list_insert_back(list_t* list, node_t* at, node_t* node);

/*
  @return       Parameter node
  @description  Insert node before at in list
                Do a shallow copy of value into list
*/
node_t* list_insert_front(list_t* list, node_t* at, node_t* node);

/*
  @return       The first element of list
  @description  Remove the first element of list
  @warning      Undefined behaviour if list is empty
*/
void* list_pop(list_t* list);

/*
  @return       Parameter node->next
  @description  Erase node
*/
node_t* list_erase(node_t* node);

/*
  @return       Created node or NULL on error
  @description  Create and allocate a node from value and assign its list
*/
node_t* list_make_node(list_t* list, void* value);

#endif
