#ifndef SELECT_H_
#define SELECT_H_

#include "llist.h"
#include "socket.h"
#include "time_utils.h"

typedef enum e_select_type
{
  SL_READ   = 1,
  SL_WRITE  = 2
} sl_type_t;

typedef struct s_select_fd
{
  sock_t sock;
  sl_type_t type;
} sl_sock_t;

typedef struct s_select
{
  ll_head_t* fds; /* List of sl_sock_t */
  fd_set set[2];
} sl_t;

sl_t* sl_create();

int sl_update(sl_t*, float seconds);
sl_t* sl_add(sl_t*, sl_type_t, sock_t);
sl_t* sl_remove(sl_t*, sl_type_t, sock_t);
sl_t* sl_remove_sock(sl_t*, sock_t);

void sl_destroy(sl_t*);

ll_t* sl_get_node(const sl_t*, sock_t);
sl_sock_t* sl_get_sock(const sl_t*, sock_t);

sl_sock_t* sl_make_sock(sock_t);
int sl_set_fdset(sl_t*, sl_sock_t*); /* Return 1 if the given sock was added in a set */
sock_t sl_set_fds(sl_t*); /* Prepare the fd_set's. Return ndfs */

#endif