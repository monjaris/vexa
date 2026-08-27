// 02_held.cpp
#include <SDL3/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win; SDL_Renderer* ren;
    SDL_CreateWindowAndRenderer("held", 800, 600, 0, &win, &ren);

    SDL_FRect circle = {0, 250, 80, 80};
    const float speed = 6.0f;
    float velx = 0;

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }


        velx = 0;

        const bool* key = SDL_GetKeyboardState(nullptr);
        if (key[SDL_SCANCODE_RIGHT]) velx += speed;
        if (key[SDL_SCANCODE_LEFT]) velx -= speed;

        circle.x += velx;

        SDL_SetRenderDrawColor(ren, 0,0,0,255);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 255,80,80,255);
        SDL_RenderFillRect(ren, &circle);
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_Quit();
}
