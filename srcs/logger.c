#include "pp/logger.h"
#include <time.h>
#include <stdio.h>

FILE* _logger_stream = NULL;

static const char* _log_str[] = {
  "INFO",
  "WARN",
  "ERR",
  "FATAL"
};

static inline FILE* get_stream()
{
  return _logger_stream ? _logger_stream : stderr;
}

void logger(const struct log_info* info, const char* format, ...)
{
  va_list ap;
  char buf[32];
  time_t now = time(NULL);

  va_start(ap, format);
  strftime(buf, 32, "%d/%m/%y %X", localtime(&now));
  fprintf(get_stream(), "[%s] [ %s ] <%s:%u(%s)> ",
    buf, _log_str[info->id], info->file, info->line, info->function);
  vfprintf(stderr, format, ap);
  fprintf(stderr, "\n");
  va_end (ap);
}
