#ifndef LLIST_H_
#define LLIST_H_

#include "mem_pool.h"

typedef struct s_llist ll_t;
typedef struct s_llhead
{
  ll_t* begin;
  ll_t* end;
} ll_head_t;

typedef struct s_llist
{
  void* elem;
  ll_t* next;
  ll_t* prev;
  ll_head_t* head;
} ll_t;

ll_head_t* ll_create();

ll_t* ll_swap(ll_t* dest, ll_t* src); /* Swap elem between src and dest. Return dest */
ll_t* ll_node(ll_head_t*, void*); /* Create a new node and set elem and head fields */

void* ll_pop(ll_head_t*);
ll_t* ll_push(ll_head_t*, ll_t* node, void*); /* Push an element into the list. If node is NULL, it pushes a node at the end */
ll_t* ll_push_node(ll_head_t*, ll_t* node, ll_t*);
ll_t* ll_push_back(ll_head_t*, void*);
ll_t* ll_push_front(ll_head_t*, void*);
ll_t* ll_erase(ll_t*); /* Erase the given node. Return the next node in case of iteration */

int ll_empty(const ll_head_t*); /* Return -1 on error, 0 if NOT empty, 1 if empty */

void ll_destroy(ll_head_t*);

#endif