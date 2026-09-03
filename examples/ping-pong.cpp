/*=============================================*\

 vexa implementation of ping-pong (vexa-0.0.1)

 Copyright (c) 2026 @gitduck6

\*=============================================*/

#include "vexa/vexa.hpp"
#include <random>
#include <iostream>

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
} // a bit of a C-style function but im too lazy to add internals to Rect

class Ball
{
/*
    * Vexa currently doesnt support circles, so ill use a rectangle and pretend its a ball
    * so it can be easily changed into a ball when circles are implemented
    * e.g. by simply modifying the draw method to something like drawcircle()
    * But who am i kidding, the api is likely to change for such a new framework.
*/
public:
    Vec2i pos = {window_size.x/2, window_size.y/2};
    Vec2 speed  = {3,3};
    float radius = 5;

    int score_player = 0, score_cpu = 0; // The ball can keep the scores cos why not

    void Draw(Renderer& gfx)
    {

        Rect CircleRect = Rect
        {
        pos.x - radius,
        pos.y - radius,
        radius * 2,
        radius * 2
        };

        gfx.rectFill(CircleRect, ColorF32::RED);
    }

    void Update()
    {
        pos.x += speed.x;
        pos.y += speed.y;

        if (pos.x - radius <= 0)
        {
            score_cpu++;
            CheckWin();
            Reset();
        }
        else if (pos.x + radius >= window_size.x)
        {
            score_player++;
            CheckWin();
            Reset();
        }
        if ((pos.y + radius >= window_size.y) || (pos.y - radius <= 0))
            speed.y *= -1.1; // -1.1 so every hit the direction switches and the speed grows a little (exponentially)
    }

    void CheckWin()
    {
        std::cout << score_player << ":" << score_cpu << std::endl; // i know this isnt exactly supposed to be here but its staying..,
        if (score_player >= scoreToWin)
        {
            std::cout << "You win!" << std::endl;
            Engine::Close();
            std::exit(0);
        }
        else if (score_cpu >= scoreToWin)
        {
            std::cout << "You lose!" << std::endl;
            Engine::Close();
            std::exit(0);
        }
    }

    void Reset()
    {
        pos.x = window_size.x / 2;
        pos.y = window_size.y / 2;

        std::random_device rd;
        std::default_random_engine engine(rd());
        std::bernoulli_distribution dist(0.5);
        // i dont fully understand this part
        // but it basically generates a random number "object"
        // and the later used dist function uses this object to get a random boolean

        int speed_choices[2] = {-1, 1};
        speed.x = 3 * speed_choices[dist(engine)];
        speed.y = 3 * speed_choices[dist(engine)];
    }

    bool CheckCollisionRect(Rect rect)
    {
        // My idea is to just to check 4 corners of the ball
        // i know it isnt perfect, but will do for now
        Vec2i bottom_right = {pos.x + (int)(2*radius), pos.y + (int)(2*radius)};
        Vec2i bottom_left = {pos.x, pos.y + (int)(2*radius)};
        Vec2i top_right = {pos.x + (int)(2*radius), pos.y};
        // pos itself is top left

        if (pointInRect(rect, bottom_right)) return true;
        if (pointInRect(rect, bottom_left)) return true;
        if (pointInRect(rect, top_right)) return true;
        if (pointInRect(rect, pos)) return true;
        return false;
    }

};

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

class MachinePaddle : public Paddle
{
public:
    void Update(int ball_y)
    {
        int center_y = body.pos.y + (body.size.y / 2);
        if (center_y > ball_y) body.pos.y -= speed;
        if (center_y < ball_y) body.pos.y += speed;

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

    MachinePaddle machine;
    machine.body.pos = {(float)window_size.x - 20, (float)window_size.y - 10};
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

        if (ball.CheckCollisionRect(player.body))
            ball.speed.x *= -1.1;
        if (ball.CheckCollisionRect(machine.body))
            ball.speed.x *= -1.1;

        machine.Update(ball.pos.y);
        ball.Update();

        if (!running) break;
        gfx.start(Color::BLACK);

        player.Draw(gfx);
        ball.Draw(gfx);
        machine.Draw(gfx);


        gfx.finish();
        time::sleep(time::Millis(dt.millis() - begin.elapsed().millis()));

    }

    Engine::Close();
    return 0;
}
