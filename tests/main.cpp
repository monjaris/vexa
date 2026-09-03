#include "vexa/vexa.hpp"
using namespace vexa;

int main()
{
    Engine::Init(Engine::VIDEO | Engine::FONT);

    Window window = Window{}.setSize({1280, 720}).setRenderer({}).setResizable().create();
    Renderer& gfx = window.renderer();

    Texture texture = gfx.loadTexture(Image::Load("tests/assets/gd.png"));
    Font font = Font::Load("/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Italic.ttf", 32);

    bool running = true;
    while(running)
    {
        if (Event::On(Event::QUIT)) running = false;
        if (Event::ActiveKeys()[Key::ESC]) running = false;

        gfx.start(ColorF32::BLACK);

        gfx.drawTexture(texture, {100, 100});

        gfx.drawText(font, "Hello, World!", {400, 400}, Color::MAGENTA);

        gfx.finish();
        time::sleep(time::Millis{16.6});
    }

    Engine::Close();
}
