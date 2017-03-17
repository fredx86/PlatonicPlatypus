#include "../tserver.h"

uint32_t packet_ascii(const ba_t* array, char status)
{
  void* end_of_packet;

  (void)status;
  if ((end_of_packet = ba_find_byte(array, '\n')) == NULL)
    return (0);
  return ((char*)end_of_packet - array->bytes + 1);
}

int main()
{
  ts_t* tiny_server = ts_create(AF_INET, 4242, &packet_ascii);

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
