/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "util.h"

#include <cstdio>
#include <stdarg.h>

/*
 * Logging
 */

void dlog(P_IN, const char *fmt, ...) {
    // format prefix with code pos info
    printf(DLOG_PRE_FMT, pos.file, pos.line, pos.func);

    // format rest
    va_list va;
    va_start(va,fmt);
    printf(fmt, va);
    va_end(va);
}