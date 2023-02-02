/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */


#ifndef BADCHESSENGINE_UTIL_H
#define BADCHESSENGINE_UTIL_H

#define cap(l, v, h) (v) < (l) ? (l) : ((v) > (h) ? (h) : (v))
#define max(a, b)    (a) > (b) ? (a) : (b)
#define min(a, b)    (a) > (b) ? (b) : (a)

// check if a character is uppercase
inline bool isupper(char c);
inline bool islower(char c);
inline bool isnlower(char c);
inline bool isnupper(char c);
inline char toupper(char c);
inline char tolower(char c);
inline bool isnumeric10(char c);
inline int tonumeric10(char c);

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
