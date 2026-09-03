/*=============================================*\

 vexa implementation of Snake (vexa-0.2.0)

 Copyright (c) 2026 @btwmarcel

\*=============================================*/

#include "vexa/vexa.hpp"
#include <cstddef>
#include <deque>
#include <iostream>
#include <optional>
#include <algorithm>
#include <iterator>
#include <random>

using namespace vexa;

constexpr int BOARD_W = 16;
constexpr int BOARD_H = 16;

constexpr int WINDOW_W = 800;
constexpr int WINDOW_H = 800;

constexpr int MOVE_INTERVAL = 250; // miliseconds

constexpr float cell_width = (float)WINDOW_W / BOARD_W;
constexpr float cell_height = (float)WINDOW_H / BOARD_H;

constexpr ColorF32 HEAD_COLOR{0.5f, 1.0f, 0.0f};

struct Cell {
  int x;
  int y;

  bool operator==(const Cell &) const = default;
};

class Snake {
  std::deque<Cell> self = {
      {BOARD_W / 2, BOARD_H / 2},
  };
  time::Date last_move = time::now();
  int dX = 1;
  int dY = 0;

  std::deque<Cell> direction_queue;

public:
  bool Tick() {
    if (last_move.elapsed().millis() < MOVE_INTERVAL)
      return false;

    if (!direction_queue.empty()) {
      dX = direction_queue.front().x;
      dY = direction_queue.front().y;
      direction_queue.pop_front();
    }

    self.push_front(NextHead());

    last_move = time::now();
    return true;
  }

  void Draw(Renderer &gfx) const {
    for (std::size_t i = 0; i < self.size(); ++i) {
      const auto &cell = self[i];

      gfx.rectFill(Rect{cell.x * cell_width, cell.y * cell_height, cell_width,
                        cell_height},
                   i == 0 ? HEAD_COLOR : ColorF32::GREEN);
    }
  }

  Cell NextHead() const {
    Cell new_head{self.front().x + dX, self.front().y + dY};

    // Wall wrap-around
    if (new_head.x < 0)
      new_head.x = BOARD_W - 1;
    else if (new_head.x >= BOARD_W)
      new_head.x = 0;

    if (new_head.y < 0)
      new_head.y = BOARD_H - 1;
    else if (new_head.y >= BOARD_H)
      new_head.y = 0;

    return new_head;
  }

  void SetDirection(int x, int y) {
    int checkX = dX;
    int checkY = dY;

    if (!direction_queue.empty()) {
      checkX = direction_queue.back().x;
      checkY = direction_queue.back().y;
    }

    if (x == checkX && y == checkY)
      return;

    if (self.size() > 1 && x == -checkX && y == -checkY)
      return;

    if (direction_queue.size() >= 2)
      return;

    direction_queue.push_back({x, y});
  }

  std::size_t Length() const { return self.size(); }

  bool Intersects(const Cell &cell) const {
    return std::any_of(self.begin(), self.end(),
                       [&](const Cell &part) { return part == cell; });
  }

  bool HitSelf() const {
    return std::any_of(std::next(self.begin()), self.end(),
                       [&](const Cell &cell) { return cell == self.front(); });
  }

  const Cell &Head() const { return self.front(); }

  void PopTail() { self.pop_back(); }

  void ResetTimer() {
    last_move = time::now();
  }
};

class Food {
  std::random_device rd;
  std::mt19937 gen;

  std::uniform_int_distribution<int> distX;
  std::uniform_int_distribution<int> distY;

public:
  Cell position{};

  Food() : gen(rd()), distX(0, BOARD_W - 1), distY(0, BOARD_H - 1) {}

  bool Respawn(const Snake &snake) {
    if (snake.Length() >= BOARD_W * BOARD_H)
      return false;

    Cell new_pos;

    do {
      new_pos = {distX(gen), distY(gen)};
    } while (snake.Intersects(new_pos));

    position = new_pos;
    return true;
  }

  void Draw(Renderer &gfx) const {
    gfx.rectFill(Rect{position.x * cell_width, position.y * cell_height,
                      cell_width, cell_height},
                 ColorF32::RED);
  }
};

class Game {
  Food food;
  Snake snake;
  Window window;

  bool running = true;
  bool paused = false;

  void Render() {
    auto &gfx = window.renderer();
    gfx.start(Color::BLACK);

    snake.Draw(gfx);
    food.Draw(gfx);
    DrawGrid();

    gfx.finish();
  }

  void Tick() {
    if (!snake.Tick())
      return;

    bool ate = snake.Head() == food.position;

    if (ate) {
      if (!food.Respawn(snake)) {
        std::cout << "You won!\n";
        running = false;
        return;
      }
    } else {
      snake.PopTail();
    }

    if (snake.HitSelf()) {
      std::cout << "You died! (self collision)\n";
      running = false;
    }
  }

  void DrawGrid() {
    auto &gfx = window.renderer();
    for (int x = 0; x <= BOARD_W; ++x) {
      float px = x * cell_width;

      gfx.rectFill(Rect{px, 0, 1, WINDOW_H},
                   ColorF32{0.15f, 0.15f, 0.15f, 1.0f});
    }

    for (int y = 0; y <= BOARD_H; ++y) {
      float py = y * cell_height;

      gfx.rectFill(Rect{0, py, WINDOW_W, 1},
                   ColorF32{0.15f, 0.15f, 0.15f, 1.0f});
    }
  }

  void HandleEvent(Event e) {
    switch (e.type()) {
    case Event::QUIT:
      running = false;
      break;

    case Event::KEY_DOWN: {
      switch (e.kb().key) {
      case Key::ESC:
        running = false;
        break;

      case Key::W:
      case Key::UP:
        snake.SetDirection(0, -1);
        break;

      case Key::A:
      case Key::LEFT:
        snake.SetDirection(-1, 0);
        break;

      case Key::S:
      case Key::DOWN:
        snake.SetDirection(0, 1);
        break;

      case Key::D:
      case Key::RIGHT:
        snake.SetDirection(1, 0);
        break;

      case Key::P:
        paused = !paused;
        if (paused) snake.ResetTimer();
        window.setTitle(paused ? "Snake (unpause with P)" : "Snake");
        break;

      default:
        break;
      }
    } break;

    default:
      break;
    }
  }

public:
  Game() {
    Engine::Init(Engine::VIDEO);
    food.Respawn(snake);
  }

  ~Game() {
    window.destroy();
    Engine::Close();
  }

  void Run() {
    window = Window{}
                 .setSize({WINDOW_W, WINDOW_H})
                 .setTitle("Snake")
                 .setRenderer(Renderer::Cfg{})
                 .create();

    constexpr auto frame_time = time::Millis{16.6f};

    while (running) {
      auto frame_begin = time::now();

      while (auto event = Event::Poll()) {
        HandleEvent(*event);
      }

      if (!paused)
        Tick();

      Render();

      auto elapsed = frame_begin.elapsed().millis();
      auto remaining = frame_time.millis() - elapsed;

      if (remaining > 0)
        time::sleep(time::Millis{remaining});
    }
  }
};

int main() {
  Game game;
  game.Run();
}
