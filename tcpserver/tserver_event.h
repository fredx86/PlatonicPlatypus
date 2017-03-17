#ifndef TCP_SERVER_EVENT_H_
#define TCP_SERVER_EVENT_H_

#include "socket.h"
#include "packet.h"

typedef struct s_ts_client ts_client_t;

enum e_ts_event
{
  TS_CONNECT,
  TS_DISCONNECT,
  TS_PACKET
};

typedef struct s_ts_event
{
  enum e_ts_event type;
  sock_t sock_id;
  pk_t* packet;
} ts_event_t;

#endif