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
  ts_event_t* event;
  ts_t* tiny_server = ts_create(AF_INET, 4242, &packet_ascii);

  while (ts_update(tiny_server, 2.5))
  {
    while ((event = ts_poll(tiny_server)))
    {
      switch (event->type)
      {
        case TS_CONNECT:
          printf("Connect %d\n", event->sock_id);
          break;
        case TS_DISCONNECT:
          printf("Disconnect %d\n", event->sock_id);
          break;
        case TS_PACKET:
          printf("Packet %d\n", event->sock_id);
          break;
      }
      ts_event_destroy(event);
    }
  }
  return (0);
}
