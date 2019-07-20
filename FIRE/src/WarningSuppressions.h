#ifndef FIRE_WarningSuppressions_h
#define FIRE_WarningSuppressions_h

// clang-format off
#ifdef __clang__
#define SUPPRESS_UnusedFunction    \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-function\"")

#define SUPPRESS_ZeroVariadicMacroArguments \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"")

#define SUPPRESS_Pop \
    _Pragma("GCC diagnostic pop")

#else
#define SUPPRESS_UnusedFunction
#define SUPPRESS_ZeroVariadicMacroArguments
#define SUPPRESS_Pop
#endif
// clang-format on

#endif //FIRE_WarningSuppressions_h