#include <assert.h>
#include "../extract.h"

int main()
{
  float f;
  int i[10];
  char* str[10];

  assert(extract("", "") == 0);
  assert(extract(" ", " ") == 0);
  assert(extract("hello", "%s", &str[0]) == 0);
  assert(strcmp(str[0], "hello") == 0);
  assert(extract("42", "%d", &i[0]) == 0);
  assert(i[0] == 42);
  assert(extract("42.0", "%f", &f) == 0);
  assert(f == 42.0f);
  assert(extract("hello world", "%s %s", &str[0], &str[1]) == 0);
  assert(strcmp(str[0], "hello") == 0 && strcmp(str[1], "world") == 0);
  assert(extract("hello_world", "%s", &str[0]) == 0);
  assert(strcmp(str[0], "hello_world") == 0);
  assert(extract("%", "%") < 0);
  assert(extract("%", "%%", NULL) == 0);
  assert(extract("lowercase%UPPERCASE", "%c%%%C", &str[0], NULL, &str[1]) == 0);
  assert(strcmp(str[0], "lowercase") == 0 && strcmp(str[1], "UPPERCASE") == 0);
  assert(extract("test % 423", "test %% %d", NULL, &i[0]) == 0);
  assert(i[0] == 423);
  assert(extract("prout l", "%i %d", &str[0], &i[0]) < 0);
  assert(extract("TEST test 42", "%C %s %d", NULL, &str[0], &i[0]) == 0);
  assert(strcmp(str[0], "test") == 0);
  assert(extract("CONNECT lol 0 -42 1", "%C %s %d %d %d", NULL, &str[0], &i[0], &i[1], &i[2]) == 0);
  assert(strcmp(str[0], "lol") == 0);
  assert(i[0] == 0 && i[1] == -42 && i[2] == 1);
  return (0);
}