#include "clist.h"

#include <stdio.h>

cl_t* cl_pool(unsigned size)
{
  return (NULL);
}

cl_t* cl_create(void* elem)
{
  cl_t* node;

  node = malloc(sizeof(cl_t));
  node->head = malloc(sizeof(cl_head_t));
  node->head->pool = cl_pool(64); //TODO New pool !

  return (cl_set(node, elem));
}

cl_t* cl_set(cl_t* node, void* elem)
{
  node->elem = elem;
  node->next = NULL;
  node->prev = NULL;
  node->head->begin = node;
  node->head->end = node;
  //TODO node->head->pool->size = ???;
  return (node);
}

/*
void pool(cl_t* list, unsigned count)
{
  void* memory;

  if (list->pool.in_use == list->pool.size)
  {
    memory = malloc(sizeof(*list) * (count + list->pool.size));
//    list->pool->available
//    list->begin = realloc(list->begin, sizeof(*list) * (count + pool->size));
    pool->size += count;
  }
}
*/

void cl_pool_add(cl_t* node)
{
  return;

  node->head = node->head->pool->head;
  if (cl_empty(node->head->pool) == 1)
  {
    cl_set(node, NULL);
    //TODO
  }
  cl_push_node(node->head->begin, node);
}

cl_t* cl_pool_next(cl_t* pool)
{
  if (cl_empty(pool) == 1)
  {
    //TODO New pool !
  }
  else
  {

  }
  /*cl_t* next;
  //TODO Check if end of pool !
  next = pool->available->begin;
  pool->available->begin = pool->available->begin->next;
  return (next);*/
  return ((cl_t*)malloc(sizeof(cl_t)));
}

cl_t* cl_swap(cl_t* dest, cl_t* src)
{
  void* elem = dest->elem;

  dest->elem = src->elem;
  src->elem = elem;
  return (dest);
}

cl_t* cl_node(cl_t* list, void* elem)
{
  cl_t* node;

  if (list == NULL)
    return (NULL);
  if ((node = cl_pool_next(list->head->pool)) == NULL)
    return (NULL);
  node->head = list->head;
  node->elem = elem;
  node->next = NULL;
  node->prev = NULL;
  return (node);
}

void* cl_pop(cl_t* list)
{
  void* elem;

  if (list == NULL)
    return (NULL);
  elem = list->head->begin->elem;
  cl_erase(list->head->begin);
  return (elem);
}

cl_t* cl_push(cl_t* node, void* elem)
{
  cl_t* tmp;

  if (node == NULL)
    return (cl_create(elem));

  if (cl_empty(node) == 1)
    return (cl_set(node, elem));

  if ((tmp = cl_node(node, elem)) == NULL)
    return (NULL);
  return (cl_push_node(node, tmp));
}

cl_t* cl_push_node(cl_t* node, cl_t* new_node)
{
  new_node->prev = node;
  if (node->next == NULL) //If end of list
  {
    node->head->end = new_node;
  }
  else
  {
    new_node->next = node->next;
    node->next->prev = new_node;
  }
  node->next = new_node;
  return (new_node);
}

cl_t* cl_push_back(cl_t* node, void* elem)
{
  if (node == NULL)
    return (cl_create(elem));

  if (cl_empty(node) == 1)
    return (cl_set(node, elem));

  return (cl_push(node->head->end, elem));
}

cl_t* cl_push_front(cl_t* node, void* elem)
{
  cl_t* tmp;

  if (node == NULL)
    return (cl_create(elem));

  if (cl_empty(node) == 1)
    return (cl_set(node, elem));

  if ((tmp = cl_push(node->head->begin, elem)) == NULL)
    return (NULL);
  return (cl_swap(node->head->begin, tmp));
}

cl_t* cl_erase(cl_t* node)
{
  if (node == NULL)
    return (NULL);
  cl_pool_add(node);
  if (node->prev == NULL)
    node->head->begin = node->next;
  else
    node->prev->next = node->next;
  if (node->next == NULL)
    node->head->end = node->prev;
  else
    node->next->prev = node->prev;
  return (node->next);
}

int cl_empty(const cl_t* list)
{
  if (list == NULL)
    return (-1);
  return (list->head->begin == NULL);
}

void cl_destroy(cl_t* list)
{
  if (list == NULL)
    return;
  //TODO destroy pool, head, and nodes
}

int main()
{
  cl_t* list = cl_push_back(NULL, "1");
  cl_t* a = cl_push_back(list, "2");
  cl_push_back(list, "4");
  cl_push_front(list, "0");
  cl_push(a, "3");

  cl_erase(list->head->begin);
  cl_erase(list->head->end);
  cl_erase(a);

  cl_push_back(list, "42");

  cl_t* tmp = list->head->begin;
  while (tmp)
  {
    printf("%s\n", (char*)tmp->elem);
    tmp = tmp->next;
  }
  printf("###\n");
  tmp = list->head->end;
  while (tmp)
  {
    printf("%s\n", (char*)tmp->elem);
    tmp = tmp->prev;
  }

  return (0);
}