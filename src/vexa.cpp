#include <SDL3/SDL.h>
#include "vexa/vexa.hpp"
NAMESPACE_BEGIN(vexa)

inline bool vx_init = false;
inline Flags<Core> vx_subsystems;
inline time::Date vx_init_date;

constexpr Core M_toVexaCore(uint32 sdl_flag);
constexpr uint32 M_toSDLSubsys(Core sdl_flag);


struct Importer {
    static constexpr auto fontInit = Font::M_InitSystem;
    static constexpr auto fontQuit = Font::M_QuitSystem;
};


bool initCores(Core initial_subsystems) {
    using enum Core;

    if (!vx_init) {
        vx_init = true;
        vx_subsystems = initial_subsystems;
        vx_init_date = time::now();
        log::info("Initializing vexa-{}", VX_VERSION);
        log::info("initCores(): working-directory: {}", os::cwd().data());

        using subsys_int = enum_t<Core>;
        subsys_int subsys = M_toSDLSubsys(vx_subsystems.value());

        if (subsys & CAST<subsys_int>(FONT)) {
            subsys &= ~CAST<subsys_int>(FONT);
            Importer::fontInit();
        }

        return SDL_Init(subsys);
    }
    return false;
}


void quitCores() {
    using enum Core;

    if (vx_init) {
        vx_init = false;
        log::info("quitCores(): uptime = {}s", Uptime().millis() / 1000.0);

        using subsys_int = enum_t<Core>;
        subsys_int subsys = M_toSDLSubsys(vx_subsystems.value());

        if (subsys & CAST<subsys_int>(FONT)) {
            subsys &= ~CAST<subsys_int>(FONT);
            Importer::fontQuit();
        }

        vx_subsystems.reset();
        SDL_Quit();
    }
}



bool setMouseCaptured(bool yes) {
    return SDL_CaptureMouse(yes);
}



time::Date InitDate() {
    return vx_init_date;
}

time::Nanos Uptime() {
    return vx_init_date.elapsed();
}

VX_NODISCARD bool IsMouseCaptured() {
    return (SDL_GetWindowFlags(nullptr) & SDL_WINDOW_MOUSE_CAPTURE);
}




constexpr Core M_toVexaCores(uint32 sdl_flag) {
    using enum Core;

    switch (sdl_flag)
    {
        VX_MAP(AUDIO, SDL_INIT_AUDIO);
        VX_MAP(VIDEO, SDL_INIT_VIDEO);
        VX_MAP(JOYSTICK, SDL_INIT_JOYSTICK);
        VX_MAP(HAPTIC, SDL_INIT_HAPTIC);
        VX_MAP(GAMEPAD, SDL_INIT_GAMEPAD);
        VX_MAP(EVENT, SDL_INIT_EVENTS);
        VX_MAP(SENSOR, SDL_INIT_SENSOR);
        VX_MAP(CAMERA, SDL_INIT_CAMERA);
        VX_MAP(NONE, 0);
    }
    return NON_COMPAT;
}

constexpr uint32 M_toSDLSubsys(Core subsys) {
    using enum Core;

    switch (subsys)
    {
        VX_REVERSE_MAP(SDL_INIT_AUDIO, AUDIO);
        VX_REVERSE_MAP(SDL_INIT_VIDEO, VIDEO);
        VX_REVERSE_MAP(SDL_INIT_JOYSTICK, JOYSTICK);
        VX_REVERSE_MAP(SDL_INIT_HAPTIC, HAPTIC);
        VX_REVERSE_MAP(SDL_INIT_GAMEPAD, GAMEPAD);
        VX_REVERSE_MAP(SDL_INIT_EVENTS, EVENT);
        VX_REVERSE_MAP(SDL_INIT_SENSOR, SENSOR);
        VX_REVERSE_MAP(SDL_INIT_CAMERA, CAMERA);
        VX_REVERSE_MAP(0, NONE);

        default : return -1;
    }
}



NAMESPACE_END(vexa)
