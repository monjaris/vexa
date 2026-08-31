#include "vexa/vexa.hpp"

using namespace vexa;

struct Player {
    Image image;
    Vec2 pos;
    Vec2 vel;
    fp32 speed = 400;

    void update(fp32 dt) {
        vel = {0, 0};

        const auto& active_keys = Event::ActiveKeys();

        // Modifers
        if (active_keys[Key::LEFT][Key::UP]) {
            vel.x -= speed * math::SQRT2_INV;
            vel.y -= speed * math::SQRT2_INV;
        }
        else if (active_keys[Key::LEFT][Key::DOWN]) {
            vel.x -= speed * math::SQRT2_INV;
            vel.y += speed * math::SQRT2_INV;
        }
        else if (active_keys[Key::RIGHT][Key::UP]) {
            vel.x += speed * math::SQRT2_INV;
            vel.y -= speed * math::SQRT2_INV;
        }
        else if (active_keys[Key::RIGHT][Key::DOWN]) {
            vel.x += speed * math::SQRT2_INV;
            vel.y += speed * math::SQRT2_INV;
        }
        // Raw
        else if (active_keys[Key::LEFT]) { vel.x -= speed; }
        else if (active_keys[Key::RIGHT]) { vel.x += speed; }
        else if (active_keys[Key::UP]) { vel.y -= speed; }
        else if (active_keys[Key::DOWN]) { vel.y += speed; }

        pos += { vel.x * dt, vel.y * dt };
    }

    void render(Renderer& gfx) {
        
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
                case Event::QUIT: { running = false; break; }

                case Event::KEY_DOWN: {
                    if (event->kb().key == Key::ESC) { running = false; break; }
                }

                default: { break; }
            }
        }

        p.update(dt.seconds());
        gfx.start(ColorU8::BLACK);
        p.render(gfx);

        gfx.finish();
        time::sleep(dt);
    }

    Engine::Close();
}
