#include <assert.h>
#include <string.h>

#include <stdio.h>

#include "pp/list.h"

static int test_find_predicate(const void* left, const void* right)
{
  (void)right;
  return strcmp((char*)left, "d") == 0;
}

static void test_push_back()
{
  size_t i = 0;
  list_t list;
  char *values[] = { "a", "b", "c", "d", NULL };

  assert(list_init(&list));

  while (values[i])
  {
    assert(list_push_back(&list, values[i++]));
  }
  assert(list.size == i);

  i = 0;
  while (list.size > 0)
  {
    assert(strcmp(list_pop(&list), values[i++]) == 0);
  }

  list_clear(&list);
}

static void test_push_front()
{
  size_t i = 0;
  list_t list;
  char *values[] = { "a", "b", "c", "d", NULL };

  assert(list_init(&list));

  while (values[i])
  {
    assert(list_push_front(&list, values[i++]));
  }
  assert(list.size == i);

  i = 3;
  while (list.size > 0)
  {
    assert(strcmp(list_pop(&list), values[i--]) == 0);
  }

  list_clear(&list);
}

static void test_find()
{
  list_t list;
  char *values[] = { "a", "b", "c", "d", NULL };

  assert(list_init(&list));

  for (size_t i = 0; values[i]; ++i)
  {
    assert(list_push_back(&list, values[i]));
  }

  node_t* found = list_find(&list, values[1], NULL);
  assert(found != NULL);
  assert(strcmp((char*)found->value, "b") == 0);

  assert(list_find(&list, "notInList", NULL) == NULL);

  found = list_find(&list, NULL, &test_find_predicate);
  assert(found != NULL);
  assert(strcmp((char*)found->value, "d") == 0);

  assert(list.size == 4);

  list_clear(&list);
}

static void test_remove()
{
  list_t list;
  char *values[] = { "a", "b", "c", "d", NULL };

  assert(list_init(&list));

  for (size_t i = 0; values[i]; ++i)
  {
    assert(list_push_back(&list, values[i]));
  }

  void* removed = list_remove(&list, values[1]);
  assert(removed != NULL);
  assert(strcmp((char*)removed, "b") == 0);

  assert(list.size == 3);
  assert(strcmp((char*)list.begin->value, "a") == 0);
  assert(strcmp((char*)list.begin->next->value, "c") == 0);

  list_clear(&list);
}

int main()
{
  test_push_back();
  test_push_front();
  test_find();
  test_remove();
  return 0;
}
