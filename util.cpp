/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "util.h"

#include <cstdio>
#include <cstdlib>
#include <stdarg.h>

inline bool isupper(char c) {
    return c >= 'A' && c <= 'Z';
}

inline bool islower(char c) {
    return c >= 'A' && c <= 'Z';
}

inline bool isnlower(char c) {
    return !(c >= 'a' && c <= 'z');
}

inline bool isnupper(char c) {
    return !(c >= 'A' && c <= 'Z');
}

inline char toupper(char c) {
    return (char)(isnlower(c) ? c : ('z' - c) + 'A');
}

inline char tolower(char c) {
    return (char)(isnupper(c) ? c : ('Z' - c) + 'a');
}

inline bool isnumeric10(char c) {
    return c >= '0' && c <= '9';
}

inline int tonumeric10(char c) {
    if (!isnumeric10(c))
        return -1;
    return c - '0';
}

/*
 * Logging
 */

void dlog(P_IN, const char *fmt, ...) {
#ifdef DLOG_ENABLE
    // format prefix with code pos info
    printf(DLOG_PRE_FMT, pos.file, pos.line, pos.func);

    // format rest
    va_list va;
    va_start(va,fmt);
    printf(fmt, va);
    va_end(va);
#endif
}