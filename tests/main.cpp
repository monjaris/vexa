#include "vexa/vexa.hpp"
#include <string>
#include <filesystem>

using namespace vexa;


std::filesystem::path findProjectRoot()
{
    std::filesystem::path current = os::execPath().cstr();

    while (!current.empty()) {
        if (std::filesystem::exists(current / ".clangd")) {
            return current;
        }

        const std::filesystem::path parent = current.parent_path();

        if (parent == current) {
            break;
        }

        current = parent;
    }

    return {};
}


int main()
{
    vexa::initCores(Core::VIDEO | Core::FONT);

    Window window = Window{}.setSize({1280, 720}).setRenderer({}).setResizable().create();
    Renderer& gfx = window.renderer();
    gfx.setMode(Renderer::STRETCH);

    std::string asset_path = findProjectRoot().string() + "/tests/assets/gd.png";
    Texture texture = gfx.loadTexture(Image::Load(asset_path.c_str()));
    Font font;

    log::setEnabled(false);
    {
        if (!texture.exists()) {
            tfmt::println("The texture is loaded from relative path, inspect the source code");
            ::exit(1);
        }

        font = Font::Load("/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Italic.ttf", 32);
        if (!font.exists()) {
            tfmt::println("Change the hardcoded font from source code, your system doesnt have it");
            ::exit(1);
        }
    }
    log::setEnabled(true);


    bool running = true;
    while(running)
    {
        static auto result = 0;

        while (auto event = Event::Poll()) {
            switch (event->type()) {
                case Event::QUIT: { running = false; break; }

                case Event::KEY_DOWN: {
                    if (event->kb().key == Key::ESC) { running = false; }

                    if (event->kb().key == Key::SPACE) {
                        result = rng::random<int32>(1, 19);
                    }

                    break;
                }

                default : break;
            }
        }

        gfx.start(Color::BLACK);

        gfx.drawText(
            font, tfmt::format("{}", result),
            {500.f, 500.f}, Color::YELLOW
        );

        gfx.drawTexture(texture, {100, 100});

        gfx.drawText(font, "Hello, World!", {400, 400}, Color::MAGENTA);

        gfx.circleFill(Circle{{600, 400}, 100}, Color::RED, Circle::NORMAL);

        gfx.finish();
        time::sleep(time::Millis{16.6});
    }
}
