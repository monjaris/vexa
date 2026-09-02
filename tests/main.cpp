#include "vexa/vexa.hpp"
#include "vexa/alt/SDL3.h"
#include "SDL3_ttf/SDL_ttf.h"

using namespace vexa;

int main()
{
    Engine::Init(Engine::VIDEO);

    Window window = Window{}.setSize({1280, 720}).setRenderer({}).create();
    Renderer& gfx = window.renderer();

    // Texture texture = gfx.loadTexture("<PATH>");

    bool running = true;
    while(running)
    {
        if (Event::On(Event::QUIT)) running = false;
        if (Event::ActiveKeys()[Key::ESC]) running = false;

        gfx.start(ColorF32::BLACK);

        // gfx.renderTexture(texture, {100, 100});

        gfx.finish();
        time::sleep(time::Millis{16.6});
    }

    Engine::Close();
}
