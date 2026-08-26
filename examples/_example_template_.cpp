/*=============================

vexa implementation of <GAME> (vexa-<version>)

Copyright (c) <YEAR> @<USER>

=============================*/

#include "vexa/vexa.hpp"

using namespace vexa;


int main()
{
    Engine::Init(Engine::VIDEO);

    auto window = Window{}
        .setSize({1280, 720})
        .setRenderer(Renderer::Cfg{})
        .create();

    auto& gfx = window.renderer();

    bool running = true;
    while (running)
    {
        while (auto event = Event::Poll()) {
            switch (event->type())
            {
                case Event::QUIT: { running = false; }

                case Event::KEY_DOWN: {
                    if (event->kb().key == Key::ESC) { running = false; }
                }

                default: { break; }
            }
        }

        gfx.start(ColorU8::BLACK);
        gfx.rectFill(Rect{100, 100, 250, 250}, ColorF32::CYAN);
        gfx.finish();
    }

    Engine::Close();
}
