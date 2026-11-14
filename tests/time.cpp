#include "vexa/vexa.hpp"

using namespace vexa;

int main()
{
    auto start = time::now();

    initCores(Core::VIDEO);
    auto ts_init = time::now() - start;

    auto window = Window();
    auto ts_iniwin = time::now() - (start + ts_init);

    window.setSize({1280, 720}).setRenderer({}).setResizable();
    auto ts_setwin = time::now() - (start + ts_init + ts_iniwin);

    window = window.create();
    auto ts_createwin = time::now() - (start + ts_init + ts_iniwin + ts_setwin);

    [[maybe_unused]]
    auto finish = time::now();


    log::print("initCores():        {}ms", ts_init.micros() / 1000.f);
    log::print("window=Window():    {}ms", ts_iniwin.micros() / 1000.f);
    log::print("window.set_():      {}ms", ts_setwin.micros() / 1000.f);
    log::print("window.create():    {}ms", ts_createwin.micros() / 1000.f);
}
