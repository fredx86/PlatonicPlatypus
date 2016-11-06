#ifndef PP_SOCKET_H_
#define PP_SOCKET_H_

#include <stdio.h>
#include "barray.h"

#ifdef _WIN32
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  typedef int socklen_t;
  typedef SOCKET sock_t;
#elif __linux__
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <netdb.h>
  typedef int sock_t;
  #define INVALID_SOCKET  -1
  #define SOCKET_ERROR    -1
#endif

typedef struct s_socket
{
  sock_t sock;
  socklen_t addr_size;
  struct sockaddr *addr;
} socket_t;

typedef int (*skinitfunc)(socket_t*, struct addrinfo*);

socket_t* skcrt(socket_t*, const char*, unsigned short, struct addrinfo*, skinitfunc);

ssize_t skrecv(socket_t*, barray_t*, size_t);
ssize_t sksend(socket_t*, const barray_t*);

void skdel(socket_t*);

//SOCKET UTILS

int _skaddrinfo(socket_t*, const char*, const char*, struct addrinfo*, skinitfunc);

#endif