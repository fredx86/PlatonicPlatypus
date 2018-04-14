#include <assert.h>

#include "pp/socket.h"

int main()
{
  size_t n;
  char buf[32];
  sock_t socket;
  struct sock_client client = {
    .host       = "www.google.com",
    .service    = "http",
    .options    = {
      .nonblock = 0,
      .ipv4     = 1,
      .ipv6     = 1,
      .reuse    = 0
    }
  };
  assert(sock_init(&socket));
  assert(sock_connect(&socket, &client) >= 0);
  assert(sock_send(&socket, &n, "GET / HTTP/1.0\r\n\r\n", 18, NULL) >= 0);
  assert(n == 18);
  assert(sock_recv(&socket, &n, buf, 8, NULL) >= 0);
  assert(n > 0 && n <= 8);
  assert(strncmp(buf, "HTTP/1.0", 8) == 0);
  sock_clear(&socket);
  return (0);
}
