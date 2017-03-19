#include "tserver.h"

ts_t* ts_create(int ai_family, uint16_t port, ts_packet_f on_rcvd)
{
  ts_t* ts;

  if (on_rcvd == NULL || (ts = malloc(sizeof(*ts))) == NULL)
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
  ll_t* tmp;
  int update;
  ts_client_t* client;

  if (server == NULL)
    return (NULL);
  if ((update = sl_update(server->select, seconds)) == -1)
    return (NULL);
  if (update == 0) //On timeout
    return (server);
  if (FD_ISSET(server->socket.sock, &server->select->readfs))
  {
    if (ts_accept(server) == NULL)
      return (NULL);
  }
  tmp = server->clients->begin;
  while (tmp)
  {
    client = tmp->elem;
    tmp = tmp->next;
    if (FD_ISSET(client->socket.sock, &server->select->readfs))
    {
      if (ts_read(server, client) == NULL)
        return (NULL);
    }
    if (FD_ISSET(client->socket.sock, &server->select->writefs))
    {
      if (ts_write(server, client) == NULL)
        return (NULL);
    }
  }
  return (server);
}

ts_event_t* ts_poll(ts_t* server)
{
  if (server == NULL)
    return (NULL);
  return (ll_pop(server->events));
}

void ts_remove(ts_t* server, sock_t sock_id, char send_event)
{
  ll_t* node;
  ts_client_t* client;

  if (server == NULL)
    return;
  if ((node = ts_get_node(server, sock_id)) == NULL)
    return;
  client = node->elem;
  sl_remove_sock(server->select, sock_id);
  sk_close(&client->socket);
  pk_destroy(client->inbound);
  pk_destroy(client->outbound);
  ll_erase(node);
  if (send_event)
  {
    ts_make_event(server, TS_DISCONNECT, sock_id);
  }
}

void ts_event_destroy(ts_event_t* event)
{
  if (event == NULL)
    return;
  pk_destroy(event->packet);
}

void ts_destroy(ts_t* server)
{
  if (server == NULL)
    return;
  //TODO Remove clients
  free(server);
}

ll_t* ts_get_node(ts_t* server, sock_t sock_id)
{
  ll_t* tmp;

  if (server == NULL)
    return (NULL);
  tmp = server->clients->begin;
  while (tmp)
  {
    if (((ts_client_t*)tmp->elem)->socket.sock == sock_id)
      return (tmp);
    tmp = tmp->next;
  }
  return (NULL);
}

ts_client_t* ts_get_client(ts_t* server, sock_t sock_id)
{
  ll_t* tmp;

  if ((tmp = ts_get_node(server, sock_id)) == NULL)
    return (NULL);
  return (tmp->elem);
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

ts_event_t* ts_make_event(ts_t* server, enum e_ts_event e, sock_t sock_id)
{
  ts_event_t* event;

  if ((event = malloc(sizeof(*event))) == NULL)
    return (NULL);
  event->type = e;
  event->sock_id = sock_id;
  event->packet = NULL;
  if (ll_push_front(server->events, event) == NULL)
    return (NULL);
  return (event);
}

ts_client_t* ts_accept(ts_t* server)
{
  sk_t socket;
  ts_client_t* client;

  socket.addr_size = sizeof(socket.addr);
  socket.sock = accept(server->socket.sock, (struct sockaddr*)&socket.addr, &socket.addr_size);
  if (socket.sock == INVALID_SOCKET)
    return (NULL);
  if ((client = ts_make_client(&socket)) == NULL)
    return (NULL);
  if (ll_push_back(server->clients, client) == NULL)
    return (NULL);
  if (sl_add(server->select, SL_READ, socket.sock) == NULL)
    return (NULL);
  if (ts_make_event(server, TS_CONNECT, socket.sock) == NULL)
    return (NULL);
  return (client);
}

ts_client_t* ts_read(ts_t* server, ts_client_t* client)
{
  char buf[1024];
  ssize_t received;
  ts_event_t* event;
  uint32_t pk_size = 1;

  if ((received = recv(client->socket.sock, buf, 1024, 0)) > 0)
  {
    if (pk_app(client->inbound, buf, received) == NULL)
      return (NULL);
    while ((pk_size = server->on_rcvd(client->inbound->content, client->status)) > 0)
    {
      if ((event = ts_make_event(server, TS_PACKET, client->socket.sock)) == NULL)
        return (NULL);
      if ((event->packet = pk_create(client->inbound->content->bytes, pk_size)) == NULL)
        return (NULL);
      pk_erase(client->inbound, 0, pk_size);
    }
  }
  else
  {
    ts_remove(server, client->socket.sock, 1);
  }
  return (client);
}

ts_client_t* ts_write(ts_t* server, ts_client_t* client)
{
  ssize_t sent;

  if ((sent = send(client->socket.sock, client->outbound->content->bytes, \
    client->outbound->content->size, 0)) > 0)
  {
    if ((size_t)sent == client->outbound->content->size) //If all data were send
      sl_remove(server->select, SL_WRITE, client->socket.sock);
    pk_erase(client->outbound, 0, sent);
  }
  else
  {
    ts_remove(server, client->socket.sock, 1);
  }
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