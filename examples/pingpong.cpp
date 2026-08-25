#include "vexa/vexa.hpp"

using namespace vexa;

typedef struct
{
    Rect<Vec2f> body;
    int speed;
}
Player;

int main(void)
{
    Vec2i window_size = {600, 400};
    Player player1 =
    {
        .body = Rect{20, 20, 20, 100},
        .speed = 5
    };

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
                    if (key == Key::DOWN) player1.body.pos.y += player1.speed;
                    if (key == Key::UP) player1.body.pos.y -= player1.speed;

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

        player1.body.pos.y  = math::clamp(player1.body.pos.y, 0, window_size.y - player1.body.size.y);
        if (!running) break;

        gfx.start(ColorU8::BLACK);

        gfx.rectFill(player1.body, ColorU8::CYAN);

        gfx.finish();
        time::sleep(time::Millis(dt.millis() - begin.elapsed().millis()));

    }

    Engine::Close();
    return 0;
}
