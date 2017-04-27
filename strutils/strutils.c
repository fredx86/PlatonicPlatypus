#include "strutils.h"

size_t str_count(const char* str, char c)
{
  size_t count = 0;
  for (size_t i = 0; str[i]; ++i)
  {
    if (str[i] == c)
      ++count;
  }
  return (count);
}

size_t str_count_f(const char* str, str_ctype_f contains)
{
  size_t count = 0;
  for (size_t i = 0; str[i]; ++i)
  {
    if (contains(str[i]))
      ++count;
  }
  return (count);
}

size_t str_count_substr(const char* str, const char* substr)
{
  size_t count = 0;
  char* tmp = (char*)str;
  size_t len = strlen(substr);

  while (tmp)
  {
    tmp = strstr(tmp, substr);
    if (tmp == NULL)
      continue;
    tmp += len;
    ++count;
  }
  return (count);
}

char* str_consume(char* str, str_ctype_f contains)
{
  int i = 0;
  while (contains(str[i]))
    ++i;
  return (&str[i]);
}

int str_dup(char** cpy, const char* str)
{
  if (str == NULL)
  {
    *cpy = NULL;
    return (0);
  }
  if ((*cpy = strdup(str)) == NULL)
    return (-1);
  return (0);
}

char* str_cpy_max(char* dest, const char* src, size_t max_len)
{
  size_t i = 0;
  while (src[i] && i < max_len)
  {
    dest[i] = src[i];
    ++i;
  }
  dest[i] = 0;
  return (dest);
}

char* str_lower(char* str)
{
  for (size_t i = 0; str[i]; ++i)
    str[i] = tolower(str[i]);
  return (str);
}

char* str_upper(char* str)
{
  for (size_t i = 0; str[i]; ++i)
    str[i] = toupper(str[i]);
  return (str);
}

char* str_trim(char* str)
{
  size_t starts = 0;
  size_t ends = strlen(str);

  if (ends == 0)
    return (str);
  while (isspace(str[starts]))
    ++starts;
  if (starts != ends--)
  {
    while (isspace(str[ends]))
      --ends;
  }
  memmove(str, str + starts, ends);
  str[ends - starts + 1] = 0;
  return (str);
}

char* str_tokenize(char* str, char c)
{
  size_t j = 0;
  str = str_trim(str);
  for (size_t i = 0; str[i];)
  {
    if (isspace(str[i]))
    {
      str[j++] = c;
      while (isspace(str[i]))
        ++i;
    }
    else
      str[j++] = str[i++];
  }
  str[j] = 0;
  return (str);
}

char** str_split(char* str, const char* sep, int* size)
{
  size_t i = 0;
  char** array;
  char* tmp = str;
  size_t len = strlen(sep);

  *size = str_count_substr(str, sep) + 1;
  if ((array = malloc(sizeof(*array) * (*size))) == NULL)
    return (NULL);
  while (tmp)
  {
    tmp = strstr(str, sep);
    if (tmp == NULL)
      continue;
    array[i++] = str;
    *tmp = 0;
    str = tmp + len;
  }
  array[i] = str;
  return (array);
}

char* str_argument(size_t size, char** haystack, const char* needle)
{
  size_t len = strlen(needle);
  for (size_t i = 0; i < size; ++i)
  {
    if (strncmp(needle, haystack[i], len) == 0 && haystack[i][len] == '=')
      return (haystack[i] + len + 1);
  }
  return (NULL);
}