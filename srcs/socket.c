#include "pp/socket.h"

socket_t* skcrt(socket_t* sock, const char* hostname, unsigned short port, struct addrinfo* hints, skinitfunc func)
{
  char strport[8];

  sprintf(strport, "%hu", port);
  sock->sock = INVALID_SOCKET;
  if (!_skaddrinfo(sock, hostname, strport, hints, func))
    return (NULL);
  return (sock);
}

ssize_t skrecv(socket_t* sock, barray_t* barray, size_t size)
{
  ssize_t r = recvfrom(sock->sock, barray->bytes, size, 0, NULL, NULL);
  barray->size = r < 0 ? 0 : r;
  return (r);
}

ssize_t sksend(socket_t* sock, const barray_t* barray)
{
  return (sendto(sock->sock, barray->bytes, barray->size, 0,
      sock->addr, sock->addr_size));
}

void skdel(socket_t* sock)
{
#ifdef _WIN32
  closesocket(sock->sock);
#elif __linux__
  shutdown(sock->sock, SHUT_RDWR);
  close(sock->sock);
#endif
}

int _skaddrinfo(socket_t* sock, const char* node, const char* service, struct addrinfo* hints, skinitfunc func)
{
  struct addrinfo* result;
  struct addrinfo* tmp;

  if (getaddrinfo(node, service, hints, &result) != 0)
    return (0);
  tmp = result;
  while (tmp)
  {
    if ((sock->sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol)) != INVALID_SOCKET)
    {
      if (func(sock, tmp))
      {
        sock->addr = tmp->ai_addr;
        sock->addr_size = tmp->ai_addrlen;
        break;
      }
      skdel(sock);
    }
    tmp = tmp->ai_next;
  }
  freeaddrinfo(result);
  return (tmp != NULL);
}