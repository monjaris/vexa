# vexa

Modern C++23 graphics/multimedia framework on top of SDL3.

Windowing, events, 2D/3D rendering, timing. Opinionated API, low boilerplate.

## Requirements

- C++23 compiler (clang/gcc)
- [xmake](https://xmake.io)
- CMake + Ninja (used only to build vendored code)
- thats all!

## Build

```bash
./build.sh dev          # debug
./build.sh              # release
```

SDL3 is compiled from vendor/SDL3 into a static library and linked into libvexa.so.
You do not need a system SDL3 package.

Minimal example

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
        if (Event::On(Event::QUIT)) running = false;

        gfx.start(ColorU8::BLACK);

        gfx.rectFill(Rect{480, 200, 320, 320}, ColorF32::CYAN);

        gfx.finish();
        time::sleep(time::Millis(16.67));
    }
}
```


# Creating examples for vexa
1. clone this repo
2. find `examples.lua` file
3. add your own example name to the `examples` list
4. go to `examples/` directory and copy-paste `_example_template_.cpp`
5. change file name to `<name-added-to-list>.cpp`
6. fill example header, code an example

note: If you want to publish, fork the repo and do the same steps then make a PR, i will accept it!

# Layout
- `include/vexa/`       public headers
- `src/`                       library sources
- `vendor/`                vendored code
- `scripts/`                 build scripts

# License (MIT)

See [License](LICENSE.txt).

If you use this project, a mention or credit would be greatly appreciated (but is not required beyond the license terms).
