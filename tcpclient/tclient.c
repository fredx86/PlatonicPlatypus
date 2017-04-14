#include "tclient.h"

tc_t* tc_create(const char* host, uint16_t port, tc_packet_f on_rcvd)
{
  tc_t* tc;
  struct addrinfo hints = { 0 };

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if (on_rcvd == NULL || (tc = malloc(sizeof(*tc))) == NULL)
    return (NULL);
  tc->on_rcvd = on_rcvd;
  if (!sk_init(&tc->socket, &hints, host, port, tc_connect))
    return (NULL);
  if ((tc->select = sl_create()) == NULL)
    return (NULL);
  if ((tc->inbound = ba_create(NULL, 0)) == NULL)
    return (NULL);
  if ((tc->outbound = ba_create(NULL, 0)) == NULL)
    return (NULL);
  if ((tc->packets = ll_create()) == NULL)
    return (NULL);
  if (sl_add(tc->select, SL_READ, tc->socket.sock) == NULL)
    return (NULL);
  return (tc);
}

tc_t* tc_update(tc_t* client, float seconds)
{
  int update;

  if (client == NULL)
    return (NULL);
  if ((update = sl_update(client->select, seconds)) == -1)
    return (NULL);
  if (update == 0) //On timeout
    return (client);
  if (FD_ISSET(client->socket.sock, &client->select->readfs))
  {
    //TODO Read
  }
  if (FD_ISSET(client->socket.sock, &client->select->writefs))
  {
    //TODO Write
  }
  return (client);
}

pk_t* tc_poll(tc_t* client)
{
  if (client == NULL)
    return (NULL);
  //TODO
  return (NULL);
}

tc_t* tc_send(tc_t* client, const ba_t* array)
{
  if (client == NULL)
    return (NULL);
  if (array == NULL)
    return (client);
  if (sl_add(client->select, SL_WRITE, client->socket.sock) == NULL)
    return (NULL);
  if (ba_app(client->outbound, array->bytes, array->size) == NULL)
    return (NULL);
  return (client);
}

void tc_destroy(tc_t* client)
{
  if (client == NULL)
    return;
  //TODO
}

tc_t* tc_read(tc_t* client)
{
  pk_t* packet;
  char buf[1024];
  ssize_t received;
  uint32_t pk_size = 1;

  if ((received = recv(client->socket.sock, buf, 1024, 0)) > 0)
  {
    if (ba_app(client->inbound, buf, received) == NULL)
      return (NULL);
    while ((pk_size = client->on_rcvd(client->inbound)) > 0)
    {
      if ((packet = pk_create(client->inbound->bytes, pk_size)) == NULL)
        return (NULL);
      if (ll_push_back(client->packets, packet) == NULL)
        return (NULL);
      ba_erase(client->inbound, 0, pk_size);
    }
  }
  else
  {
    //TODO disconnected
  }
  return (client);
}

tc_t* ts_write(tc_t* client)
{
  ssize_t sent;

  if ((sent = send(client->socket.sock, client->outbound->bytes, \
    client->outbound->size, 0)) > 0)
  {
    if ((size_t)sent == client->outbound->size) //If all data were send
      sl_remove(client->select, SL_WRITE, client->socket.sock);
    ba_erase(client->outbound, 0, sent);
  }
  else
  {
    //TODO disconnected
  }
  return (client);
}

int tc_connect(sk_t* sock, struct addrinfo* addrinfo)
{
  if (connect(sock->sock, &addrinfo->ai_addr, \
    addrinfo->ai_addrlen) == SOCKET_ERROR)
    return (0);
  return (1);
}