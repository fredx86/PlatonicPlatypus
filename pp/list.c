#include "pp/list.h"

list_t* list_init(list_t* list)
{
  list->begin = NULL;
  list->end = NULL;
  list->size = 0;
  return (list);
}

void list_clear(list_t* list)
{
  while (list->size > 0)
  {
    list_pop(list);
  }
}

node_t* list_swap(node_t* dest, node_t* src)
{
  void* value = dest->value;

  dest->value = src->value;
  src->value = value;
  return (dest);
}

node_t* list_push_front(list_t* list, void* value)
{
  node_t* node = list_make_node(value);

  if (node == NULL)
  {
    return (NULL);
  }
  return (list_insert_front(list, list->begin, node));
}

node_t* list_push_back(list_t* list, void* value)
{
  node_t* node = list_make_node(value);

  if (node == NULL)
  {
    return (NULL);
  }
  return (list_insert_back(list, list->end, node));
}

node_t* list_insert_back(list_t* list, node_t* at, node_t* node)
{
  list->size += 1;
  if (at == NULL)
  {
    list->begin = node;
    list->end = node;
    return (node);
  }
  node->prev = at;
  if (at->next == NULL) //If end of list
  {
    list->end = node;
  }
  else
  {
    node->next = at->next;
    at->next->prev = node;
  }
  at->next = node;
  return (node);
}

node_t* list_insert_front(list_t* list, node_t* at, node_t* node)
{
  list_insert_back(list, at, node);
  if (at != NULL)
  {
    return (list_swap(at, node));
  }
  return (node);
}

void* list_pop(list_t* list)
{
  void* value = list->begin->value;
  list_erase(list, list->begin);
  return (value);
}

node_t* list_erase(list_t* list, node_t* node)
{
  node_t* next = node->next;

  list->size -= 1;
  if (node->prev == NULL)
  {
    list->begin = node->next;
  }
  else
  {
    node->prev->next = node->next;
  }
  if (node->next == NULL)
  {
    list->end = node->prev;
  }
  else
  {
    node->next->prev = node->prev;
  }
  free(node);
  return (next);
}

node_t* list_make_node(void* value)
{
  node_t* node;

  if ((node = malloc(sizeof(*node))) == NULL)
  {
    return (NULL);
  }
  node->value = value;
  node->next = NULL;
  node->prev = NULL;
  return (node);
}
