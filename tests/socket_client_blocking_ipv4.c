#include <assert.h>

#include "pp/socket.h"

int main()
{
  size_t n;
  char buf[32];
  sock_t socket;
  //Local server that shouts "HELLO\n"
  struct sock_client client = {
    .host       = "localhost",
    .service    = "1234",
    .options    = {
      .nonblock = 0,
      .ipv4     = 1,
      .ipv6     = 0,
      .reuse    = 0
    }
  };
  assert(sock_init(&socket));
  assert(sock_connect(&socket, &client));
  assert(sock_send(&socket, &n, "HELLO\n", 6, NULL));
  assert(n == 6);
  assert(sock_recv(&socket, &n, buf, 5, NULL));
  assert(n == 5);
  assert(strncmp(buf, "HELLO", 5) == 0);
  sock_clear(&socket);
  return (0);
}
