#ifndef PP_SOCKET_H_
#define PP_SOCKET_H_

#include <stdlib.h>

struct sock_options
{
  int nonblock:1;
  int ipv4:1;
  int ipv6:1;
  int reuse;
};

struct sock_client
{
  const char* host;
  const char* service;
  struct sock_options options;
};

struct sock_server
{
  const char* service;
  int backlog;
  struct sock_options options;
};

/*
  Socket definition to implement
*/
typedef struct sock sock_t;

/*
  @return       Parameter socket or NULL on error
  @description  Initialize socket
                Implementation defined
*/
sock_t* sock_init(sock_t* socket);

/*
  @description  Clear socket content
                Implementation defined 
*/
void sock_clear(sock_t* socket);

/*
  @return       0 on success or negative value on error
  @description  Prepare socket to talk from client
                Implementation defined
*/
int sock_connect(sock_t* socket, const struct sock_client* client);

/*
  @return       0 on success or negative value on error
  @description  Prepare socket to listen from server
                Implementation defined
*/
int sock_listen(sock_t* socket, const struct sock_server* server);

/*
  @return       0 on success or negative value on error
  @description  Close socket
                Implementation defined
*/
int sock_close(sock_t* socket);

/*
  @return       0 on success or negative value on error
  @description  Send data of size to socket with flags
                sent is filled with the number of bytes sent
                flags CAN be NULL
                Implementation defined
*/
int sock_send(sock_t* socket, size_t* sent, const void* data, size_t size, const void* flags);

/*
  @return       0 on success or negative value on error
  @description  Receive data of maximum size from socket with flags
                recvd is filled with the number of bytes received
                flags CAN be NULL
                Implementation defined
*/
int sock_recv(sock_t* socket, size_t* recvd, void* data, size_t size, const void* flags);

/*
  @return       0 on success or negative value on error
  @description  Accept an accepted socket from socket
                Implementation defined
*/
int sock_accept(const sock_t* socket, sock_t* accepted);

/*
  OS-defined implementations
*/
#ifdef __unix__
  #include "uxsocket.h"
#else
  #error socket.h not defined for target plateform
#endif

#endif
