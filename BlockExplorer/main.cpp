#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include "Block.h"
#include "Controls.h"

SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;
SDL_TimerID timerID = NULL;

bool run = true;
Block* myBlock = new Block();
Uint32 startTime;

using namespace std;

#define SDL_main main
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL ) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool close() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return true;
}

int main(int argc, char* argv[]) {
    if (!init()) {
        return -1;
    }

    SDL_Event event;
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
     startTime = SDL_GetTicks();

    while (run) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - startTime) / 1000.0;
        while(SDL_PollEvent(&event) != 0) {

            switch (event.type) {
                case SDL_QUIT:
                    run = false;
                    break;

            }
        }

        SDL_SetRenderDrawColor(renderer, 0x0,0x0, 0x0, 0x0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255,255,255);
        myBlock->renderPointsToCamera(renderer);

        myBlock->rotateY(renderer, 30 * deltaTime * .2);
        SDL_RenderPresent(renderer);

    }

    if (!close()) {
        return -1;
    }
    return 0;
}
