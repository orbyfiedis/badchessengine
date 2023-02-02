/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

/*
 * Shell source code.
 *
 * The shell is the primary way to interact with BadChessEngine.
 * After startup, the user is entered in to it. The shell is used
 * to execute commands, ranging from configuring the engine to starting a
 * new game or opening the SDL GUI to play.
 */

#ifndef BADCHESSENGINE_SHELL_H
#define BADCHESSENGINE_SHELL_H

/// @brief Primary shell state class.
class Shell {
private:
    // if the shell should close
    bool _close;

public:
    Shell() = default;

    // start the shell loop
    // entering into the shell
    // for the remainder of the
    // program, unless an error
    // occurs
    int start();
};

#endif //BADCHESSENGINE_SHELL_H
