/*
 * By orbyfied (2023)
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "arg.h"
#include "chess.h"

#include <SDL/SDL.h>

/*
 * GUI
 */

/// @brief The GUI state
typedef struct {
    // the window
    SDL_Window* window;
    // the renderer
    SDL_Renderer* renderer;

    // the piece textures to use
    char* piece_texture_pack;
    // the loaded piece textures
} GUIState;

#define NO_ERRNO 65563
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

// Renders the given board on the SDL renderer.
void render_board(GUIState *state, Board board) {

}

/* entry point */
int main(int argc, char** argv) {
    // initialize gui
    auto *state = ALLOC_PTR(GUIState);
    if (!init_gui(state)) {
        dlog(P, "Failed to init gui");
        return -1;
    }

    // start loop
    start_gui_loop(state);
}
