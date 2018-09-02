#include "pp/logger.h"
#include <time.h>
#include <stdio.h>

struct log_cfg _logger_cfg = {
  .time_format = NULL,
  .stream = NULL
};

static const char* _log_str[] = {
  "INFO",
  "WARN",
  "ERROR",
  "FATAL"
};

static inline FILE* get_stream()
{
  if (!_logger_cfg.stream)
  {
    return stderr;
  }
  return _logger_cfg.stream;
}

static inline const char* get_time_format()
{
  if (!_logger_cfg.time_format)
  {
    return "%d-%m-%y %X";
  }
  return _logger_cfg.time_format;
}

void logger(const struct log_info* info, const char* format, ...)
{
  va_list ap;
  char buf[32];
  time_t now = time(NULL);

  va_start(ap, format);
  strftime(buf, 32, get_time_format(), localtime(&now));
  fprintf(get_stream(), "%s [ %s ] <%s:%u:%s> ",
    buf, _log_str[info->id], info->file, info->line, info->function);
  vfprintf(get_stream(), format, ap);
  fprintf(get_stream(), "\n");
  va_end(ap);
}
