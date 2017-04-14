#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include "select.h"
#include "packet.h"
#include "socket.h"

typedef uint32_t (*tc_packet_f)(const ba_t*);

typedef struct s_tcp_client
{
  sk_t socket;
  sl_t* select;
  ba_t* inbound;
  ba_t* outbound;
  ll_head_t* packets; /* List of pk_t* */
  tc_packet_f on_rcvd;
} tc_t;

tc_t* tc_create(const char* host, uint16_t port, tc_packet_f on_rcvd);

tc_t* tc_update(tc_t*, float seconds);
pk_t* tc_poll(tc_t*);

tc_t* tc_send(tc_t*, const ba_t*);

void ts_destroy(tc_t*);

int tc_connect(sk_t*, struct addrinfo*);

#endif