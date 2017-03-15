#ifndef SOCKET_H_
#define SOCKET_H_

#include <string.h>
#ifdef _WIN32
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  typedef int socklen_t;
  typedef SOCKET sock_t;
#elif __linux__
  #include <netdb.h>
  #include <unistd.h>
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  typedef int sock_t;
  #define INVALID_SOCKET  -1
  #define SOCKET_ERROR    -1
#endif

typedef struct s_socket
{
  sock_t sock;
  socklen_t addr_size;
  struct sockaddr_storage addr;
} sk_t;

void sk_close(sk_t*);

#endif