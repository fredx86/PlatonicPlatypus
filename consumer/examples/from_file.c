#include <ctype.h>
#include "consumer.h"

#define FILE_TO_CONSUMER "test.txt"

int is_letter_e(int c)
{
  return (c == 'e');
}

int main()
{
  char* tmp;
  FILE* file;
  size_t saved;
  consumer_t consumer;

  if ((file = fopen(FILE_TO_CONSUMER, "r")) == NULL)
    return (1);

  consumer_file(&consumer, file); //Load from file

  consume_char(&consumer, 'I');

  saved = consumer.read; //Save the current position in order to extract part of input

  consume_str(&consumer, " am");
  consume_func(&consumer, isspace);
  consume_char(&consumer, 'a');
  consume_char(&consumer, ' ');
  consume_func(&consumer, isalnum);
  consume_func(&consumer, is_letter_e);

  tmp = consumer_get(&consumer, saved);
  printf("You've extracted: '%s'\n", tmp);
  free(tmp); //tmp is allocated and should be free() !

  fclose(file);
  return (0);
}