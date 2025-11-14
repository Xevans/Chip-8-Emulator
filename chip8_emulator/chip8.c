#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"

//Initialize SDL by checking subsystem
bool initSDL(void) {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Could not initialize SDL subsystems! %s\n", SDL_GetError());
        return false; // fail
    }

    return true; // success
}


void finalCleanup(void) {
    SDL_Quit(); // shutdown SDL subsystem (deallocate heap mem)
}

int main(int argc, char **argv) {
    (void)argc; // because these arguments are not used
    (void)argv;

    // init SDL
    if (!initSDL()) exit(EXIT_FAILURE);

    // Final Cleanup
    finalCleanup();

    exit(EXIT_SUCCESS);
}