#ifndef PP_HMAP_HPP_
#define PP_HMAP_HPP_

#include <stdlib.h>
#include <string.h>
#include "clist.h"

typedef size_t (*hmhashfunc)(const char*, size_t);

typedef enum e_hmkey
{
  HM_STRING,
  HM_VALUE
} hmkey_t;

typedef struct s_hmpair
{
  const void* key;
  void* value;
} hmpair_t;

/*
hmap = List of buckets
Bucket = Chained list (clist_t)
Chained list elem = Pair(key, value) (hmpair_t)
*/
typedef struct s_hmap
{
  hmhashfunc hash;
  hmkey_t key;
  size_t size;
  clist_t **buckets;
} hmap_t;

hmap_t* hmcrt(hmap_t*, size_t, hmkey_t);

hmpair_t* hmadd(hmap_t*, const void*, void*);
hmpair_t* hmget(hmap_t*, const void*);

void hmdel(hmap_t*);

/* HMAP UTILS */

hmpair_t* _hmadd_keyval(hmap_t*, const void*, void*);

int _hmkey_find(const clist_t*, const void*);
int _hmkey_cmp(hmkey_t, const void*, const void*);
size_t _hmkey_size(hmkey_t, const void*);

hmpair_t* _hmpair(const void*, void*);
size_t _hmjenkins(const char*, size_t);

#endif