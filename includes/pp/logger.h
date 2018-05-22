#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdarg.h>
#include <stdio.h>

enum log_id
{
  LOGGER_INFO,
  LOGGER_WARN,
  LOGGER_ERR,
  LOGGER_FATAL
};

struct log_info
{
  enum log_id id;
  unsigned line;
  const char* file;
  const char* function;
};

extern FILE* _logger_stream;

#define TRC_PACKED(id)  (&(struct log_info) {id, __LINE__, __FILE__, __func__})
#define TRC_INFO        TRC_PACKED(LOGGER_INFO)
#define TRC_WARN        TRC_PACKED(LOGGER_WARN)
#define TRC_ERR         TRC_PACKED(LOGGER_ERR)
#define TRC_FATAL       TRC_PACKED(LOGGER_FATAL)

/*
  @description  Log a message to the _logger_stream
                Use internally vfprintf()
                If _logger_stream is NULL, will log on stderr
*/
void logger(const struct log_info* info, const char* format, ...);

#endif
