/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "shell.h"

#include "util.h"
#include "arg.h"
#include "platform.h"

#include <stdio.h>
#include <iostream>

/*
 * class Shell
 */

// the state of the shell
enum ShellState {
    SHS_ROOT
};

/// @brief Get the display name of the given state.
const char *get_shs_name(ShellState state) {
    switch (state) {
        case SHS_ROOT: return "root";
    }

    return nullptr;
}

int Shell::start() {
    // attempt to enable VT100 sequences
    if (platform::enable_vt()) {
        dlog(P, "failed to enable vt terminal seq");
    }

    // print tag
    printf("\033[30m#\n");
    printf("\033[30m# BadChessEngine Shell (2023)\n");
    printf("\033[30m# by Orbyfied (very stupid)\n");
    printf("\033[30m#\n");

    // the current state
    ShellState state = SHS_ROOT;

    // start main loop
    _close = false;
    while (!_close) {
        // print prompt
        {
            printf(":");
            printf(get_shs_name(state));
        }

        printf(" $ ");

        // read command line
        std::string line;
        std::getline(std::cin, line);

    }

    // return success
    return 0;
}