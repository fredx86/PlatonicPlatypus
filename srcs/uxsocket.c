#include "pp/socket.h"

sock_t* sock_init(sock_t* sock)
{
  return sock;
}

void sock_clear(sock_t* sock)
{
  sock_close(sock);
}

sock_t* sock_connect(sock_t* sock, const struct sock_client* client)
{
  return (socket_from_host(sock,
    client->host,
    client->service,
    &client->options,
    &connect));
}

sock_t* sock_listen(sock_t* sock, const struct sock_server* server)
{
  if (!socket_from_host(sock, NULL, server->service, &server->options, &bind))
  {
    return NULL;
  }
  if (listen(sock->sockfd, server->backlog) < 0)
  {
    return NULL;
  }
  return sock;
}

int sock_close(sock_t* sock)
{
  shutdown(sock->sockfd, SHUT_RDWR);
  return close(sock->sockfd);
}

sock_t* sock_send(sock_t* sock, size_t* sent, const void* data, size_t size, const void* flags)
{
  ssize_t tmp = send(sock->sockfd, data, size, flags ? *(int*)flags : 0);
  if (tmp < 0)
  {
    return NULL;
  }
  *sent = tmp;
  return sock;
}

sock_t* sock_recv(sock_t* sock, size_t* recvd, void* data, size_t size, const void* flags)
{
  ssize_t tmp = recv(sock->sockfd, data, size, flags ? *(int*)flags : 0);
  if (tmp < 0)
  {
    return NULL;
  }
  *recvd = tmp;
  return sock;
}

sock_t* sock_accept(const sock_t* sock, sock_t* accepted)
{
  if (sock_init(accepted) == NULL)
  {
    return NULL;
  }
  accepted->sockfd = accept(sock->sockfd, NULL, NULL);
  return accepted;
}

sock_t* socket_from_host(sock_t* sock,
  const char* host,
  const char* service,
  const struct sock_options* options,
  int (*functor)(int, const struct sockaddr*, socklen_t))
{
  struct addrinfo hints;
  struct addrinfo *result;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = socket_family(options);
  hints.ai_socktype = socket_type(options);
  if (getaddrinfo(host, service, &hints, &result) != 0)
  {
    return NULL;
  }
  for (struct addrinfo* it = result; it; it = it->ai_next)
  {
    sock->sockfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
    if (sock->sockfd >= 0 && socket_pre_options(sock, options) >= 0 &&
      functor(sock->sockfd, it->ai_addr, it->ai_addrlen) >= 0)
    {
      break;
    }
    close(sock->sockfd);
    sock->sockfd = -1;
  }
  freeaddrinfo(result);
  if (sock->sockfd >= 0 && socket_post_options(sock, options) < 0)
  {
    return NULL;
  }
  return sock;
}

inline int socket_family(const struct sock_options* options)
{
  if (options->ipv4 && options->ipv6)
    return AF_UNSPEC;
  else if (options->ipv4)
    return AF_INET;
  else if (options->ipv6)
    return AF_INET6;
  return AF_UNSPEC;
}

inline int socket_type(const struct sock_options* options)
{
  (void)options;
  return SOCK_STREAM;
}

int socket_pre_options(sock_t* sock, const struct sock_options* options)
{
  return setsockopt(sock->sockfd, SOL_SOCKET, SO_REUSEADDR,
    &options->reuse, sizeof(options->reuse));
}

int socket_post_options(sock_t* sock, const struct sock_options* options)
{
  if (options->nonblock && fcntl(sock->sockfd, F_SETFL, O_NONBLOCK) < 0)
  {
    return -1;
  }
  return 0;
}
