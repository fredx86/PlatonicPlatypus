#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <stdio.h>
#include "select.h"
#include "packet.h"
#include "socket.h"

typedef struct s_tcp_server ts_t;
typedef uint32_t (*rcvd_packet_f)(ts_t*, void* client, pk_t*);
/*
typedef void (*on_connect_f)(ts_t*, sock_t);
typedef void (*on_disconnect_f)(ts_t*, sock_t);
*/

typedef struct s_tcp_server_client
{
  sk_t socket;
  pk_t* inbound;
  pk_t* outbound;
  void* client;
} ts_client_t;

typedef struct s_tcp_server
{
  sl_t* select;
  ll_head_t* clients; /* List of ts_client_t */
  sk_t server;
  //Maybe in a struct ?
  rcvd_packet_f on_rcvd;
} ts_t;

ts_t* ts_create(int ai_family, uint16_t port);

//ts_t* ts_update(ts_t*, float seconds);

void ts_destroy(ts_t*);

int ts_init_socket(sk_t*, int ai_family, uint16_t port);
int ts_bind_socket(sk_t*, struct addrinfo*);

#endif