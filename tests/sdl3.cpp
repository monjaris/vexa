#include "alt/SDL3.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* swin = SDL_CreateWindow("", 500, 500, 0);
    SDL_SetWindowBordered(swin, false);
    SDL_Renderer* sren = SDL_CreateRenderer(swin, nullptr);

    while (true)
    {
        bool running = true;

        SDL_SetRenderDrawColor(sren, 150, 0, 150, 255);
        SDL_RenderClear(sren);

        SDL_RenderPresent(sren);
        if (!running) break;
        SDL_Delay(16);
    }
}

