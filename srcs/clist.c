#include "pp/clist.h"

clist_t* clcrt(clist_t* clist, void* elem)
{
  clist->elem = elem;
  clist->begin = clist;
  clist->end = _clsetalloc(NULL, clist->begin, NULL);
  clist->prev = NULL;
  clist->next = clist->end;
  return (clist->end ? clist : NULL);
}

clist_t* cladd(clist_t* clist, clist_t* node, void* elem)
{
  clist_t* list;

  if (node == clist->begin)
    return (clfrnt(clist, elem));
  if (node == clist->end)
    return (clbck(clist, elem));
  if ((list = _clsetalloc(elem, node, node->next)) == NULL)
    return (NULL);
  node->next = list;
  node->next->prev = list;
  return (list);
}

clist_t* clfrnt(clist_t* clist, void* elem)
{
  clist_t* list;

  if ((list = _clsetalloc(clist->begin->elem, clist->begin, clist->begin->next)) == NULL)
    return (NULL);
  clist->begin->elem = elem;
  clist->begin->next->prev = list;
  clist->begin->next = list;
  return (clist->begin);
}


clist_t* clbck(clist_t* clist, void* elem)
{
  clist_t* list;

  if ((list = _clsetalloc(elem, clist->end->prev, clist->end)) == NULL)
    return (NULL);
  clist->end->prev->next = list;
  clist->end->prev = list;
  return (list);
}

void* clfndf(clist_t* clist, clfunc func, const void* param)
{
  clist_t* tmp = clist->begin;

  while (tmp != clist->end)
  {
    if (func(tmp, param))
      return (tmp->elem);
    tmp = tmp->next;
  }
  return (NULL);
}

void clrmv(clist_t* clist, clist_t* node)
{
  clist_t* tmp;

  if (node == clist->begin)
  {
    tmp = node->next;
    node->elem = tmp->elem;
    node->next = tmp->next;
    free(tmp);
    return;
  }
  if (node == clist->end)
  {
    tmp = node->prev;
    tmp->prev->next = clist->end;
    node->prev = tmp->prev;
    free(tmp);
    return;
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
}

void cldel(clist_t* clist)
{
  clist_t* tmp1;
  clist_t* tmp2;

  tmp1 = clist->begin->next;
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
  list->elem = elem;
  list->prev = prev;
  list->next = next;
  return (list);
}