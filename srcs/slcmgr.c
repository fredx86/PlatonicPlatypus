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

slcmgr_t* sladd(slcmgr_t* slcmgr, socket_t* socket, slcrw_t rw)
{
  if (!_sladd(&slcmgr->sockets[rw], socket))
    return (NULL);
  return (slcmgr);
}

slcmgr_t* slrmv(slcmgr_t* slcmgr, socket_t* socket, slcrw_t rw)
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