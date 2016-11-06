#include <pp/socket.h>

#define BUFF_SIZE 1024

int server_init(socket_t* sock, struct addrinfo* addrinfo)
{
  char reuse = 1;

  if (bind(sock->sock, addrinfo->ai_addr, addrinfo->ai_addrlen) == SOCKET_ERROR)
    return (0);
  if (listen(sock->sock, 1024) == SOCKET_ERROR)
    return (0);
  setsockopt(sock->sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  return (1);
}

int main()
{
  socket_t server;
  socket_t client;
  barray_t response;
  struct addrinfo hints = { 0 };

#ifdef _WIN32
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    return (1);
#endif

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (skcrt(&server, NULL, 4242, &hints, &server_init) == NULL)
  {
    fprintf(stderr, "skcrt()\n");
    return (1);
  }
  if (bacrts(&response, BUFF_SIZE) == NULL) //Create a byte array of size BUFF_SIZE at min
  {
    fprintf(stderr, "bacrts()\n");
    return (1);
  }
  if ((client.sock = accept(server.sock, NULL, 0)) == INVALID_SOCKET)
  {
    fprintf(stderr, "accept()\n");
    return (1);
  }
  if (skrecv(&client, &response, BUFF_SIZE) == -1) //The byte array MUST be at least BUFF_SIZE when given to this function ! This function does NOT allocate in any way !
  {
    fprintf(stderr, "skrecv()\n");
    return (1);
  }
  if (sksend(&client, &response) == -1)
  {
    fprintf(stderr, "sksend()\n");
    return (1);
  }
  skdel(&server);
  skdel(&client);

#ifdef _WIN32
  WSACleanup();
#endif
  return (0);
}