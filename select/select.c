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

sl_t* sl_update(sl_t* slct, float seconds)
{
  if (slct == NULL)
    return (NULL);
  //select();
  //FD_ZERO(&slct->set[0]);
  //FD_ZERO(&slct->set[1]);
  return (slct);
}

void sl_set_fdset(sl_t* slct, sl_sock_t* sl_sock) //TODO Move that bitch
{
  if (sl_sock->type & SL_READ)
    FD_SET(sl_sock->sock, &slct->set[0]);
  if (sl_sock->type & SL_WRITE)
    FD_SET(sl_sock->sock, &slct->set[1]);
}

void test(sl_t* slct) //TODO Remove test
{
  ll_t* tmp;

  tmp = slct->fds->begin;
  while (tmp)
  {
    sl_sock_t* sl_sock = tmp->elem; //TODO
//    sl_sock->type
    tmp = tmp->next;
  }
}

sl_t* sl_add(sl_t* slct, sl_type type, sock_t sock)
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
  sl_sock->type = type;
  return (slct);
}

sl_t* sl_remove(sl_t* slct, sl_type type, sock_t sock)
{
  ll_t* node;

  if (slct == NULL)
    return (NULL);
  if ((node = sl_get_node(slct, sock)) == NULL)
    return (slct);
  ll_erase(node);
  return (slct);
}

ll_t* sl_get_node(const sl_t* slct, sock_t sock)
{
  ll_t* tmp;
  sl_sock_t* sl_sock;

  tmp = slct->fds->begin;
  while (tmp)
  {
    if (((sl_sock_t*)tmp->elem)->sock == sock)
      return (tmp);
    tmp = tmp->next;
  }
  return (NULL);
}

sl_sock_t* sl_get_fd(const sl_t* slct, sock_t sock)
{
  ll_t* node;

  if ((node = sl_get_node(slct, sock)) == NULL)
    return (NULL);
  return (node->elem);
}

sl_sock_t* sl_make_fd(sock_t sock)
{
  sl_sock_t* sl_sock;

  if ((sl_sock = malloc(sizeof(*sl_sock))) == NULL)
    return (NULL);
  sl_sock->sock = sock;
  return (sl_sock);
}