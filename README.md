# vexa

Modern C++23 graphics/multimedia framework on top of SDL3.

Windowing, events, 2D/3D rendering, timing. Opinionated API, low boilerplate.

## Requirements

- C++23 compiler (clang++)
- [xmake](https://xmake.io)
- CMake + Ninja (used only to build vendored SDL3)

## Build

```bash
./build.sh dev          # debug
./build.sh              # release
```

SDL3 is compiled from vendor/SDL3 into a static library and linked into libvexa.so.
You do not need a system SDL3 package.
Quick example

```c++
#include "vexa/vexa.hpp"

using namespace vexa;

int main()
{
    // Initialize Vexa
    Engine::Init(Engine::VIDEO);

    // create a window with 1280x720 size and default renderer
    auto window = Window{}
        .setSize({1280, 720})
        .setRenderer(Renderer::Cfg{})
        .create();
    auto& gfx = window.renderer();

    bool running = true;
    while (running)
    {
        // poll events
        while (auto event = Event::Poll()) {
            switch (event->type()) {
                case Event::QUIT: { running = false; break; }
                default: { break; }
            }
        }

        gfx.start(ColorU8::BLACK);

        gfx.rectFill(Rect{480, 200, 320, 320}, ColorF32::CYAN);

        gfx.finish();
        time::sleep(time::Millis(16.67));
    }

    Engine::Close();
}
```

# Layout
- include/vexa/     public headers \
- src/              library sources \
- vendor/SDL3/      vendored SDL3 tree \
- tests/            small binaries (game, etc.) \
- xmake/            build scripts (SDL static + vexa shared)

# License (MIT)

See [License](LICENSE.txt).

Vendored SDL3 remains under its own zlib license; keep its notices when redistributing.
