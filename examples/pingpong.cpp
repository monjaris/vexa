#include "vexa/vexa.hpp"

using namespace vexa;
Vec2i window_size = {600, 400};

class Paddle
{
protected:
    void KeepIn()
    {
        body.pos.y  = math::clamp(body.pos.y, 0, window_size.y - body.size.y);
    }

public:
    Rect body = Rect{0,0,0,0};
    int speed;

    void Draw(Renderer& gfx)
    {
        gfx.rectFill(body, ColorF32::WHITE);
    }

    void Update(enum Key key)
    {
        if (key == Key::UP) body.pos.y -= speed;
        else if (key == Key::DOWN) body.pos.y += speed;

        KeepIn();
    }

};


int main(void)
{

    Engine::Init(Engine::VIDEO);

    constexpr auto dt = time::Millis{16.6f};

    auto window = Window {}
    .setResizable()
    .setSize(window_size)
    .setRenderer(Renderer::Cfg{})
    .create();
    auto& gfx = window.renderer();

    Paddle player;

    player.body.pos = {10, 10};
    player.body.size = {10, 100};
    player.speed = 5;

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

                    player.Update(key);

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

        player.Draw(gfx);

        gfx.finish();
        time::sleep(time::Millis(dt.millis() - begin.elapsed().millis()));

    }

    Engine::Close();
    return 0;
}
