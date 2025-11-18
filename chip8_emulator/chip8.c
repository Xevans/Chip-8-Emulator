#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

// convienient struct to reference different SDL properties and define them all in one place.
// improves readability
typedef struct {
    SDL_Window *window;
} sdl_t;


typedef struct {
    int window_width; // Display window width
    int window_height; // Display window height
} config_t;




//Initialize SDL by checking subsystem
bool initSDL(sdl_t *sdl, const config_t config) {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Could not initialize SDL subsystems! %s\n", SDL_GetError());
        return false; // fail
    }

    sdl->window = SDL_CreateWindow(
        "CHIP-8 Emulator", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        config.window_width, 
        config.window_height,
        0
    );

    // check if window is not null
    if (!sdl->window) {
        SDL_Log("Could not initialize SDL Window %s\n", SDL_GetError());
        return false; // window creation failed
    }

    return true; // success
}



// Set up init emulator configuration from passed commandline args
bool set_config_from_args(config_t *config, int argc, char **argv) {

    // set default config
    *config = (config_t) {
        .window_width = 64, // original CHIP8 X resolution
        .window_height = 32, // original CHIP8 Y resolution
    };

    // set config overrides
    for (int i = 0; i < argc; i++) {
        (void)argv[i]; //unused variable (void) tells the compiler that nothing is being done with this var yet
    }
    
    return true;
}


void finalCleanup(sdl_t *sdl) {
    SDL_DestroyWindow(sdl->window);
    SDL_Quit(); // shutdown SDL subsystem
}




int main(int argc, char **argv) {
    (void)argc; // because these arguments are not used
    (void)argv;

    // init sdl object from struct.
    sdl_t sdl = {0};

    // init emulator config
    config_t config = {0};
    if (!set_config_from_args(&config, argc, argv)) exit(EXIT_FAILURE);

    // init SDL
    if (!initSDL(&sdl, config)) exit(EXIT_FAILURE);

    // Final Cleanup
    finalCleanup(&sdl);


    exit(EXIT_SUCCESS);
}