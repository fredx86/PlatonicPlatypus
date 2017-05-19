#include "hmap.h"

hm_t* hm_create(hm_size size, hm_len_f key_size, hm_cmp_f key_cmp, hm_hash_f hash_func)
{
  hm_t* map;

  if (size == 0 || (map = malloc(sizeof(*map))) == NULL)
    return (NULL);
  map->size = size;
  map->hash = (hash_func == NULL ? &hm_jenkins : hash_func);
  map->key_size = key_size;
  map->key_cmp = key_cmp;
  if ((map->buckets = calloc(size, sizeof(*map->buckets))) == NULL)
    return (NULL);
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
      free(ll_pop(map->buckets[i]));
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
  free(map->buckets);
  free(map);
}

size_t hm_key_index(hm_t* map, const void* key)
{
  return (map->hash(key, map->key_size(key)) % map->size);
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
    if (map->key_cmp(key, pair->key))
      return (pair);
    it = it->next;
  }
  return (NULL);
}

hm_pair_t* hm_make_pair(const void* key, void* value)
{
  hm_pair_t* pair;

  if ((pair = malloc(sizeof(*pair))) == NULL)
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

size_t hm_len_string(const void* string)
{
  return (strlen((const char*)string));
}

int hm_cmp_string(const void* a, const void* b)
{
  return (strcmp((const char*)a, (const char*)b) == 0);
}

size_t hm_len_int(const void* intptr)
{
  (void)intptr;
  return (sizeof(int));
}

int hm_cmp_int(const void* a, const void* b)
{
  return (*(int*)a == *(int*)b);
}