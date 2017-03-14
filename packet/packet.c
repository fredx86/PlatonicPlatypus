#include "packet.h"

pk_t* pk_create(const void* bytes, size_t size)
{
  pk_t* packet;

  if ((packet = malloc(sizeof(*packet))) == NULL)
    return (NULL);
  if ((packet->content = ba_create(bytes, size)) == NULL)
    return (NULL);
  pk_ptr_reset(packet);
  return (packet);
}

void pk_clear(pk_t* packet)
{
  if (packet == NULL)
    return;
  ba_clear(packet->content);
  pk_ptr_reset(packet);
}

void pk_ptr_reset(pk_t* packet)
{
  if (packet != NULL)
    packet->ptr = packet->content->bytes;
}

pk_t* pk_app(pk_t* packet, const void* bytes, size_t size)
{
  if (packet == NULL)
    return (NULL);
  return (ba_app(packet->content, bytes, size) ? packet : NULL);
}

pk_t* pk_i8(pk_t* packet, uint8_t n)
{
  return (pk_app(packet, &n, sizeof(n)));
}

pk_t* pk_i16(pk_t* packet, uint16_t n)
{
  uint16_t data = htons(n);
  return (pk_app(packet, &data, sizeof(data)));
}

pk_t* pk_i32(pk_t* packet, uint32_t n)
{
  uint32_t data = htonl(n);
  return (pk_app(packet, &data, sizeof(data)));
}

pk_t* pk_str(pk_t* packet, char* str)
{
  size_t len = strlen(str);
  return (pk_app(packet, str, len + 1));
}

pk_t* pk_get(pk_t* packet, size_t size, void* bytes)
{
  if (packet == NULL)
    return (NULL);
  if (pk_buflen(packet) < size)
    return (NULL);
  memcpy(bytes, packet->ptr, size);
  packet->ptr += size;
  return (packet);
}

pk_t* pk_get_i8(pk_t* packet, uint8_t* n)
{
  return (pk_get(packet, sizeof(*n), n));
}

pk_t* pk_get_i16(pk_t* packet, uint16_t* n)
{
  if (pk_get(packet, sizeof(*n), n) == NULL)
    return (NULL);
  *n = ntohs(*n);
  return (packet);
}

pk_t* pk_get_i32(pk_t* packet, uint32_t* n)
{
  if (pk_get(packet, sizeof(*n), n) == NULL)
    return (NULL);
  *n = ntohl(*n);
  return (packet);
}

pk_t* pk_get_str(pk_t* packet, char* str, size_t size)
{
  size_t len;
  char* end_of_str;

  if (packet == NULL)
    return (NULL);
  if ((end_of_str = find_byte(packet->ptr, pk_buflen(packet), 0)) == NULL)
    return (NULL);
  len = end_of_str - packet->ptr + 1;
  if (len > size)
    return (NULL);
  memcpy(str, packet->ptr, len);
  packet->ptr += len;
  return (packet);
}

size_t pk_buflen(pk_t* packet)
{
  if (packet == NULL)
    return (0);
  if (packet->ptr == NULL)
  {
    pk_ptr_reset(packet);
    if (packet->ptr == NULL)
      return (0);
  }
  return (packet->content->size - (packet->ptr - packet->content->bytes));
}

pk_t* pk_insert(pk_t* packet, size_t pos, const void* bytes, size_t size)
{
  if (packet == NULL)
    return (NULL);
  return (ba_insert(packet->content, pos, bytes, size) ? packet : NULL);
}

pk_t* pk_replace(pk_t* packet, size_t pos, const void* bytes, size_t size)
{
  if (packet == NULL)
    return (NULL);
  return (ba_replace(packet->content, pos, bytes, size) ? packet : NULL);
}

pk_t* pk_erase(pk_t* packet, size_t pos, size_t size)
{
  if (packet == NULL)
    return (NULL);
  return (ba_erase(packet->content, pos, size) ? packet : NULL);
}

void pk_destroy(pk_t* packet)
{
  if (packet == NULL)
    return;
  ba_destroy(packet->content);
  free(packet);
}