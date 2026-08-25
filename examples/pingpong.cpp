#include "vexa/vexa.hpp"

using namespace vexa;



int main(void)
{
    Vec2i window_size = {600, 400};
    auto player1 = Rect{20, 20, 20, 100};
    auto player_speed = 6;

    Engine::Init(Engine::VIDEO);

    constexpr auto dt = time::Millis{16.6f};

    auto window = Window {}
    .setResizable()
    .setSize(window_size)
    .setRenderer(Renderer::Cfg{})
    .create();
    auto& gfx = window.renderer();


    bool running = true;
    while (running)
    {
        auto begin = time::now();
        while (auto event = Event::Poll())
        {
            switch (event->type())
            {
                case Event::KEY_DOWN:
                {
                    auto key = event->kb().key;

                    if (key == Key::Q) running = false;
                    if (key == Key::DOWN) player1.pos.y += player_speed;
                    if (key == Key::UP) player1.pos.y -= player_speed;

                    break;
                }
                case Event::QUIT:
                {
                    running = false;
                    break;
                }
                default: break;
            }
        }
        if (!running) break;

        gfx.start(ColorU8::BLACK);

        gfx.rectFill(player1, ColorU8::CYAN);

        gfx.finish();
        time::sleep(time::Millis(dt.millis() - begin.elapsed().millis()));

    }

    Engine::Close();
    return 0;
}
