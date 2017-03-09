#ifndef CLIST_H_
#define CLIST_H_

#include <stdlib.h>

typedef struct s_clist cl_t;
typedef struct s_clhead
{
  cl_t* begin;
  cl_t* end;
  cl_t* pool;
} cl_head_t;

typedef struct s_clist
{
  void* elem;
  cl_t* next;
  cl_t* prev;
  cl_head_t* head;
} cl_t;

cl_t* cl_create(void*);
cl_t* cl_set(cl_t*, void*);

cl_t* cl_swap(cl_t* dest, cl_t* src); /* Swap elem between src and dest. Return dest */
cl_t* cl_node(cl_t*, void*); /* Create a new node and set elem and head fields */

void* cl_pop(cl_t*);
cl_t* cl_push(cl_t* node, void*); /* Push an element into the list. If node is NULL, it create a new list */
cl_t* cl_push_node(cl_t* node, cl_t*);
cl_t* cl_push_back(cl_t*, void*);
cl_t* cl_push_front(cl_t*, void*);
cl_t* cl_erase(cl_t*); /* Erase the given node. Return the next node in case of iteration */

int cl_empty(const cl_t*); /* Return -1 on error, 0 if NOT empty, 1 if empty */

void cl_destroy(cl_t*);

#endif