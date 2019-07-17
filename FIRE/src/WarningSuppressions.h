#ifndef FIRE_WarningSuppressions_h
#define FIRE_WarningSuppressions_h

// clang-format off
#ifndef _WIN32
#define SUPPRESS_UnusedFunction    \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-function\"")

#define SUPPRESS_Pop \
    _Pragma("GCC diagnostic pop")
#else
#define SUPPRESS_UnusedFunction
#define SUPPRESS_Pop
#endif
// clang-format on

#endif //FIRE_WarningSuppressions_h