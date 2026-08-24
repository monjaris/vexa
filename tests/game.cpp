#include "vexa/vexa.hpp"
#include "vexa/alt/SDL3.h"

using namespace vexa;

auto main() -> int
{
    Engine::Init(Engine::VIDEO);

    constexpr auto dt = time::Millis{16.6f};

    auto window = Window {}
        .setResizable()
        .setSize({1280, 720})
        .setRenderer(Renderer::Cfg{})
    .create();

    auto& gfx = window.renderer();

    for (;;)
    {
        auto begin = time::now();

        bool running = true;
        auto quit = [&running] { running = false; };

        while (auto event = Event::Poll()) {
            switch (event->type())
            {
                case Event::QUIT: { log::info("quit.."); quit(); break; }
                case Event::KEY_DOWN: {
                    auto key = event->kb().key;
                    auto mods = event->kb().mods;
                    if (key == Key::ESC) { running = false; }

                    else if (key==Key::Q && filterMods(mods, KeyMod::CTRL, KeyMod::ALT|KeyMod::SHIFT))
                    {
                        quit();
                    }

                    else if (key==Key::X && filterMods(mods, KeyMod::SHIFT|KeyMod::ALT)) {
                        quit();
                    }
                }
                // case cn::Event::TEXT_INPUT: {
                    // cn::log::info("{}", event->text().content);  break;
                // }
                default: { break; }
            }
        }
        if (!running) break;

        gfx.start(ColorU8::BLACK);

        gfx.rectFill({Rect{100, 100, 250, 250}}, ColorU8::CYAN);
        gfx.triangleFill(Triangle({400,400},{500,600},{600,400}), ColorU8::GREEN);
        gfx.triangleLines(Triangle({100, 600}, {175, 500}, {250, 670}), ColorU8::MAGENTA);

        gfx.finish();
        time::sleep(time::Millis(dt.millis() - begin.elapsed().millis()));
    }

    // cn::Engine::Close();
}
