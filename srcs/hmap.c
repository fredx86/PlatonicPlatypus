#include "pp/hmap.h"

hmap_t* hmcrt(hmap_t* hmap, size_t size, hmkey_t key)
{
  hmap->size = size;
  hmap->hash = &_hmjenkins;
  hmap->key = key;
  if ((hmap->buckets = calloc(size, sizeof(*hmap->buckets))) == NULL)
    return (NULL);
  return (hmap);
}

hmpair_t* hmadd(hmap_t* hmap, const void* key, void* value)
{
  hmpair_t* pair;

  if ((pair = hmget(hmap, key)) != NULL)
  {
    pair->value = value;
    return (pair);
  }
  return (_hmadd_keyval(hmap, key, value));
}

hmpair_t* hmget(hmap_t* hmap, const void* key)
{
  const void* key_keytype[] = { key, &hmap->key };
  size_t index = hmap->hash(key, _hmkey_size(hmap->key, key)) % hmap->size;

  if (hmap->buckets[index] == NULL)
    return (NULL);
  return (clfndf(hmap->buckets[index], &_hmkey_find, key_keytype));
}

void hmdel(hmap_t* hmap)
{
  size_t i;
  clist_t* it;
  clist_t* tmp_it;

  for (i = 0; i < hmap->size; ++i)
  {
    if (hmap->buckets[i] == NULL)
      continue;
    it = hmap->buckets[i]->begin;
    while (it != hmap->buckets[i]->end)
    {
      tmp_it = it->next;
      free(it); //free hmpair_t
      it = tmp_it;
    }
    cldel(hmap->buckets[i]);
  }
  free(hmap->buckets);
}

hmpair_t* _hmadd_keyval(hmap_t* hmap, const void* key, void* value)
{
  clist_t* list;
  hmpair_t* pair;
  size_t index = hmap->hash(key, _hmkey_size(hmap->key, key)) % hmap->size;

  if (hmap->buckets[index] == NULL)
  {
    if ((list = malloc(sizeof(*list))) == NULL ||
      (pair = _hmpair(key, value)) == NULL)
      return (NULL);
    hmap->buckets[index] = list;
    clcrt(list, pair);
    return (pair);
  }
  else //Collisions
  {
    if ((pair = _hmpair(key, value)) == NULL)
      return (NULL);
    clbck(hmap->buckets[index], pair);
  }
  return (pair);
}

int _hmkey_find(const clist_t* list, const void* param)
{
  hmpair_t* pair = (hmpair_t*)list->elem;
  const void* key = ((const void**)param)[0];
  hmkey_t* keytype = (hmkey_t*)((const void**)param)[1];
  return (_hmkey_cmp(*keytype, pair->key, key));
}

int _hmkey_cmp(hmkey_t keytype, const void* x, const void* y)
{
  if (keytype == HM_STRING)
    return (strcmp((const char*)x, (const char*)y) == 0);
  return (x == y);
}

size_t _hmkey_size(hmkey_t keytype, const void* key)
{
  if (keytype == HM_STRING)
    return (strlen((const char*)key));
  return (sizeof(key));
}

hmpair_t* _hmpair(const void* key, void* value)
{
  hmpair_t* pair;

  if ((pair = malloc(sizeof(*pair))) == NULL)
    return (NULL);
  pair->key = key;
  pair->value = value;
  return (pair);
}

size_t _hmjenkins(const char* key, size_t len)
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