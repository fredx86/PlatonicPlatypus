#ifndef UNIX_SOCKET_H_
#define UNIX_SOCKET_H_

#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

/*
  Implementation of the sock_t structure
*/
typedef struct sock
{
  int sockfd;
} sock_t;

/*
  @return       0 on success or a negative value on error
  @description  Setup sock from host and service using getaddrinfo()
                Setup sock's options, using socket_pre_options() and socket_post_options()
*/
int socket_from_host(sock_t* sock,
  const char* host,
  const char* service,
  const struct sock_options* options,
  int (*functor)(int, const struct sockaddr*, socklen_t));

/*
  @return       Socket family: AF_UNSPEC, AF_INET or AF_INET6
  @description  Choose socket family from options
*/
int socket_family(const struct sock_options* options);

/*
  @return       SOCK_STREAM
*/
int socket_type(const struct sock_options* options);

/*
  @return       0 on success or a negative value on error
  @description  Apply options to sock after the socket is created but before any connect() or bind()
*/
int socket_pre_options(sock_t* sock, const struct sock_options* options);

/*
  @return       0 on success or a negative value on error
  @description  Apply options to sock after the connect() or bind()
*/
int socket_post_options(sock_t* sock, const struct sock_options* options);

#endif
