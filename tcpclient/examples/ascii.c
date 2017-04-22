#include <stdio.h>
#include "../tclient.h"

#define HOST    "127.0.0.1"
#define PORT    4242
#define TIMEOUT 2.5 //In seconds

uint32_t packet_ascii(const ba_t* array)
{
  void* end_of_packet;

  if ((end_of_packet = ba_find_byte(array, '\n')) == NULL)
    return (0);
  return ((char*)end_of_packet - array->bytes + 1);
}

int main()
{
  pk_t* packet;
  tc_t* tiny_client = tc_create(HOST, PORT, &packet_ascii);

  if (tiny_client == NULL)
    return (1);
  printf("> Client connected to %s:%d\n", HOST, PORT);
  while (1)
  {
    if (tc_update(tiny_client, TIMEOUT) <= 0)
      break;
    while ((packet = tc_poll(tiny_client)))
    {
      printf("> Client received packet\n");
      tc_send(tiny_client, packet->content);
      pk_destroy(packet);
    }
  }
  tc_destroy(tiny_client);
  printf("> Client stopped\n");
  return (0);
}
