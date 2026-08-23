#include "cone.hpp"
#include "alt/SDL3.h"

namespace cn = cone;
#include <iostream>
auto main() -> int
{
    cn::Engine::Init(cn::Engine::VIDEO);

    constexpr auto dt = cn::time::Millis{16.6f};

    auto window = cn::Window ()
        .setResizable()
        .setSize({1280, 720})
        .setRenderer(cn::Renderer::Cfg{})
    .create();

    auto& gfx = window.renderer();

    for (;;)
    {
        auto begin = cn::time::now();

        bool running = true;
        auto quit = [&running] { running = false; };

        while (auto event = cn::Event::Poll()) {
            using cn::Key;
            using cn::KeyMod;
            using cn::filterMods;

            switch (event->type())
            {
                case cn::Event::QUIT: { cn::log::info("quit.."); quit(); break; }
                case cn::Event::KEY_DOWN: {
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

        gfx.start(cn::ColorU8::BLACK);

        gfx.rectFill({cn::Rect{100, 100, 250, 250}}, cn::ColorU8::CYAN);
        gfx.triangleFill(cn::Triangle({400,400},{500,600},{600,400}), cn::ColorU8::GREEN);
        gfx.triangleLines(cn::Triangle({100, 600}, {175, 500}, {250, 670}), cn::ColorU8::MAGENTA);

        gfx.finish();
        cn::time::sleep(cn::time::Millis(dt.millis() - begin.elapsed().millis()));
    }

    // cn::Engine::Close();
}
