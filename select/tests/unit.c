#include <assert.h>
#include "../select.h"

int main()
{
  sl_t* select = sl_create();

  assert(select != NULL);

  sl_destroy(select);
  return (0);
}
