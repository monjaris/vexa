#include "vexa/vexa.hpp"

using namespace vexa;

int main()
{
    auto start = time::now();

    initCores(Core::VIDEO);
    auto ts_init_cores = time::now() - start;

    auto window = Window();
    auto ts_init_window = time::now() - (start + ts_init_cores);

    window.setSize({1280, 720}).setRenderer({}).setResizable();
    auto ts_setup_window = time::now() - (start + ts_init_cores + ts_init_window);

    window = window.create();
    auto ts_create_window = time::now() - (start + ts_init_cores + ts_init_window + ts_setup_window);

    [[maybe_unused]]
    auto finish = time::now();


    log::print("initCores():        {}ms", ts_init_cores.micros() / 1000.f);
    log::print("window=Window():    {}ms", ts_init_window.micros() / 1000.f);
    log::print("window.set_():      {}ms", ts_setup_window.micros() / 1000.f);
    log::print("window.create():    {}ms", ts_create_window.micros() / 1000.f);
}
