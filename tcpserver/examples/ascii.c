#include <signal.h>
#include "../tserver.h"

char g_run = 1;

void server_stop(int signal)
{
  (void)signal;
  g_run = 0;
}

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

  signal(SIGINT, server_stop);
  if (tiny_server == NULL)
    return (1);
  printf("> Server running on port 4242\n");
  while (g_run)
  {
    if (ts_update(tiny_server, 2.5) == NULL)
      break;
    while ((event = ts_poll(tiny_server)))
    {
      switch (event->type)
      {
        case TS_CONNECT:
          printf("> %d connected\n", event->sock_id);
          break;
        case TS_DISCONNECT:
          printf("> %d disconnected\n", event->sock_id);
          break;
        case TS_PACKET:
          printf("> %d sent packet\n", event->sock_id);
          ts_send(tiny_server, event->sock_id, event->packet->content);
          break;
      }
      ts_event_destroy(event);
    }
  }
  ts_destroy(tiny_server);
  printf("> Server stopped\n");
  return (0);
}
