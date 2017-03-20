#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <stdio.h>
#include "select.h"
#include "packet.h"
#include "socket.h"
#include "tserver_event.h"

typedef struct s_tcp_server ts_t;
typedef uint32_t (*ts_packet_f)(const ba_t*, char);

typedef struct s_ts_client
{
  sk_t socket;
  ba_t* inbound;
  ba_t* outbound;
  char status;
} ts_client_t;

typedef struct s_tcp_server
{
  sl_t* select;
  ll_head_t* clients; /* List of ts_client_t */ //TODO Replace with hashmap!
  sk_t socket;
  ts_packet_f on_rcvd;
  ll_head_t* events; /* List of ts_event_t */
} ts_t;

ts_t* ts_create(int ai_family, uint16_t port, ts_packet_f on_rcvd);

ts_t* ts_update(ts_t*, float seconds);
ts_event_t* ts_poll(ts_t*);

ts_t* ts_send(ts_t*, sock_t, const ba_t*);
ts_t* ts_send_client(ts_t*, ts_client_t*, const ba_t*);
ts_t* ts_send_all(ts_t*, const ba_t*);

void ts_remove(ts_t*, sock_t, char);
void ts_remove_client(ts_t*, ts_client_t*, char);

void ts_event_destroy(ts_event_t*);
void ts_destroy(ts_t*);

ts_t* ts_update_client(ts_t*, ts_client_t*);

ll_t* ts_get_node(ts_t*, sock_t);
ts_client_t* ts_get_client(ts_t*, sock_t);
ts_client_t* ts_make_client(sk_t*);
ts_event_t* ts_make_event(ts_t*, enum e_ts_event, sock_t);

ts_client_t* ts_accept(ts_t*);
ts_client_t* ts_read(ts_t*, ts_client_t*, char* should_remove); /* Return NULL on error. Should change the 'should_remove' flag if needed */
ts_client_t* ts_write(ts_t*, ts_client_t*, char* should_remove); /* Return NULL on error. Should change the 'should_remove' flag if needed  */

int ts_init_socket(sk_t*, int ai_family, uint16_t port);
int ts_bind_socket(sk_t*, struct addrinfo*);

#endif