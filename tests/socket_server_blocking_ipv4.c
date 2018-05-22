#include <assert.h>

#include "pp/socket.h"

int main()
{
  size_t n;
  char buf[32];
  sock_t socket;
  sock_t sockclient;
  struct sock_server server = {
    .service    = "1235",
    .backlog    = 1024,
    .options    = {
      .nonblock = 0,
      .ipv4     = 1,
      .ipv6     = 0,
      .reuse    = 1
    }
  };
  assert(sock_init(&socket));
  assert(sock_listen(&socket, &server));
  assert(sock_accept(&socket, &sockclient));
  assert(sock_recv(&sockclient, &n, buf, 5, NULL));
  assert(n == 5);
  assert(strncmp(buf, "HELLO", 5) == 0);
  sock_close(&sockclient);
  sock_clear(&socket);
  return (0);
}
