#include "vexa/vexa.hpp"
#include "vexa/alt/SDL3.h"

using namespace vexa;

int main()
{
    Engine::Init(Engine::VIDEO);

    auto window = Window{}.setSize({1280, 720}).setRenderer({}).create();
    auto& gfx = window.renderer();

    Texture texture = gfx.newTexture("<PATH>");

    bool running = true;
    while(running)
    {
        while (auto ev = Event::Poll()) {
            switch (ev->type()) {
                case Event::QUIT: { running = false; break; }

                default : break;
            }

            if (Event::ActiveKeys()[Key::ESC]) { running = false; }
        }

        gfx.start(ColorF32::BLACK);

        gfx.renderTexture(texture, {100, 100});

        gfx.finish();
        time::sleep(time::Millis{16.6});
    }

    Engine::Close();
}
