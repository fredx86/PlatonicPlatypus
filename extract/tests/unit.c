#include <assert.h>
#include "../extract.h"

int main()
{
  int i[10];
  float f;
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
  assert(extract("hello world", "%s", &str[0]) < 0);
  assert(extract("hello_world", "%i", &str[0]) == 0);
  assert(strcmp(str[0], "hello_world") == 0);
  assert(extract("%", "%") < 0);
  assert(extract("%", "%%") == 0);
  assert(extract("lowercase%UPPERCASE", "%c%%%C", &str[0], NULL, &str[1]) == 0);
  assert(strcmp(str[0], "lowercase") == 0 && strcmp(str[1], "UPPERCASE") == 0);
  assert(extract("test % 423", "test %% %d", NULL, &i[0]) == 0);
  assert(i[0] == 423);
  assert(extract("test l", "%i %d", &str[0], &i[0]) < 0);
  return (0);
}