#include "cone.hpp"
#include "alt/SDL3.h"

namespace cn = cone;

auto main() -> int
{
    using cone::Engine;
    using cone::Window;
    using cone::Renderer;
    using cone::ColorU8;
    using cone::Rect;
    namespace log = cone::log;
    namespace time = cone::time;
    Engine::Init(Engine::VIDEO);

    Window::Cfg window_cfg = {};
    Renderer::Cfg renderer_cfg = {};
    fp32 dt = 1000.f/60.f;

    auto tm_init = time::now();
    Window window = Window {window_cfg};
    auto tm_resize = time::now();
    window.setResizable();
    auto tm_size = time::now();
    window.setSize({1280, 720});
    auto tm_render = time::now();
    window.setRenderer(renderer_cfg);
    auto tm_create = time::now();
    window = window.create();
    auto tm_finish = time::now();

    log::info("init: {}", (tm_resize - tm_init).nanos());
    log::info("resize: {}", (tm_size - tm_resize).nanos());
    log::info("size: {}", (tm_render - tm_size).nanos());
    log::info("create: {}", (tm_create - tm_render).nanos());
    log::info("finish: {}", (tm_finish - tm_create).nanos());


    auto& gfx = window.renderer();


    bool running = true;
    while (running) {
        auto start = time::now();

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_EVENT_QUIT: {
                    running = false; break;
                }
                case SDL_EVENT_KEY_DOWN: {
                    switch (ev.key.scancode) {
                        case SDL_SCANCODE_ESCAPE: {
                            running = false; break;
                        }
                        case SDL_SCANCODE_Q: {
                            if (ev.key.mod == SDL_KMOD_LCTRL) running = false;

                            break;
                        }
                        default: {
                        }
                    }
                }
            }
        }


        gfx.start(ColorU8::BLACK);

        gfx.rectFill({Rect{100, 100, 250, 250}}, ColorU8::CYAN);

        gfx.finish();
        time::sleep(time::Millis(dt - start.elapsed().millis()));
    }

    Engine::Close();
}
