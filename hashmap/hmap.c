#include "hmap.h"

hm_t* hm_create(hm_size size, hm_key_t key_type, hm_hash_f hash_func)
{
  hm_t* map;

  if (size == 0 || (map = mem_get(sizeof(*map))) == NULL)
    return (NULL);
  map->size = size;
  map->hash = (hash_func == NULL ? &hm_jenkins : hash_func);
  map->key = key_type;
  if ((map->buckets = mem_get(size * sizeof(*map->buckets))) == NULL)
    return (NULL);
  memset(map->buckets, 0, size * sizeof(*map->buckets));
  return (map);
}

void hm_clear(hm_t* map)
{
  if (map == NULL)
    return;
  for (size_t i = 0; i < map->size; ++i)
  {
    if (map->buckets[i] == NULL)
      continue;
    while (ll_empty(map->buckets[i]) == 0)
      mem_release(ll_pop(map->buckets[i]));
    ll_destroy(map->buckets[i]);
    map->buckets[i] = NULL;
  }
}

hm_pair_t* hm_put(hm_t* map, const void* key, void* value)
{
  hm_pair_t* pair;

  if (map == NULL)
    return (NULL);
  if ((pair = hm_get(map, key)) != NULL)
  {
    pair->value = value;
    return (pair);
  }
  return (hm_add_keyval(map, key, value));
}

hm_pair_t* hm_get(hm_t* map, const void* key)
{
  if (map == NULL)
    return (NULL);
  return (hm_key_find(map, map->buckets[hm_key_index(map, key)], key));
}

void hm_destroy(hm_t* map)
{
  if (map == NULL)
    return;
  hm_clear(map);
  mem_release(map->buckets);
  mem_release(map);
}

size_t hm_key_index(hm_t* map, const void* key)
{
  return (map->hash(key, hm_key_size(map->key, key)) % map->size);
}

hm_pair_t* hm_add_keyval(hm_t* map, const void* key, void* value)
{
  hm_pair_t* pair;
  size_t index = hm_key_index(map, key);

  if (map->buckets[index] == NULL)
  {
    if ((map->buckets[index] = ll_create()) == NULL)
      return (NULL);
  }
  if ((pair = hm_make_pair(key, value)) == NULL)
    return (NULL);
  if (ll_push_back(map->buckets[index], pair) == NULL)
    return (NULL);
  return (pair);
}

hm_pair_t* hm_key_find(hm_t* map, const ll_head_t* head, const void* key)
{
  ll_t* it;
  hm_pair_t* pair;

  if (head == NULL)
    return (NULL);
  it = head->begin;
  while (it)
  {
    pair = (hm_pair_t*)it->elem;
    if (hm_key_cmp(map->key, key, pair->key))
      return (pair);
    it = it->next;
  }
  return (NULL);
}

int hm_key_cmp(hm_key_t key_type, const void* x, const void* y)
{
  if (key_type == HM_STRING)
    return (strcmp((const char*)x, (const char*)y) == 0);
  return (x == y);
}

size_t hm_key_size(hm_key_t key_type, const void* key)
{
  if (key_type == HM_STRING)
    return (strlen((const char*)key));
  return (sizeof(key));
}

hm_pair_t* hm_make_pair(const void* key, void* value)
{
  hm_pair_t* pair;

  if ((pair = mem_get(sizeof(*pair))) == NULL)
    return (NULL);
  pair->key = key;
  pair->value = value;
  return (pair);
}

size_t hm_jenkins(const char* key, size_t len)
{
  size_t i = 0;
  size_t hash = 0;

  while (i < len)
  {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
    ++i;
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return (hash);
}
