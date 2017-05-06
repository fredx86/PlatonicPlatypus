#include <assert.h>
#include "../extract.h"

int main()
{
  int i;
  float f;
  char* str1 = NULL;
  char* str2 = NULL;

  assert(extract("", "") == 0);
  assert(extract(" ", " ") == 0);
  assert(extract("hello", "%s", &str1) == 0);
  assert(str1 != NULL && strcmp(str1, "hello") == 0);
  assert(extract("42", "%d", &i) == 0);
  assert(i == 42);
  assert(extract("42.0", "%f", &f) == 0);
  assert(f == 42.0f);
  assert(extract("hello world", "%s %s", &str1, &str2) == 0);
  assert(str1 != NULL && str2 != NULL && strcmp(str1, "hello") == 0 && strcmp(str2, "world") == 0);
  assert(extract("hello world", "%s", &str1) < 0);
  assert(extract("hello_world", "%i", &str1) == 0);
  assert(str1 != NULL && strcmp(str1, "hello_world") == 0);
  assert(extract("%", "%") < 0);
  assert(extract("%", "%%") == 0);
  assert(extract("lowercase%UPPERCASE", "%c%%%C", &str1, NULL, &str2) == 0);
  assert(str1 != NULL && str2 != NULL && strcmp(str1, "lowercase") == 0 && strcmp(str2, "UPPERCASE") == 0);
  assert(extract("test % 423", "test %% %d", NULL, &i) == 0);
  assert(i == 423);
  return (0);
}