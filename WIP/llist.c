#include "llist.h"
#include <stdio.h>

ll_head_t* ll_create()
{
  ll_head_t* head;

  if ((head = mem_get(sizeof(*head))) == NULL)
    return (NULL);
  head->begin = NULL;
  head->end = NULL;
  return (head);
}

ll_t* ll_swap(ll_t* dest, ll_t* src)
{
  void* elem = dest->elem;

  dest->elem = src->elem;
  src->elem = elem;
  return (dest);
}

ll_t* ll_node(ll_head_t* head, void* elem)
{
  ll_t* node;

  if (head == NULL)
    return (NULL);
  if ((node = mem_get(sizeof(*node))) == NULL)
    return (NULL);
  node->head = head;
  node->elem = elem;
  node->next = NULL;
  node->prev = NULL;
  return (node);
}

void* ll_pop(ll_head_t* head)
{
  void* elem;

  if (head == NULL || ll_empty(head) == 1)
    return (NULL);
  elem = head->begin->elem;
  ll_erase(head->begin);
  return (elem);
}

ll_t* ll_push(ll_head_t* head, ll_t* node, void* elem)
{
  ll_t* tmp;

  if (head == NULL)
    return (NULL);

  if ((tmp = ll_node(head, elem)) == NULL)
    return (NULL);
  return (ll_push_node(head, node, tmp));
}

ll_t* ll_push_node(ll_head_t* head, ll_t* node, ll_t* new_node)
{
  if (node == NULL)
  {
    head->begin = new_node;
    head->end = new_node;
    return (new_node);
  }
  new_node->prev = node;
  if (node->next == NULL) //If end of list
  {
    head->end = new_node;
  }
  else
  {
    new_node->next = node->next;
    node->next->prev = new_node;
  }
  node->next = new_node;
  return (new_node);
}

ll_t* ll_push_back(ll_head_t* head, void* elem)
{
  if (head == NULL)
    return (NULL);
  return (ll_push(head, head->end, elem));
}

ll_t* ll_push_front(ll_head_t* head, void* elem)
{
  ll_t* tmp;

  if (head == NULL)
    return (NULL);
  if ((tmp = ll_push(head, head->begin, elem)) == NULL)
    return (NULL);
  return (ll_swap(head->begin, tmp));
}

ll_t* ll_erase(ll_t* node)
{
  ll_t* tmp;

  if (node == NULL)
    return (NULL);
  tmp = node->next;

  if (node->prev == NULL)
    node->head->begin = node->next;
  else
    node->prev->next = node->next;

  if (node->next == NULL)
    node->head->end = node->prev;
  else
    node->next->prev = node->prev;
  mem_release(node);
  return (tmp);
}

int ll_empty(const ll_head_t* head)
{
  if (head == NULL)
    return (-1);
  return (head->begin == NULL);
}

void ll_destroy(ll_head_t* head)
{
  while (ll_empty(head) == 0)
    ll_pop(head);
  mem_release(head);
}

int main()
{
  ll_head_t* head = ll_create();

  ll_push_back(head, "1");
  ll_t* a = ll_push_back(head, "2");
  ll_push_back(head, "4");
  ll_push_front(head, "0");
  ll_push(head, a, "3");

  ll_erase(head->begin);
  ll_erase(head->end);
  ll_erase(a);

  ll_push_back(head, "42");

  ll_t* tmp = head->begin;
  while (tmp)
  {
    printf("%s\n", (char*)tmp->elem);
    tmp = tmp->next;
  }
  printf("###\n");
  tmp = head->end;
  while (tmp)
  {
    printf("%s\n", (char*)tmp->elem);
    tmp = tmp->prev;
  }
  ll_destroy(head);

  return (0);
}