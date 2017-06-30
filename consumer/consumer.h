#ifndef PP_CONSUMER_H_
#define PP_CONSUMER_H_

#define PP_CONSUMER_SIZE  1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_consumer
{
  unsigned is_file:1;
  union
  {
    FILE* file;
    char* string;
  } handler;
  char buf[PP_CONSUMER_SIZE];
  char* ptr;
  unsigned is_end:1;
  size_t read;
} consumer_t;

/*
  Feed the consumer a string
  /!\ Your string will be transformed !
*/
void consumer_string(consumer_t*, char* str);

/*
  Feed the consumer a file
  /!\ Your file will be transformed !
*/
void consumer_file(consumer_t*, FILE* file);

/* Consume the input if the current char is equals to 'c' */
int consume_char(consumer_t*, char c);

/* Consume the input if the current string starts with 'str' */
int consume_str(consumer_t*, const char* str);

/* Consume the input if the current char if one of the 'chars' */
int consume_first_of(consumer_t*, const char* chars);

/* Consume the input if the current char is between 'start' and 'end' */
int consume_range(consumer_t*, char start, char end);

/*
  Consume the input if the function given as parameter return > 0
  using the current char as its parameter
*/
int consume_func(consumer_t*, int (*func)(int));

/*
  Return the current char
  - Handle the trailing of the input AKA it calls consumer_fill_buf() on reaching the end of the current buffer
*/
char consumer_peek(consumer_t*);

/*
  Return part of the input string from a previous position
  The string returned is malloc'ed and should be free()
  On error, this function returns NULL
  /!\ This function might be expensive
*/
char* consumer_get(consumer_t*, size_t pos);

/* Set the current handler (file or string), and set the 'is_file' flag accordingly */
void consumer_set_handler(consumer_t*, void* handler, int is_file);

/* Used to increment the nb of bytes read & the current ptr */
void consumer_incr(consumer_t*);

/*
  Fill the buffer using the handler.
  Set the 'is_end' flag is the end of input is reached.
*/
void consumer_fill_buf(consumer_t*);

/*
  Subtract the current position by 'pos'
  - Handle both the substraction from the pointer when in range of buffer, and the OOB case
*/
void consumer_rollback(consumer_t*, size_t pos);

#endif