#ifndef SELECT_H_
#define SELECT_H_

#include "llist.h"

//TODO Temp sock
typedef int sock_t;

#include <sys/select.h>

typedef enum e_select_type
{
  SL_READ   = 1,
  SL_WRITE  = 2
} sl_type;

typedef struct s_select_fd
{
  sock_t sock;
  sl_type type;
} sl_sock_t;

typedef struct s_select
{
  ll_head_t* fds; /* List of sl_sock_t */
  fd_set set[2];
} sl_t;

sl_t* sl_create();

sl_t* sl_update(sl_t*, float seconds);
sl_t* sl_add(sl_t*, sl_type, sock_t);
sl_t* sl_remove(sl_t*, sl_type, sock_t);

ll_t* sl_get_node(const sl_t*, sock_t);
sl_sock_t* sl_get_sock(const sl_t*, sock_t);

sl_sock_t* sl_make_sock(sock_t);

#endif