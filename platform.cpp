/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "platform.h"

namespace platform {

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || defined(__LINUX__) || (defined(__APPLE__) && defined(__MACH__)))

int enable_vt() {

}

#elif defined(_WIN32)

#include "windows.h"

int enable_vt() {
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    return !SetConsoleMode(stdout, ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT);
}

#endif

}