#include "pp/slcmgr.h"

slcmgr_t* slcrt(slcmgr_t* slcmgr, socket_t* handler)
{
  for (size_t i = 0; i < 2; ++i)
  {
    if ((arcrt(&slcmgr->sockets[i], 0, NULL)) == NULL)
      return (NULL);
  }
  slcmgr->handler = handler;
  return (slcmgr);
}

int slupdms(slcmgr_t* slcmgr, float ms)
{
  struct timeval timeout;

  timems(&timeout, ms);
  return (select(_slmax(slcmgr), &slcmgr->readfs, &slcmgr->writefs, NULL, (ms == 0 ? NULL : &timeout)));
}

slcmgr_t* sladd(slcmgr_t* slcmgr, socket_t* socket, slrw_t rw)
{
  if (!_sladd(&slcmgr->sockets[rw], socket))
    return (NULL);
  return (slcmgr);
}

slcmgr_t* slrmv(slcmgr_t* slcmgr, socket_t* socket, slrw_t rw)
{
  if (!_slrmv(&slcmgr->sockets[rw], socket))
    return (NULL);
  return (slcmgr);
}

int _sladd(array_t* array, socket_t* socket)
{
  if (!arhas(array, socket))
    return (aradd(array, socket) != NULL);
  return (1);
}

int _slrmv(array_t* array, socket_t* socket)
{
  return (arrmvv(array, socket) != NULL);
}

sock_t _slmax(slcmgr_t* slcmgr)
{
  return (_slarmax(&slcmgr->sockets[1],
    _slarmax(&slcmgr->sockets[0], slcmgr->handler->sock))
  );
}

sock_t _slarmax(array_t* array, sock_t sockId)
{
  sock_t tmp = sockId;

 for (size_t i = 0; i < array->size; ++i)
 {
  if (((socket_t*)array->item[i])->sock > tmp)
    tmp = ((socket_t*)array->item[i])->sock;
 }
  return (tmp);
}