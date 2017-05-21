#include <assert.h>
#include "../packet.h"

int main()
{
  uint32_t i;
  char data[32];
  pk_t* packet = pk_create(NULL, 0);

  assert(pk_app(NULL, "hello", 5) == NULL);
  assert(pk_app(packet, "hello", 5) != NULL);

  assert(pk_i8(NULL, 42) == NULL);
  assert(pk_i8(packet, 42) != NULL);

  assert(pk_i16(NULL, 123) == NULL);
  assert(pk_i16(packet, 123) != NULL);

  assert(pk_i32(NULL, 456) == NULL);
  assert(pk_i32(packet, 456) != NULL);

  assert(pk_str(NULL, "world") == NULL);
  assert(pk_str(packet, "world") != NULL);

  pk_clear(packet);

  assert(pk_app(packet, "+-", 2) != NULL);
  assert(pk_get(packet, 3, NULL) == NULL);
  assert(pk_get(packet, 1, data) != NULL);
  assert(data[0] == '+');
  assert(pk_get(packet, 1, data) != NULL);
  assert(data[0] == '-');

  pk_clear(packet);

  assert(pk_str(packet, "hello") != NULL);
  assert(pk_i32(packet, 97531) != NULL);
  assert(pk_get_str(packet, (char*)data, 4) == NULL);
  assert(pk_get_str(packet, (char*)data, 32) != NULL);
  assert(strcmp(data, "hello") == 0);
  assert(pk_get_i32(packet, &i) != NULL);
  assert(i == 97531);

  pk_clear(packet);

  assert(pk_app(packet, "i am a test hello_world!\n", 25) != NULL);
  assert(pk_extract(packet, " \n", 32, data) == 1);
  assert(pk_extract(packet, " \n", 32, data) == 2);
  assert(pk_extract(packet, " \n", 32, data) == 1);
  assert(pk_extract(packet, " \n", 32, data) == 4);
  assert(pk_extract(packet, " \n", 32, data) == 12);
  assert(pk_extract(packet, " \n", 32, data) == 0);

  return (0);
}
