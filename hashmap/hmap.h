#ifndef HMAP_H_
#define HMAP_H_

#include <stdlib.h>
#include <string.h>
#include "llist.h"

typedef size_t (*hm_hash_f)(const char*, size_t);

typedef enum e_hmsize
{
  HM_SMALL = 256,
  HM_MEDIUM = 1024,
  HM_BIG = 4096,
  HM_VERY_BIG = 8192
} hm_size;

typedef enum e_hmkey
{
  HM_STRING,
  HM_VALUE
} hm_key_t;

typedef struct s_hmpair
{
  const void* key;
  void* value;
} hm_pair_t;

typedef struct s_hmap
{
  hm_hash_f hash;
  hm_key_t key;
  size_t size;
  ll_head_t** buckets;
} hm_t;

hm_t* hm_create(hm_size, hm_key_t, hm_hash_f);

void hm_clear(hm_t*);

hm_pair_t* hm_put(hm_t*, const void*, void*);
hm_pair_t* hm_get(hm_t*, const void*);

void hm_destroy(hm_t*);

size_t hm_key_index(hm_t*, const void* key);
hm_pair_t* hm_add_keyval(hm_t*, const void*, void*);
hm_pair_t* hm_key_find(hm_t*, const ll_head_t*, const void*);
int hm_key_cmp(hm_key_t, const void*, const void*);
size_t hm_key_size(hm_key_t, const void*);

hm_pair_t* hm_make_pair(const void*, void*);
size_t hm_jenkins(const char*, size_t); /* Jenkins hash function -> https://en.wikipedia.org/wiki/Jenkins_hash_function */

#endif
