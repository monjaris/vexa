#include "vexa/vexa.hpp"

using namespace vexa;

struct Player {
    Rect body = {{0, 0}, {75, 75}};
    Vec2 vel;
    fp32 speed = 5;

    void input(const Event& ev) {
        vel = {0, 0};

        auto kb = ev.kb();
        if (kb.key == Key::A) vel.x += speed;
        if (kb.key == Key::D) vel.x -= speed;
        if (kb.key == Key::W) vel.y -= speed;
        if (kb.key == Key::S) vel.y += speed;
    }

    void update(fp32 dt) {
        body.pos.x += vel.x * dt;
        body.pos.y += vel.y * dt;
    }

    void render(Renderer& gfx) {
        gfx.rectFill(body, ColorU8::YELLOW);
    }
};


int main()
{
    Engine::Init(Engine::VIDEO);

    auto dt = time::Millis{16.667};

    auto window = Window{}
        .setSize({1280, 720})
        .setRenderer(Renderer::Cfg{})
    .create();

    auto& gfx = window.renderer();

    Player p;

    bool running = true;
    while (running)
    {
        while (auto event = Event::Poll()) {
            switch (event->type())
            {
                case Event::QUIT: { running = false; }

                case Event::KEY_DOWN: {
                    if (event->kb().key == Key::ESC) { running = false; }
                }

                default: { break; }
            }

            p.input(*event);
        }

        p.update(dt.millis());
        log::info("{}, {}", p.body.pos.x, p.body.pos.y);

        gfx.start(ColorU8::BLACK);

        p.render(gfx);

        gfx.finish();
        time::sleep(dt);
    }

    Engine::Close();
}
