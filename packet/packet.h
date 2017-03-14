#ifndef PACKET_H_
#define PACKET_H_

#include <stdint.h>
#include "barray.h"
#include <arpa/inet.h>


typedef struct s_packet
{
  ba_t* content;
  char* ptr;
} pk_t;

pk_t* pk_create(const void*, size_t);

void pk_clear(pk_t*);
void pk_ptr_clear(pk_t*);
pk_t* pk_app(pk_t*, const void*, size_t);
pk_t* pk_i8(pk_t*, uint8_t);
pk_t* pk_i16(pk_t*, uint16_t);
pk_t* pk_i32(pk_t*, uint32_t);
pk_t* pk_str(pk_t*, char*);

pk_t* pk_get(pk_t*, size_t, void*);
pk_t* pk_get_i8(pk_t*, uint8_t*);
pk_t* pk_get_i16(pk_t*, uint16_t*);
pk_t* pk_get_i32(pk_t*, uint32_t*);
pk_t* pk_get_str(pk_t*, char*, size_t);

size_t pk_buflen(pk_t*);

pk_t* pk_insert(pk_t*, size_t, const void*, size_t);
pk_t* pk_replace(pk_t*, size_t, const void*, size_t);
pk_t* pk_erase(pk_t*, size_t, size_t);

void pk_destroy(pk_t*);

#endif