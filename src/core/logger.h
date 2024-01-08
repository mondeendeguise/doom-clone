#pragma once

#include "../defines.h"
#include <stdint.h>

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 0

#if RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

enum LOG_LEVEL {
    E_FATAL = 0,
    E_ERROR = 1,
    E_WARN = 2,
    E_INFO = 3,
    E_DEBUG = 4,
    E_TRACE = 5,
};

int32_t initialize_logging(void);
void shutdown_logging(void);

API void log_output(enum LOG_LEVEL log_level, const char *message, ...);

#define FATAL(message, ...) log_output(E_FATAL, message, ##__VA_ARGS__);

#ifndef ERROR
#define ERROR(message, ...) log_output(E_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define WARN(message, ...) log_output(E_WARN, message, ##__VA_ARGS__);
#else
#define WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define INFO(message, ...) log_output(E_INFO, message, ##__VA_ARGS__);
#else
#define INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define DEBUG(message, ...) log_output(E_DEBUG, message, ##__VA_ARGS__);
#else
#define DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define TRACE(message, ...) log_output(E_TRACE, message, ##__VA_ARGS__);
#else
#define TRACE(DEBUGmessage, ...)
#endif
