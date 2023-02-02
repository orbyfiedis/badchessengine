/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */


#ifndef BADCHESSENGINE_SDL_UI_H
#define BADCHESSENGINE_SDL_UI_H

#ifdef SDL_UI_ENABLE

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
int handle_sdl_err(CodePos pos, const char *stage, int code);

// Initialize the GUI
int init_gui(GUIState *state);

// Start the GUI loop
void start_gui_loop(GUIState *state);

/*
 * Render: Board
 */

const char *board_get_texture_path(GUIState *state, const char *name);

// Renders the given board on the SDL renderer.
void render_board(GUIState *state, Board board);

#endif

#endif //BADCHESSENGINE_SDL_UI_H
