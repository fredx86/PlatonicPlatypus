#include "consumer.h"

void consumer_string(consumer_t* consumer, char* str)
{
  consumer_set_handler(consumer, str, 0);
}

void consumer_file(consumer_t* consumer, FILE* file)
{
  consumer_set_handler(consumer, file, 1);
}

int consume_char(consumer_t* consumer, char c)
{
  if (consumer_peek(consumer) == c)
  {
    consumer_incr(consumer);
    return (1);
  }
  return (0);
}

int consume_str(consumer_t* consumer, const char* str)
{
  for (size_t i = 0; str[i]; ++i)
  {
    if (!consume_char(consumer, str[i]))
    {
      consumer_rollback(consumer, i);
      return (0);
    }
  }
  return (1);
}

int consume_first_of(consumer_t* consumer, const char* chars)
{
  for (size_t i = 0; chars[i]; ++i)
  {
    if (consume_char(consumer, chars[i]))
      return (1);
  }
  return (0);
}

int consume_range(consumer_t* consumer, char start, char end)
{
  char c = consumer_peek(consumer);

  if (c >= start && c <= end)
  {
    consumer_incr(consumer);
    return (1);
  }
  return (0);
}

int consume_func(consumer_t* consumer, int (*func)(int))
{
  if (func(consumer_peek(consumer)))
  {
    consumer_incr(consumer);
    return (1);
  }
  return (0);
}

char consumer_peek(consumer_t* consumer)
{
  if (!consumer->is_end && *consumer->ptr == '\0')
  {
    consumer_fill_buf(consumer);
  }
  return (*consumer->ptr);
}

char* consumer_get(consumer_t* consumer, size_t pos)
{
  char* str;
  size_t len;

  if (consumer->read <= pos)
    return ("");
  len = consumer->read - pos;
  consumer_rollback(consumer, len);
  if ((str = malloc(len + 1)) == NULL)
    return (NULL);
  for (size_t i = 0; i < len; ++i)
  {
    str[i] = consumer_peek(consumer);
    consumer_incr(consumer);
  }
  str[len] = 0;
  return (str);
}

void consumer_set_handler(consumer_t* consumer, void* handler, int is_file)
{
  memset(consumer, 0, sizeof(*consumer));
  consumer->ptr = consumer->buf;
  consumer->handler.string = handler;
  consumer->is_file = is_file;
}

void consumer_incr(consumer_t* consumer)
{
  ++consumer->ptr;
  ++consumer->read;
}

void consumer_fill_buf(consumer_t* consumer)
{
  size_t i;

  consumer->buf[0] = 0;
  if (consumer->is_file)
  {
    fread(consumer->buf, 1, PP_CONSUMER_SIZE - 1, consumer->handler.file);
  }
  else
  {
    for (i = 0; consumer->handler.string[i] && i < PP_CONSUMER_SIZE - 1; ++i)
    {
      consumer->buf[i] = consumer->handler.string[i];
    }
    consumer->buf[i] = 0;
    consumer->handler.string += i;    
  }
  if (consumer->buf == '\0')
  {
    consumer->is_end = 1;
  }
  consumer->ptr = consumer->buf;
}

void consumer_rollback(consumer_t* consumer, size_t pos)
{
  consumer->read -= pos;
  if (pos <= (size_t)(consumer->ptr - consumer->buf))
  {
    consumer->ptr -= pos;
    return;
  }
  if (consumer->is_file)
  {
    fseek(consumer->handler.file, ftell(consumer->handler.file) - pos, SEEK_SET);
  }
  else
  {
    consumer->handler.string -= pos + strlen(consumer->ptr);
  }
  consumer_fill_buf(consumer);
}