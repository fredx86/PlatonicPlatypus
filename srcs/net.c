#include "pp/net.h"

float htonf(float f)
{
  float cpy = f;

  if (endianess())
    revbytes(&cpy, sizeof(cpy));
  return (cpy);
}

float ntohf(float f)
{
  return (htonf(f));
}