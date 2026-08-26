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
        gfx.rectFill(Rect{250, 200, 200, 200}, ColorF32::CYAN);
        gfx.circleFill(Circle{{200, 400}, 80}, ColorF32::RED, Circle::POOR);
        gfx.circleFill(Circle{{400, 400}, 80}, ColorF32::RED, Circle::FAIR);
        gfx.circleFill(Circle{{600, 400}, 80}, ColorF32::RED, Circle::NORMAL);
        gfx.circleFill(Circle{{800, 400}, 80}, ColorF32::RED, Circle::CRISP);
        gfx.circleFill(Circle{{1000, 400}, 80}, ColorF32::RED, Circle::PERFECT);
        gfx.finish();
        time::sleep(time::Millis{16.67});
    }

    Engine::Close();
}
