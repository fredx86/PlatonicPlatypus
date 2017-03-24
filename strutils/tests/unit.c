#include <assert.h>
#include "../str_utils.h"

int main()
{
  char test1[] = "hello world !";
  char test2[] = " hello world !";
  char test3[] = "hello world ! ";
  char test4[] = " hello world ! ";
  char test5[] = " \t hello world ! \t \t";
  char test6[] = "";
  char test7[] = " ";
  char test8[] = " \t  \t ";

  assert(strcmp(str_trim(test1), "hello world !") == 0);
  assert(strcmp(str_trim(test2), "hello world !") == 0);
  assert(strcmp(str_trim(test3), "hello world !") == 0);
  assert(strcmp(str_trim(test4), "hello world !") == 0);
  assert(strcmp(str_trim(test5), "hello world !") == 0);
  assert(strcmp(str_trim(test6), "") == 0);
  assert(strcmp(str_trim(test7), "") == 0);
  assert(strcmp(str_trim(test8), "") == 0);
  return (0);
}