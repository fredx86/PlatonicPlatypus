#ifndef PP_SLCMGR_H_
#define PP_SLCMGR_H_

#include "array.h"
#include "socket.h"

typedef enum e_slcrw
{
  SLC_READ  = 0,
  SLC_WRITE = 1
} slcrw_t;

typedef struct s_slcmgr
{
  socket_t* handler;
  array_t sockets[2]; /* read, write */
  fd_set readfs;
  fd_set writefs;
} slcmgr_t;

slcmgr_t* slcrt(slcmgr_t*, socket_t*);

//int slupdt(slcmgr_t*, float);

slcmgr_t* sladd(slcmgr_t*, socket_t*, slcrw_t);
slcmgr_t* slrmv(slcmgr_t*, socket_t*, slcrw_t);

/* SELECT UTILS */

int _sladd(array_t*, socket_t*);
int _slrmv(array_t*, socket_t*);

/*
sock_t _slmax(slcmgr_t*);
*/

#endif