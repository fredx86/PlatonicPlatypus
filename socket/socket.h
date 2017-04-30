#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <stdint.h>
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

typedef int (*sk_init_f)(sk_t*, struct addrinfo*);

/* Enable sockets functionalities. Return 0 on failure */
int sk_start();
/* Disable sockets functionnalities */
void sk_stop();

/* Return 0 on error, 1 on success */
int sk_init(sk_t*, const struct addrinfo*, const char*, uint16_t, sk_init_f);

void sk_close(sk_t*);

#endif