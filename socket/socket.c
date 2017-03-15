#include "socket.h"

void sk_close(sk_t* socket)
{
#ifdef _WIN32
  closesocket(socket->sock);
#elif __linux__
  shutdown(socket->sock, SHUT_RDWR);
  close(socket->sock);
#endif
}