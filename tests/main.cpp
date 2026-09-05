#include "vexa/vexa.hpp"
using namespace vexa;

int main()
{
    Engine::Init(Engine::VIDEO | Engine::FONT);

    Window window = Window{}.setSize({1280, 720}).setRenderer({}).setResizable().create();
    Renderer& gfx = window.renderer();
    gfx.setMode(Renderer::STRETCH);
    window.setAspectRatio(1.6);

    Texture texture = gfx.loadTexture(Image::Load("tests/assets/gd.png"));
    Font font = Font::Load("/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Italic.ttf", 32);

    bool running = true;
    while(running)
    {
        while (auto event = Event::Poll()) {
            switch (event->type()) {
                case Event::QUIT: { running = false; break; }

                case Event::KEY_DOWN: {
                    if (event->kb().key == Key::ESC) { running = false; }

                    break;
                }

                default : break;
            }
        }

        gfx.start(ColorF32::BLACK);

        gfx.drawTexture(texture, {100, 100});

        gfx.drawText(font, "Hello, World!", {400, 400}, Color::MAGENTA);

        gfx.finish();
        time::sleep(time::Millis{16.6});
    }

}
