#include "logger.h"
#include "asserts.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

i32 initialize_logging(void) {
    // TODO: create log file
    return TRUE;
}

void shutdown_logging(void) {
    // TODO: clean log/write queued entries
    return;
}

void log_output(enum LOG_LEVEL level, const char *message, ...) {
    const char *log_strings[6] = {
        "[FATAL]: ", "[ERROR]: ",
        "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: ",
    };
    b8 is_error = level < 2;

    // Technically imposes a 32k char limit on a single log entry
    // You should not do that though...
    char out_message[32000];
    memset(out_message, 0, sizeof(out_message));

    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[32000];
    sprintf(out_message2, "%s%s\n", log_strings[level], out_message);

    // TODO: platform-specific output
    fprintf(stderr, "%s", out_message2);
}

void report_assertion_failure(const char *expression, const char *message,
                              const char *file, i32 line) {
    log_output(E_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, "
                        "in file %s, line: %d\n",
               expression, message, file, line);
}
