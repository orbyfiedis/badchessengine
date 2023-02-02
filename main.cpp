/*
 * By orbyfied (2023)
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "shell.h"

// the shell
static Shell *g_shell;

/* entry point */
int main(int argc, char** argv) {
    // initialize shell
    g_shell = new Shell();
    g_shell->start();
}
