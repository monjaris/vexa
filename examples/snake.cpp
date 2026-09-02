/*=============================================*\

 vexa implementation of Snake (vexa-0.2.0)

 Copyright (c) 2026 @btwmarcel

\*=============================================*/

#include "vexa/core/Key.hpp"
#include "vexa/time.hpp"
#include "vexa/vexa.hpp"
#include <deque>
#include <iostream>
#include <random>

using namespace vexa;

struct Cell {
  int x;
  int y;
};

const int BOARD_W = 20;
const int BOARD_H = 20;

const int WINDOW_W = 800;
const int WINDOW_H = 800;

const float cell_width = (float)WINDOW_W / BOARD_W;
const float cell_height = (float)WINDOW_H / BOARD_H;

int main() {
  Engine::Init(Engine::VIDEO);

  auto window = Window{}
                    .setSize({WINDOW_W, WINDOW_H})
                    .setTitle("Snake")
                    .setRenderer(Renderer::Cfg{})
                    .create();

  auto &gfx = window.renderer();

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> distX(0, BOARD_W - 1);
  std::uniform_int_distribution<int> distY(0, BOARD_H - 1);

  // Directions
  int dX = 1;
  int dY = 0;

  std::deque<Cell> snake{
      {BOARD_W / 2, BOARD_H / 2},
  };

  Cell food{distX(gen), distY(gen)};

  auto last_move = time::now();

  bool running = true;
  while (running) {
    while (auto event = Event::Poll()) {
      switch (event->type()) {
      case Event::QUIT:
        running = false;
        break;

      case Event::KEY_UP: {
        switch (event->kb().key) {
        case Key::ESC:
          running = false;
          break;

        case Key::W:
          dY = -1;
          dX = 0;
          break;

        case Key::A:
          dX = -1;
          dY = 0;
          break;

        case Key::S:
          dY = 1;
          dX = 0;
          break;

        case Key::D:
          dY = 0;
          dX = 1;
          break;

        default:
          break;
        }
      }
      default:
        break;
      }
    }

    gfx.start(ColorU8::BLACK);

    if (last_move.elapsed().millis() >= 250) {
      Cell new_head{snake.front().x + dX, snake.front().y + dY};

      snake.push_front(new_head);
      snake.pop_back();

      last_move = time::now();
    }

    for (const auto &cell : snake) {
      gfx.rectFill(Rect{cell.x * cell_width, cell.y * cell_height, cell_width,
                        cell_height},
                   ColorF32::CYAN);
    }

    gfx.rectFill(Rect{food.x * cell_width, food.y * cell_height, cell_width,
                      cell_height},
                 ColorF32::GREEN);

    if (snake.front().x == food.x && snake.front().y == food.y) { // eat food
      std::cout << "mmm\n";
      food = {distX(gen), distY(gen)};
      Cell new_tail = snake.back();
      new_tail.x -= dX;
      new_tail.y -= dY;
      snake.push_back(new_tail);
    }

    gfx.finish();
  }

  Engine::Close();
}
