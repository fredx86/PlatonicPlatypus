#ifndef PP_CLIST_HPP_
#define PP_CLIST_HPP_

#include <stdlib.h>

typedef struct s_clist
{
  void* item;
  struct s_clist* prev;
  struct s_clist* next;
  struct s_clist* _begin;
  struct s_clist* _end;
} clist_t;

typedef int (*clfunc)(const clist_t*, const void*);

clist_t* clcrt(clist_t*, size_t, void**);

clist_t* cladd(clist_t*, clist_t*, void*);
clist_t* clfrnt(clist_t*, void*);
clist_t* clbck(clist_t*, void*);

clist_t* clbegin(clist_t*);
clist_t* clend(clist_t*);

void* clpop(clist_t*);
clist_t* clrmv(clist_t*, clist_t*);

int cliter(clist_t*, clist_t** it);
void* clfndf(clist_t*, clfunc, const void*);
int clempty(const clist_t*);

void cldel(clist_t*);

//CLIST UTILS

clist_t* _clsetalloc(void*, clist_t* prev, clist_t* next);

#endif
