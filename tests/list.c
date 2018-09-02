#include <assert.h>
#include <string.h>

#include <stdio.h>

#include "pp/list.h"

static void push_back()
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

static void push_front()
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

int main()
{
  push_back();
  push_front();
  return 0;
}
