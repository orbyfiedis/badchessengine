/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */


#ifndef BADCHESSENGINE_UTIL_H
#define BADCHESSENGINE_UTIL_H

// unsafe cast
#define UCAST(v, T) *((T*)&(v))

#define cap(l, v, h) (v) < (l) ? (l) : ((v) > (h) ? (h) : (v))
//#define max(a, b) (a) > (b) ? (a) : (b)
//#define min(a, b) (a) > (b) ? (b) : (a)

// check if a character is uppercase
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

// a position in the code
typedef struct {
    const char *file;
    const int line;
    const char *func;
} CodePos;

#define P    { .file = __FILE__, .line = __LINE__, .func = __func__ }
#define P_IN CodePos pos

// define default prefix format
#ifndef DLOG_PRE_FMT
#define DLOG_PRE_FMT "%s:%i %s "
#endif

// enable by default
#ifndef DLOG_ENABLE
#define DLOG_ENABLE 1
#endif

/// @brief Logs a debug message, with file, line, etc.
/// Prefix Format (DLOG_PRE_FMT): printf format, params: (file, line, func)
void dlog(P_IN, const char *fmt, ...);

/*
 * Errno
 */

#define ENULL 1

#endif //BADCHESSENGINE_UTIL_H
