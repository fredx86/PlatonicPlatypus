#include "tserver.h"

ts_t* ts_create(int ai_family, uint16_t port, ts_packet_f on_rcvd)
{
  ts_t* ts;

  if ((ts = malloc(sizeof(*ts))) == NULL)
    return (NULL);
  ts->on_rcvd = on_rcvd;
  if ((ts->clients = ll_create()) == NULL)
    return (NULL);
  if ((ts->events = ll_create()) == NULL)
    return (NULL);
  if ((ts->select = sl_create()) == NULL)
    return (NULL);
  if (!ts_init_socket(&ts->socket, ai_family, port))
    return (NULL);
  if (sl_add(ts->select, SL_READ, ts->socket.sock) == NULL)
    return (NULL);
  return (ts);
}

ts_t* ts_update(ts_t* server, float seconds)
{
  int update;
  ll_t* tmp;
  sl_sock_t* s;

  if (server == NULL)
    return (NULL);
  if ((update = sl_update(server->select, seconds)) == -1)
    return (NULL);
  if (update == 0) //On timeout
    return (server);
  tmp = server->select->fds->begin;
  while (tmp)
  {
    s = tmp->elem;
    if (FD_ISSET(s->sock, &server->select->readfs))
    {
/*      
        if (s->sock == server->socket.sock)
        ts_accept(server);
        ts_read(server, s->sock);
*/
    }
    if (FD_ISSET(s->sock, &server->select->writefs))
    {
      //TODO
    }
    tmp = tmp->next;
  }
  return (server);
}

ts_event_t* ts_poll(ts_t* server)
{
  if (server == NULL)
    return (NULL);
  if (ll_empty(server->events) != 0)
    return (NULL);
  return (ll_pop(server->events));
}

void ts_destroy(ts_t* server)
{
  if (server == NULL)
    return;
  //TODO Remove clients
  free(server);
}

ts_client_t* ts_get_client(ts_t* server, sock_t sock_id)
{
  ll_t* tmp;

  tmp = server->clients->begin;
  while (tmp)
  {
    if (((ts_client_t*)tmp->elem)->socket.sock == sock_id)
      return (tmp->elem);
    tmp = tmp->next;
  }
  return (NULL);
}

ts_client_t* ts_make_client(sk_t* socket)
{
  ts_client_t* client;

  if ((client = malloc(sizeof(*client))) == NULL)
    return (NULL);
  memcpy(&client->socket, socket, sizeof(*socket));
  if ((client->inbound = pk_create(NULL, 0)) == NULL)
    return (NULL);
  if ((client->outbound = pk_create(NULL, 0)) == NULL)
    return (NULL);
  client->status = 0;
  return (client);
}

//TODO Move away
ts_event_t* ts_add_event(ts_t* server, enum e_ts_event e, ts_client_t* client)
{
  ts_event_t* event;

  if ((event = malloc(sizeof(*event))) == NULL)
    return (NULL);
  event->type = e;
  event->client = client;
  event->packet = NULL;
  if (ll_push_front(server->events, event) == NULL)
    return (NULL);
  return (event);
}

//TODO Move away
ts_client_t* ts_accept(ts_t* server)
{
  sk_t socket;
  ts_client_t* client;

  socket.sock = accept(server->socket.sock, (struct sockaddr*)&socket.addr, &socket.addr_size);
  if (socket.sock == INVALID_SOCKET)
    return (NULL);
  if ((client = ts_make_client(&socket)) == NULL)
    return (NULL);
  if (ll_push_back(server->clients, client) == NULL)
    return (NULL);
  if (ts_add_event(server, TS_CONNECT, client) == NULL)
    return (NULL);
  return (client);
}

int ts_init_socket(sk_t* sk, int ai_family, uint16_t port)
{
  char strport[8];
  struct addrinfo* tmp;
  struct addrinfo* result;
  struct addrinfo hints = { 0 };

  hints.ai_family = ai_family;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_STREAM;
  sprintf(strport, "%hu", port);
  if (getaddrinfo(NULL, strport, &hints, &result) != 0)
    return (0);
  tmp = result;
  while (tmp)
  {
    if ((sk->sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol)) != INVALID_SOCKET)
    {
      if (ts_bind_socket(sk, tmp))
      {
        memcpy(&sk->addr, tmp->ai_addr, tmp->ai_addrlen);
        sk->addr_size = tmp->ai_addrlen;
        break;
      }
      sk_close(sk);
    }
    tmp = tmp->ai_next;
  }
  freeaddrinfo(result);
  return (tmp != NULL);
}

int ts_bind_socket(sk_t* socket, struct addrinfo* addrinfo)
{
  char reuse = 1;

  if (bind(socket->sock, addrinfo->ai_addr, addrinfo->ai_addrlen) == SOCKET_ERROR)
    return (0);
  if (listen(socket->sock, SOMAXCONN) == SOCKET_ERROR)
    return (0);
  setsockopt(socket->sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  return (1);
}