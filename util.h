/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */


#ifndef BADCHESSENGINE_UTIL_H
#define BADCHESSENGINE_UTIL_H

#include <cstdarg>
#include <malloc.h>
#include <memory>

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

struct str_buf {
    char *data;
    int len;
    int alloc;

    ~str_buf() {
        free(data);
    }
};

inline str_buf *str_alloc_buf(int init) {
    char *data = (char*) malloc(init);
    return new str_buf{
        .data  = data,
        .len   = 0,
        .alloc = init
    };
}

inline void str_realloc_grow(str_buf *buf) {
    int new_alloc = (int)(buf->alloc * 1.5);
    char *old_data = buf->data;
    buf->data = (char*) malloc(new_alloc);
    if (old_data != nullptr) {
        memcpy(buf->data, old_data, buf->len);
    }
    buf->alloc = new_alloc;
}

inline void str_append(str_buf *buf, char* str) {
    char c;
    while ((c = *str) != 0) {
        // append char
        buf->data[buf->len++] = c;

        // resize buffer
        if (buf->len >= buf->alloc) {
            str_realloc_grow(buf);
        }

        // advance
        ++str;
    }
}

inline void str_appendc(str_buf *buf, char c) {
    // append char
    buf->data[buf->len++] = c;

    // resize buffer
    if (buf->len >= buf->alloc) {
        str_realloc_grow(buf);
    }
}

/// @brief To string the given buffer into a C-string.
inline char *str_buf_tocstr(str_buf *buf, int *lenOut = nullptr) {
    int len = buf->len;
    char* r = (char*) malloc(len + 1);
    memcpy(r, buf->data, len);
    r[len] = '\0';
    if (lenOut)
        *lenOut = len;
    return r;
}

/// @brief To string the given buffer into a string.
inline std::string str_buf_tostr(str_buf *buf) {
    int len = buf->len;
    char* r = (char*) malloc(len + 1);
    memcpy(r, buf->data, len);
    return { r, static_cast<unsigned long long>(len) };
}

/// @brief To string the given buffer into a C-string and free it.
inline char *str_buf_ftocstr(str_buf *buf, int *lenOut = nullptr) {
    char *str = str_buf_tocstr(buf, lenOut);
    delete buf;
    return str;
}

/// @brief To string the given buffer into a string and free it.
inline std::string str_buf_ftostr(str_buf *buf) {
    std::string str = str_buf_tostr(buf);
    delete buf;
    return str;
}

inline char *strconcat(int count, int *lenOut = nullptr, ...) {
    va_list args;
    va_start(args, count);

    str_buf *buf = str_alloc_buf(64);
    for (; count >= 0; count--) {
        char* str = va_arg(args, char*);
        str_append(buf, str);
    }

    va_end(args);
    char *str = str_buf_tocstr(buf, lenOut);
    delete buf;
    return str;
}

inline char* stitch_args(int argc, char** argv) {
    str_buf *buf = str_alloc_buf(64);

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
