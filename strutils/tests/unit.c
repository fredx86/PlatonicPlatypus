#include <assert.h>
#include "../strutils.h"

int main()
{
  int size;
  char** array;
  char trim1[] = "hello world !";
  char trim2[] = " hello world !";
  char trim3[] = "hello world ! ";
  char trim4[] = " hello world ! ";
  char trim5[] = " \t hello world ! \t \t";
  char trim6[] = "";
  char trim7[] = " ";
  char trim8[] = " \t  \t ";
  char split1[] = "hello world !";
  char split2[] = "hello\tworld\t!";
  char split3[] = "hello\t world\t !";

  assert(strcmp(str_trim(trim1), "hello world !") == 0);
  assert(strcmp(str_trim(trim2), "hello world !") == 0);
  assert(strcmp(str_trim(trim3), "hello world !") == 0);
  assert(strcmp(str_trim(trim4), "hello world !") == 0);
  assert(strcmp(str_trim(trim5), "hello world !") == 0);
  assert(strcmp(str_trim(trim6), "") == 0);
  assert(strcmp(str_trim(trim7), "") == 0);
  assert(strcmp(str_trim(trim8), "") == 0);

  assert((array = str_split(split1, " ", &size)) != NULL);
  assert(strcmp(array[0], "hello") == 0);
  assert(strcmp(array[1], "world") == 0);
  assert(strcmp(array[2], "!") == 0);
  assert(size == 3);
  assert((array = str_split(split2, "\t", &size)) != NULL);
  assert(size == 3);
  assert((array = str_split(split3, "\t ", &size)) != NULL);
  assert(size == 3);
  assert(strcmp(array[0], "hello") == 0);
  assert(strcmp(array[1], "world") == 0);
  assert(strcmp(array[2], "!") == 0);
  return (0);
}
