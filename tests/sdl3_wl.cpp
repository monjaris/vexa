#include "alt/SDL3.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("", 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    for (;;)
    {
        bool running = true;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_EVENT_QUIT: { running = false; break; }
            }
        }
        if (!running) break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        auto rect = SDL_FRect{100, 100, 100, 100};
        SDL_RenderRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_Quit();
}
