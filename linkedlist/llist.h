#ifndef LLIST_H_
#define LLIST_H_

#include <stdlib.h>

typedef struct s_llist ll_t;
typedef struct s_llhead
{
  ll_t* begin;
  ll_t* end;
  size_t size;
} ll_head_t;

typedef struct s_llist
{
  void* elem;
  ll_t* next;
  ll_t* prev;
  ll_head_t* head;
} ll_t;

ll_head_t* ll_create();

/* Clear the linked list. Does NOT free() the ll_t->elem */
void ll_clear(ll_head_t*);

/* Swap elem between src and dest. Return dest */
ll_t* ll_swap(ll_t* dest, ll_t* src);

/* Dequeue 1 node from beginning of the list. Return the elem field */
void* ll_pop(ll_head_t*);

/* Push an element into the list. If node is NULL, it pushes a node at the end */
ll_t* ll_push(ll_head_t*, ll_t* node, void*);
ll_t* ll_push_node(ll_head_t*, ll_t* node, ll_t*);
ll_t* ll_push_back(ll_head_t*, void*);
ll_t* ll_push_front(ll_head_t*, void*);

/* Erase the given node. Return the next node in case of iteration */
ll_t* ll_erase(ll_t*);

/* Return -1 on error, 0 if NOT empty, 1 if empty */
int ll_empty(const ll_head_t*);

void ll_destroy(ll_head_t*);

/* Create a new node and set elem and head fields */
ll_t* ll_make_node(ll_head_t*, void*);

#endif
