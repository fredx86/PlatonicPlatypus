#include <pp/clist.h>
#include <stdio.h>

int main(int ac, char** av)
{
  void* elem;
  clist_t list;

  if (clcrt(&list, ac, (void**)av) == NULL)
  {
    fprintf(stderr, "clrt()\n");
    return (1);
  }
  while (!clempty(&list))
  {
    elem = clpop(&list);
    printf("%s\n", (char*)elem);
  }
  cldel(&list);
  return (0);
}