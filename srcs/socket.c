#include "pp/socket.h"

static char _socket_enable = 0;

socket_t* skcrt(socket_t* sock, int type)
{
#ifdef _WIN32
  if (!_socket_enable)
  {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
      return (0);
  }
#endif
  _socket_enable = 1;
  sock->sock = INVALID_SOCKET;
  sock->type = type;
  return (sock);
}

int skconnect(socket_t* sock, const char* hostname, unsigned short port)
{
  char strport[8];
  struct addrinfo hints = { 0 };

  sprintf(strport, "%hu", port);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = sock->type;
  return (_skaddrinfo(sock, hostname, strport, &hints, &_skconnect));
}

ssize_t skrecv(socket_t* sock, void* buff, size_t size)
{
  return (recvfrom(sock->sock, buff, size, 0, NULL, NULL));
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

void skbrk()
{
#ifdef _WIN32
  WSACleanup();
#endif
}

int _skconnect(socket_t* sock, struct addrinfo* addrinfo)
{
  return (connect(sock->sock, addrinfo->ai_addr, addrinfo->ai_addrlen) == 0);
}

int _skaddrinfo(socket_t* sock, const char* node, const char* service, struct addrinfo* hints, _skaddrinfofunc func)
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