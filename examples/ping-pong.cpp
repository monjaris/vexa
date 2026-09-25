/*=============================================*\

 vexa implementation of ping-pong (vexa-0.0.1)

 Copyright (c) 2026 @gitduck6

\*=============================================*/

#include "vexa/vexa.hpp"

using namespace vexa;


Vec2i window_size = {600, 400};
int scoreToWin = 5;

bool pointInRect(Rect rect, Vec2i point)
{
    if ((point.x > rect.pos.x) && (point.x < (rect.pos.x + rect.size.x)))
    {
        if ((point.y > rect.pos.y) && (point.y < (rect.pos.y + rect.size.y)))
        {
            return true;
        }
    }
    return false;
}

class Ball
{
public:
    Circle circle = Circle{{window_size.x / 2.f, window_size.y / 2.f}, 5};
    Vec2 speed = {3, 3};

    int score_player = 0, score_cpu = 0;

    void draw(Renderer& gfx)
    {
        gfx.circleFill(circle, Color::WHITE, Circle::PERFECT);
    }

    void update()
    {
        circle.pos.x += speed.x;
        circle.pos.y += speed.y;

        if (circle.pos.x - circle.radius <= 0)
        {
            score_cpu++;
            checkWindowBounds();
            resetPosition();
        }
        else if (circle.pos.x + circle.radius >= window_size.x)
        {
            score_player++;
            checkWindowBounds();
            resetPosition();
        }

        if ((circle.pos.y + circle.radius >= window_size.y) || (circle.pos.y - circle.radius <= 0))
            speed.y *= -1.1;
    }

    void checkWindowBounds()
    {
        log::print("{} : {}", score_player, score_cpu);

        if (score_player >= scoreToWin)
        {
            log::print("You WON!");
            Engine::Quit();
            std::exit(0);
        }
        else if (score_cpu >= scoreToWin)
        {
            log::print("Game OVER!");
            Engine::Quit();
            std::exit(0);
        }
    }

    void resetPosition()
    {
        circle.pos.x = window_size.x / 2;
        circle.pos.y = window_size.y / 2;

        int speed_choices[2] = {-1, 1};
        speed.x = 3 * rng::random<int>(speed_choices[0], speed_choices[1]);
        speed.y = 3 * rng::random<int>(speed_choices[0], speed_choices[1]);
    }

    bool checkCollisionRect(const Rect& rect)
    {
        // Find the closest point on the rectangle to the circle center.
        float closest_x = math::clamp(
            circle.pos.x,
            rect.pos.x,
            (rect.pos.x + rect.size.x)
        );

        float closest_y = math::clamp(
            circle.pos.y,
            rect.pos.y,
            (rect.pos.y + rect.size.y)
        );

        float dx = circle.pos.x - closest_x;
        float dy = circle.pos.y - closest_y;

        return (dx * dx + dy * dy) <= (circle.radius * circle.radius);
    }
};


class Paddle
{
protected:
    void clampPosition()
    {
        body.pos.y = math::clamp(body.pos.y, 0, window_size.y - body.size.y);
    }

public:
    Rect body = Rect{0, 0, 0, 0};
    int speed;

    void draw(Renderer& gfx)
    {
        gfx.rectFill(body, ColorF32::WHITE);
    }

    void Update(enum Key key)
    {
        if (key == Key::UP) body.pos.y -= speed;
        else if (key == Key::DOWN) body.pos.y += speed;

        clampPosition();
    }

};

class MachinePaddle : public Paddle
{
public:
    void update(int ball_y)
    {
        int center_y = body.pos.y + (body.size.y / 2);

        if (center_y > ball_y) body.pos.y -= speed;
        if (center_y < ball_y) body.pos.y += speed;

        clampPosition();
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

    MachinePaddle machine;
    machine.body.pos = {
        (float)window_size.x - 20,
        (float)window_size.y - 10
    };
    machine.body.size = {10, 100};
    machine.speed = 3;

    Ball ball;

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

                    if (key == Key::Q)
                        running = false;

                    player.Update(key);

                    break;
                }

                case Event::QUIT:
                {
                    running = false;
                    break;
                }

                default:
                    break;
            }
        }

        if (ball.checkCollisionRect(player.body)) ball.speed.x *= -1.1;

        if (ball.checkCollisionRect(machine.body)) ball.speed.x *= -1.1;

        machine.update(ball.circle.pos.y);
        ball.update();

        if (!running) break;

        gfx.start(Color::BLACK);

        player.draw(gfx);
        ball.draw(gfx);
        machine.draw(gfx);

        gfx.finish();

        time::sleep(
            time::Millis(dt.millis() - begin.elapsed().millis())
        );
    }

    Engine::Quit();
    return 0;
}
