#include <ctype.h>
#include "consumer.h"

#define STRING_TO_CONSUME "I am a test string !"

int is_letter_e(int c)
{
  return (c == 'e');
}

int main()
{
  char* tmp;
  size_t saved;
  consumer_t consumer;

  consumer_string(&consumer, STRING_TO_CONSUME); //Load from string

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
  return (0);
}