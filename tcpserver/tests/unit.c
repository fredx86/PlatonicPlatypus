#include "../tserver.h"

int main()
{
  ts_t* tiny_server = ts_create(AF_INET, 4242);

  //ts_update(tiny_server);
  /*while (event = ts_poll(tiny_server))
  {
    switch (event.type)
    {
      case TS_CONNECT:
        break;
      case TS_DISCONNECT:
        break;
      case TS_PACKET:
        break;
    }
  }*/

  return (0);
}
