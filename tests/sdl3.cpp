#include <print>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

struct Player {
    SDL_Texture* texture;
    float x, y = 0;

    void start(SDL_Renderer* renderer) {
        
    }

    void render(SDL_Renderer* renderer) {
        SDL_FRect dest{
            100.0f, 100.0f,
            256.0f, 256.0f
        };

        SDL_RenderTexture(renderer, texture, nullptr, &dest);
    }

    void finish() {
        SDL_DestroyTexture(texture);
    }
};


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_CreateWindowAndRenderer("", 1280, 720, 0, &win, &ren);

    Player p;

    p.start(ren);

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }


        SDL_SetRenderDrawColor(ren, 0,0,0,255);
        SDL_RenderClear(ren);

        p.render(ren);

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    p.finish();

    SDL_Quit();
}
