#ifndef PACKET_H_
#define PACKET_H_

#include <stdint.h>
#include "barray.h"

#ifdef _WIN32
  #include <Winsock2.h>
#else
  #include <arpa/inet.h>
#endif

typedef struct s_packet
{
  ba_t* content;
  char* ptr;
} pk_t;

pk_t* pk_create(const void*, size_t);

void pk_clear(pk_t*);
void pk_ptr_reset(pk_t*);
int pk_ptr_update(pk_t*);
pk_t* pk_app(pk_t*, const void*, size_t);
pk_t* pk_i8(pk_t*, uint8_t);
pk_t* pk_i16(pk_t*, uint16_t);
pk_t* pk_i32(pk_t*, uint32_t);
pk_t* pk_str(pk_t*, char*);

pk_t* pk_get(pk_t*, size_t, void*);

/*
  Extract into 'buf' of size 'size' until one of 'bytes'
  Return the number of bytes extracted
  Return -1 on failure
*/
int pk_extract(pk_t*, const char* bytes, size_t size, void* buf);

pk_t* pk_get_i8(pk_t*, uint8_t*);
pk_t* pk_get_i16(pk_t*, uint16_t*);
pk_t* pk_get_i32(pk_t*, uint32_t*);
pk_t* pk_get_str(pk_t*, char*, size_t);

size_t pk_size(const pk_t*);
size_t pk_buflen(pk_t*);

pk_t* pk_insert(pk_t*, size_t, const void*, size_t);
pk_t* pk_replace(pk_t*, size_t, const void*, size_t);
pk_t* pk_erase(pk_t*, size_t, size_t);

void pk_destroy(pk_t*);

#endif