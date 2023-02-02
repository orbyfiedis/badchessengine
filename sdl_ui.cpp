/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "sdl_ui.h"

#ifdef SDL_UI_ENABLE

#include <SDL/SDL.h>

/*
 * GUI
 */

int handle_sdl_err(CodePos pos, const char *stage, int code) {
    if (code == 0)
        return 0;
    if (code != -NO_ERRNO)
        dlog(pos, "SDL call %s failed, code(%i): %s\n", stage, code, SDL_GetError());
    else
        dlog(pos, "SDL call %s failed: %s\n", stage, SDL_GetError());
    return -1;
}

// Initialize the GUI
int init_gui(GUIState *state) {
    int ret;

    // init sdl
    if ((ret = SDL_Init(SDL_INIT_EVERYTHING)) != 0) {
        return handle_sdl_err(P, "Init", ret);
    }

    // create window
    state->window = SDL_CreateWindow("BadChessEngine",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     1200, 900, 0);
    if (!state->window) {
        return handle_sdl_err(P, "CreateWindow", -NO_ERRNO);
    }

    // create renderer
    state->renderer = SDL_CreateRenderer(state->window, 0, 0);
    if (!state->renderer) {
        return handle_sdl_err(P, "CreateRenderer", -NO_ERRNO);
    }
}

// Start the GUI loop
void start_gui_loop(GUIState *state) {

}

/*
 * Render: Board
 */

const char *board_get_texture_path(GUIState *state, const char *name) {
    return strconcat(3, nullptr, "./res/boardtex/", name, "/");
}

// Renders the given board on the SDL renderer.
void render_board(GUIState *state, Board board) {

}

#endif