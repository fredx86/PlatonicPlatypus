#include "socket.h"

int sk_start()
{
#ifdef _WIN32
  WSADATA wsa;
  return (WSAStartup(MAKEWORD(2, 2), &wsa) != 0);
#endif
  return (1);
}

void sk_stop()
{
#ifdef _WIN32
  WSACleanup();
#endif
}

int sk_init(sk_t* sk, const struct addrinfo* hints, const char* host, \
  uint16_t port, sk_init_f init)
{
  char strport[8];
  struct addrinfo* tmp;
  struct addrinfo* result;

  sprintf(strport, "%hu", port);
  if (getaddrinfo(host, strport, hints, &result) != 0)
    return (0);
  tmp = result;
  while (tmp)
  {
    if ((sk->sock = socket(tmp->ai_family, tmp->ai_socktype, \
      tmp->ai_protocol)) != INVALID_SOCKET)
    {
      if (init(sk, tmp))
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

void sk_close(sk_t* socket)
{
#ifdef _WIN32
  closesocket(socket->sock);
#elif __linux__
  shutdown(socket->sock, SHUT_RDWR);
  close(socket->sock);
#endif
}