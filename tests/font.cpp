#include "vexa/vexa.hpp"

namespace vx = vexa;


int main()
{
    vx::Engine::Init(vx::Engine::VIDEO);
    vx::Window::Cfg window_config;
    window_config.is_resizable = true;
    window_config.size = {1280, 720};
    auto window = vx::Window(window_config).setRenderer({}).create();
    auto& gfx = window.renderer();

    while (true)
    {
        bool running = true;

        while (auto event = vx::Event::Poll()) {
            auto type = event->type();
            auto key = event->kb().key;
            auto mods = event->kb().mods;

            if (type == vx::Event::QUIT) {
                running = false;
            }
            else if ((key == vx::Key::ESC) && mods == vx::KeyMod::NONE) {
                running = false;
            }
        }
        if (!running) break;

        gfx.start();

        gfx.rectFill({100, 100, 100, 100}, vx::Color::RED);

        gfx.finish();
        vx::time::sleep(vx::time::Millis{16});
    }

    vx::Engine::Quit();
}
