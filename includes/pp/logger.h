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

struct log_cfg
{
  const char* time_format;
  FILE* stream;
};

/*
  Logger's configuration
  If stream is NULL, will use stderr
  If time_format is NULL, will use '%d-%m-%y %X' format (uses strftime)
*/
extern struct log_cfg _logger_cfg;

#define _TRC_PACKED(id)  (&(struct log_info) {id, __LINE__, __FILE__, __func__})
#define TRC_INFO        _TRC_PACKED(LOGGER_INFO)
#define TRC_WARN        _TRC_PACKED(LOGGER_WARN)
#define TRC_ERR         _TRC_PACKED(LOGGER_ERR)
#define TRC_FATAL       _TRC_PACKED(LOGGER_FATAL)

/*
  @description  Log a message using the _logger_cfg
                info parameter should be created by using a TRC_* macro
                Use internally vfprintf()
*/
void logger(const struct log_info* info, const char* format, ...);

#endif
