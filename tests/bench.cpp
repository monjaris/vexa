// #include "vexa/vexa.hpp"

// using namespace vexa;

auto main() -> int
{
//     Engine::Init(Engine::VIDEO);

//     Window::Cfg window_cfg = {};
//     Renderer::Cfg renderer_cfg = {};
//     fp32 dt = 1000.f/60.f;

//     // // auto tm_init = time::now();
//     // // Window window = Window {window_cfg};
//     // // auto tm_resize = time::now();
//     // // window.setResizable();
//     // // auto tm_size = time::now();
//     // // window.setSize({1280, 720});
//     // // auto tm_render = time::now();
//     // // window.setRenderer(renderer_cfg);
//     // // auto tm_create = time::now();
//     // // window = window.create();
//     // // auto tm_finish = time::now();

//     // log::info("init: {}", (tm_resize - tm_init).nanos());
//     // log::info("resize: {}", (tm_size - tm_resize).nanos());
//     // log::info("size: {}", (tm_render - tm_size).nanos());
//     // log::info("create: {}", (tm_create - tm_render).nanos());
//     // log::info("finish: {}", (tm_finish - tm_create).nanos());

//     // Window window = Window{window_cfg}.setResizable().setSize({1280, 720}).setRenderer(renderer_cfg).create();

//     auto& gfx = window.renderer();


//     bool running = true;
//     while (running) {
//         while (auto ev = Event::Poll()) {
//             switch (ev->type()) {
//                 case Event::QUIT: {
//                     running = false; break;
//                 }
//                 case Event::KEY_DOWN: {
//                     switch (ev->kb().key) {
//                         case Key::ESC: {
//                             running = false; break;
//                         }
//                         case Key::Q: {
//                             if (filterMods(ev->kb().mods, KeyMod::CTRL)) running = false;
//                             break;
//                         }
//                         default : {}
//                     }
//                 }
//                 default : {}
//             }
//         }


//         gfx.start(Color::BLACK);

//         gfx.rectFill({Rect{100, 100, 250, 250}}, Color::CYAN);

//         gfx.finish();
//         time::sleep(time::Millis{dt});
//     }

//     Engine::Quit();
}
