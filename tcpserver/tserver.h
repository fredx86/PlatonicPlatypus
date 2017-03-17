#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <stdio.h>
#include "select.h"
#include "packet.h"
#include "socket.h"
#include "tserver_event.h"

typedef struct s_tcp_server ts_t;
typedef uint32_t (*ts_packet_f)(ts_t*, pk_t*, char);

typedef struct s_ts_client
{
  sk_t socket;
  pk_t* inbound;
  pk_t* outbound;
  char status;
} ts_client_t;

typedef struct s_tcp_server
{
  sl_t* select;
  ll_head_t* clients; /* List of ts_client_t */
  sk_t socket;
  ts_packet_f on_rcvd;
  ll_head_t* events; /* List of ts_event_t */
} ts_t;

ts_t* ts_create(int ai_family, uint16_t port, ts_packet_f on_rcvd);

//ts_t* ts_update(ts_t*, float seconds);
ts_event_t* ts_poll(ts_t*);

//ts_t* ts_send(ts_t*, sock_t, pk_t*);
//ts_t* ts_send_all(ts_t*, pk_t*);
void ts_remove(ts_t*, sock_t);

//void ts_event_destroy(ts_event_t*);
void ts_destroy(ts_t*);

ll_t* ts_get_node(ts_t*, sock_t);
ts_client_t* ts_get_client(ts_t*, sock_t);
ts_client_t* ts_make_client(sk_t*);

int ts_init_socket(sk_t*, int ai_family, uint16_t port);
int ts_bind_socket(sk_t*, struct addrinfo*);

#endif