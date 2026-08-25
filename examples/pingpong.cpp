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
    Rect body;
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

        gfx.rectFill(Rect{100, 100, 250, 250}, ColorF32::CYAN);

        gfx.finish();
        time::sleep(time::Millis(dt.millis() - begin.elapsed().millis()));

    }

    Engine::Close();
    return 0;
}
