#include "pp/clist.h"

clist_t* clcrt(clist_t* clist, size_t size, void** items)
{
  size_t i;

  clist->item = NULL;
  clist->_begin = clist;
  if ((clist->_end = _clsetalloc(NULL, clist->_begin, NULL)) == NULL)
    return (NULL);
  clist->prev = NULL;
  clist->next = clist->_end;
  for (i = 0; i < size; ++i)
  {
    if (!clbck(clist, items[i]))
      return (NULL);
  }
  return (clist);
}

clist_t* cladd(clist_t* clist, clist_t* node, void* item)
{
  clist_t* list;

  if (node == NULL)
    return (clbck(clist, item));
  if (node == clist->_begin || node == clist->_end)
    return (NULL);
  if ((list = _clsetalloc(item, node, node->next)) == NULL)
    return (NULL);
  node->next = list;
  node->next->prev = list;
  return (list);
}

clist_t* clfrnt(clist_t* clist, void* item)
{
  clist_t* list;

  if ((list = _clsetalloc(item, clist->_begin, clist->_begin->next)) == NULL)
    return (NULL);
  clist->_begin->next->prev = list;
  clist->_begin->next = list;
  return (list);
}

clist_t* clbck(clist_t* clist, void* item)
{
  clist_t* list;

  if ((list = _clsetalloc(item, clist->_end->prev, clist->_end)) == NULL)
    return (NULL);
  clist->_end->prev->next = list;
  clist->_end->prev = list;
  return (list);
}

clist_t* clbegin(clist_t* clist)
{
  return (clist->_begin->next == clist->_end ? NULL : clist->_begin->next);
}

clist_t* clend(clist_t* clist)
{
  return (clist->_end->prev == clist->_begin ? NULL : clist->_end->prev);
}

void* clpop(clist_t* clist)
{
  void* elem;
  clist_t* first = clbegin(clist);

  if (first == NULL)
    return (NULL);
  elem = first->item;
  clrmv(clist, first);
  return (elem);
}

clist_t* clrmv(clist_t* clist, clist_t* node)
{
  if (node == clist->_begin || node == clist->_end)
    return (NULL);
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
  return (clist);
}

int cliter(clist_t* clist, clist_t** it)
{
  clist_t* end = clend(clist);

  if (!end)
    return (0);
  if (*it == NULL)
  {
    *it = clbegin(clist);
    return (1);
  }
  if (*it != end)
  {
    *it = (*it)->next;
    return (1);
  }
  return (0);
}

void* clfndf(clist_t* clist, clfunc func, const void* param)
{
  clist_t* tmp = clist->_begin->next;

  while (tmp != clist->_end)
  {
    if (func(tmp, param))
      return (tmp->item);
    tmp = tmp->next;
  }
  return (NULL);
}

int clempty(const clist_t* clist)
{
  return (clist->_begin->next == clist->_end);
}

void cldel(clist_t* clist)
{
  clist_t* tmp1;
  clist_t* tmp2;

  tmp1 = clist->_begin->next;
  while (tmp1)
  {
    tmp2 = tmp1->next;
    free(tmp1);
    tmp1 = tmp2;
  }
}

clist_t* _clsetalloc(void* elem, clist_t* prev, clist_t* next)
{
  clist_t* list = malloc(sizeof(*list));

  if (list == NULL)
    return (NULL);
  list->item = elem;
  list->prev = prev;
  list->next = next;
  return (list);
}
