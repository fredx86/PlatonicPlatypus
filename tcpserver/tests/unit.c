#include "../tserver.h"

int main()
{
  ts_t* tiny_server = ts_create(AF_INET, 4242);

  printf("%d\n", tiny_server->server.sock);
  return (0);
}
