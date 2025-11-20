#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

/* convienient struct to reference different SDL properties and define them all in one place.
improves readability*/
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} sdl_t;


/*data structure for SDL configuration settings*/
typedef struct {
    int window_width; // Display window width
    int window_height; // Display window height
    int fg_color; // foreground color RGBA8888
    int bg_color; // backlground color RGBA8888
    int scale_factor; // Amount to scale chip8 pixel by (20x will be a larger window)
} config_t;




//Initialize SDL by checking subsystem
bool initSDL(sdl_t *sdl, const config_t config) {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Could not initialize SDL subsystems! %s\n", SDL_GetError());
        return false; // fail.
    }

    // create SDL window instance to render graphics to
    sdl->window = SDL_CreateWindow(
        "CHIP-8 Emulator", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        config.window_width * config.scale_factor, 
        config.window_height * config.scale_factor,
        0
    );

    // check if window is not null
    if (!sdl->window) {
        SDL_Log("Could not initialize SDL Window %s\n", SDL_GetError());
        return false; // window creation failed
    }


    // create SDL renderer instance
    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);

    // check if renderer is not null
    if (!sdl->renderer) {
        SDL_Log("Could not initialize SDL Renderer %s\n", SDL_GetError());
        return false; // renderer creation failed
    }

    return true; // SDL initialization success
}



// Set up init emulator configuration from passed commandline args
bool set_config_from_args(config_t *config, int argc, char **argv) {

    // set default config
    *config = (config_t) {
        .window_width = 64, // original CHIP8 X resolution
        .window_height = 32, // original CHIP8 Y resolution
        .fg_color = 0xFFFF00FF, // WHITE
        .bg_color = 0xFF000000, // YELLOW
        .scale_factor = 20 // default resolution (1280x640)
    };

    // set config overrides
    for (int i = 0; i < argc; i++) {
        (void)argv[i]; //unused variable (void) tells the compiler that nothing is being done with this var yet
    }

    return true;
}


void finalCleanup(sdl_t *sdl) {
    SDL_DestroyRenderer(sdl->renderer);
    SDL_DestroyWindow(sdl->window);
    SDL_Quit(); // shutdown SDL subsystem
}


// Clear screen
void clearScreen(config_t *config, sdl_t *sdl) {
    const uint8_t r = (config->bg_color >> 24) & 0xFF;
    const uint8_t g = (config->bg_color >> 16) & 0xFF;
    const uint8_t b = (config->bg_color >>  8) & 0xFF;
    const uint8_t a = (config->bg_color >>  0) & 0xFF;

    SDL_SetRenderDrawColor(sdl->renderer, r, g, b, a); // rgba where each value is 8 bits 32 bits total
    SDL_RenderClear(sdl->renderer);
}


void updateScreen(sdl_t *sdl) {
    SDL_RenderPresent(sdl->renderer);
}


int main(int argc, char **argv) {
    // init sdl object from struct.
    sdl_t sdl = {0};

    // init emulator object config
    config_t config = {0};

    // set config settings
    if (!set_config_from_args(&config, argc, argv)) exit(EXIT_FAILURE);

    // set SDL settings
    if (!initSDL(&sdl, config)) exit(EXIT_FAILURE);

    // Initial screen clear. set screen clear to bg color
    clearScreen(&config, &sdl);


    // Main emulation loop
    while (true) {
        // getTime(); // store start time
        // Emulate Chip8 instructions
        // getTime(); // get new time determine time since last instruction and delasy for that amount of time

        // delay for aprox 60hz/60fps. 60hz = (16.67ms)
        SDL_Delay(16 /*- time_elapsed*/);

        // update window with changes
        updateScreen(&sdl);
    }


    // Final Cleanup
    finalCleanup(&sdl);


    exit(EXIT_SUCCESS);
}