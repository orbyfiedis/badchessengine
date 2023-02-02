/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

/*
 * Platform specific functions.
 * Implementations are in platform.cpp, dependant
 * by utilizing preprocessor directive.
 */

#ifndef BADCHESSENGINE_PLATFORM_H
#define BADCHESSENGINE_PLATFORM_H

namespace platform {

// enable VT100 sequences on the terminal
int enable_vt();

}

#endif //BADCHESSENGINE_PLATFORM_H
