#include "vexa.hpp"

int main()
{
    IF_THEN(not
        vexa::Engine::Init(vexa::Engine::VIDEO | vexa::Engine::EVENT),
        vexa::log::fatal("Engine didnt start");
    );

    vexa::Window::Cfg window_cfg;
    vexa::Renderer::Cfg renderer_cfg;
    window_cfg.size = {1, 1};
    auto window = vexa::Window{window_cfg}.setRenderer(renderer_cfg).create();
    auto& gfx = window.renderer();

    while(true)
    {
        gfx.start(vexa::ColorF32::BLACK);
        gfx.rectFill({{132, 453}, {132, 343}}, vexa::ColorU8::RED);
        gfx.finish();
        vexa::time::sleep(vexa::time::Millis{16.6});
    }

    vexa::Engine::Close();
}
