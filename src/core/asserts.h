#pragma once

#include "../defines.h"
#include <stdint.h>

#define ASSERTIONS_ENABLED

#ifdef ASSERTIONS_ENABLED
#if _MSC_VER  // visual studio support
#include <intrin.h>
#define debug_break() __debugbreak()
#else
#define debug_break(void) __builtin_trap()
#endif

API void report_assertion_failure(const char *expression, const char *message,
        const char *file, int32_t line);

#define ASSERT(expr) {                                            \
    if(expr) {                                                    \
    } else {                                                      \
        report_assertion_failure(#expr, "", __FILE__, __LINE__);  \
        debug_break();                                            \
    }                                                             \
}

#define ASSERT_MSG(expr, message) {                                     \
    if(expr) {                                                          \
    } else {                                                            \
        report_assertion_failure(#expr, message,  __FILE__, __LINE__);  \
        debug_break();                                                  \
    }                                                                   \
}

#ifdef _DEBUG
#define ASSERT_DEBUG(expr) {                                      \
    if(expr) {                                                    \
    } else {                                                      \
        report_assertion_failure(#expr, "", __FILE__, __LINE__);  \
        debug_break();                                            \
    }                                                             \
}

#else
#define ASSERT_DEBUG(expr)
#endif

#else // assertions_enabled
#define ASSERT(expr)
#define ASSERT_MSG(expr, msg)
#define ASSERT_DEBUG(expr)
#endif
