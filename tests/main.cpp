#include "vexa/vexa.hpp"
using namespace vexa;

int main()
{
    Engine::Init(Engine::VIDEO);

    Window window = Window{}.setSize({1280, 720}).setRenderer({}).create();
    Renderer& gfx = window.renderer();

    Texture texture = gfx.loadTexture("tests/assets/gd.png");
    if (texture.error()) {
        log::error("failed to load texture: {}", texture.path());
    }

    bool running = true;
    while(running)
    {
        if (Event::On(Event::QUIT)) running = false;
        if (Event::ActiveKeys()[Key::ESC]) running = false;

        gfx.start(ColorF32::BLACK);

        gfx.renderTexture(texture, {100, 100});

        gfx.finish();
        time::sleep(time::Millis{16.6});
    }

    Engine::Close();
}
