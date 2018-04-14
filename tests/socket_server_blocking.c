#include <assert.h>

#include "pp/socket.h"

int main()
{
  size_t n;
  char buf[32];
  sock_t socket;
  struct sock_server server = {
    .service    = "8173",
    .backlog    = 1024,
    .options    = {
      .nonblock = 0,
      .ipv4     = 1,
      .ipv6     = 1,
      .reuse    = 1
    }
  };
  assert(sock_init(&socket));
  assert(sock_listen(&socket, &server) >= 0);
  sock_clear(&socket);
  return (0);
}
