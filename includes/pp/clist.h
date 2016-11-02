#ifndef PP_CLIST_HPP_
#define PP_CLIST_HPP_

#include <stdlib.h>

typedef struct s_clist
{
  void* elem;
  struct s_clist* prev;
  struct s_clist* next;
  struct s_clist* begin;
  struct s_clist* end;
} clist_t;

typedef int (*clfunc)(const clist_t*, const void*);

clist_t* clcrt(clist_t*, void*);

clist_t* cladd(clist_t*, clist_t*, void*);
clist_t* clfrnt(clist_t*, void*);
clist_t* clbck(clist_t*, void*);

void clrmv(clist_t*, clist_t*);

void* clfndf(clist_t*, clfunc, const void*);

void cldel(clist_t*);

//CLIST UTILS

clist_t* _clsetalloc(void*, clist_t* prev, clist_t* next);

#endif