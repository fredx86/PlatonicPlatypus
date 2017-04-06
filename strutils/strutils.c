#include "strutils.h"

int str_count(const char* str, char c)
{
  int count = 0;
  for (int i = 0; str[i]; ++i)
  {
    if (str[i] == c)
      ++count;
  }
  return (count);
}

int str_count_f(const char* str, str_ctype_f contains)
{
  int count = 0;
  for (int i = 0; str[i]; ++i)
  {
    if (contains(str[i]))
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
  for (int i = 0; str[i]; ++i)
    str[i] = tolower(str[i]);
  return (str);
}

char* str_upper(char* str)
{
  for (int i = 0; str[i]; ++i)
    str[i] = toupper(str[i]);
  return (str);
}

char* str_trim(char* str)
{
  int starts = 0;
  int ends = strlen(str);

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
  int j = 0;
  str = str_trim(str);
  for (int i = 0; str[i];)
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

char** str_split(char* str, char c, int* size)
{
  int i = 0;
  char** array;
  char* tmp = str;

  *size = str_count(str, c) + 1;
  if ((array = malloc(sizeof(*array) * (*size))) == NULL)
    return (NULL);
  while (*str)
  {
    if (*str == c)
    {
      array[i++] = tmp;
      *(str++) = 0;
      tmp = str;
    }
    else
      ++str;
  }
  array[i] = tmp;
  return (array);
}
