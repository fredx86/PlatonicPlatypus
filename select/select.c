#include "select.h"

sl_t* sl_create()
{
  sl_t* slct;

  if ((slct = malloc(sizeof(*slct))) == NULL)
    return (NULL);
  if ((slct->fds = ll_create()) == NULL)
    return (NULL);
  return (slct);
}

int sl_update(sl_t* slct, float seconds)
{
  sock_t nfds;
  struct timeval timeout;

  if (slct == NULL)
    return (-1);
  FD_ZERO(&slct->set[0]);
  FD_ZERO(&slct->set[1]);
  nfds = sl_set_fds(slct);
  time_from_seconds(&timeout, seconds);
  return (select(nfds + 1, &slct->set[0], &slct->set[1], NULL, &timeout));
}

sl_t* sl_add(sl_t* slct, sl_type_t type, sock_t sock)
{
  sl_sock_t* sl_sock;

  if (slct == NULL)
    return (NULL);
  if ((sl_sock = sl_get_sock(slct, sock)) == NULL)
  {
    if ((sl_sock = sl_make_sock(sock)) == NULL)
      return (NULL);
    if (ll_push_back(slct->fds, sl_sock) == NULL)
      return (NULL);
  }
  sl_sock->type |= type;
  return (slct);
}

sl_t* sl_remove(sl_t* slct, sl_type_t type, sock_t sock)
{
  sl_sock_t* sl_sock;

  if (slct == NULL)
    return (NULL);
  if ((sl_sock = sl_get_sock(slct, sock)) == NULL)
    return (slct);
  sl_sock->type &= ~type;
  return (slct);
}

sl_t* sl_remove_sock(sl_t* slct, sock_t sock)
{
  ll_t* node;

  if (slct == NULL)
    return (NULL);
  if ((node = sl_get_node(slct, sock)) == NULL)
    return (slct);
  ll_erase(node);
  return (slct);
}

void sl_destroy(sl_t* slct)
{
  if (slct == NULL)
    return;
  while (ll_empty(slct->fds) == 0)
    free(ll_pop(slct->fds));
  ll_destroy(slct->fds);
  free(slct);
}

ll_t* sl_get_node(const sl_t* slct, sock_t sock)
{
  ll_t* tmp;

  tmp = slct->fds->begin;
  while (tmp)
  {
    if (((sl_sock_t*)tmp->elem)->sock == sock)
      return (tmp);
    tmp = tmp->next;
  }
  return (NULL);
}

sl_sock_t* sl_get_sock(const sl_t* slct, sock_t sock)
{
  ll_t* node;

  if ((node = sl_get_node(slct, sock)) == NULL)
    return (NULL);
  return (node->elem);
}

sl_sock_t* sl_make_sock(sock_t sock)
{
  sl_sock_t* sl_sock;

  if ((sl_sock = malloc(sizeof(*sl_sock))) == NULL)
    return (NULL);
  sl_sock->sock = sock;
  sl_sock->type = 0;
  return (sl_sock);
}

int sl_set_fdset(sl_t* slct, sl_sock_t* sl_sock)
{
  int is_set = 0;

  if (sl_sock->type & SL_READ)
  {
    FD_SET(sl_sock->sock, &slct->set[0]);
    is_set = 1;
  }
  if (sl_sock->type & SL_WRITE)
  {
    FD_SET(sl_sock->sock, &slct->set[1]);
    is_set = 1;
  }
  return (is_set);
}

sock_t sl_set_fds(sl_t* slct)
{
  ll_t* tmp;
  sock_t nfds = 0;
  sl_sock_t* sl_sock;

  tmp = slct->fds->begin;
  while (tmp)
  {
    sl_sock = tmp->elem;
    if (sl_set_fdset(slct, sl_sock) && nfds < sl_sock->sock)
      nfds = sl_sock->sock;
    tmp = tmp->next;
  }
  return (nfds);
}