#include "pp/clist.h"

clist_t* clcrt(clist_t* clist, void* elem)
{
  clist->elem = elem;
  clist->begin = clist;
  clist->end = _clsetalloc(NULL, clist, NULL);
  clist->prev = NULL;
  clist->next = clist->end;
  return (clist->end ? clist : NULL);
}

clist_t* clfrnt(clist_t* clist, void* elem)
{
  clist_t* list;

  if ((list = _clsetalloc(clist->begin->elem, clist->begin, clist->begin->next)) == NULL)
    return (NULL);
  clist->begin->elem = elem;
  clist->begin->next = list;
  return (list);
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