#include "vexa/alt/SDL3.h"
#include "vexa/alt/SDL3-TTF.hpp"
#include "vexa/Engine.hpp"
#include "vexa/os.hpp"
NAMESPACE_BEGIN(vexa)

using This = Engine;



bool This::Init(Subsystem initial_subsystems) noexcept {
    if (!m_init) {
        m_init = true;
        m_subsystems = initial_subsystems;
        m_init_date = time::now();
        log::info("Initializing VEXA-{}", VX_VERSION);
        log::info("Engine::Init(): working-directory: {}", os::cwd().data());

        using subsys_int = enum_t<Subsystem>;
        subsys_int subsys = M_toSDLSubsystems(m_subsystems.value());

        if (subsys & CAST<subsys_int>(FONT)) {
            subsys &= ~CAST<subsys_int>(FONT);
            TTF_Init();
        }

        return SDL_Init(subsys);
    }
    return false;
}


void This::Close() noexcept {
    if (m_init) {
        m_init = false;
        m_subsystems.reset();
        log::info("Engine::Close(): ");

        using subsys_int = enum_t<Subsystem>;
        subsys_int subsys = M_toSDLSubsystems(m_subsystems.value());

        if (subsys & CAST<subsys_int>(FONT)) {
            subsys &= ~CAST<subsys_int>(FONT);
            TTF_Quit();
        }

        SDL_Quit();
    }
}


bool This::InitSubsystems(Subsystem subsystems) noexcept {
    m_subsystems.add(subsystems);
    return SDL_InitSubSystem(M_toSDLSubsystems(m_subsystems.value()));
}


void This::CloseSubsystems(Subsystem subsystems) noexcept {
    m_subsystems.sub(subsystems);
    SDL_QuitSubSystem(M_toSDLSubsystems(m_subsystems.value()));
}


bool This::setMouseCaptured(bool yes) noexcept {
    return SDL_CaptureMouse(yes);
}



time::Date This::InitDate() noexcept {
    return m_init_date;
}

time::Nanos This::Uptime() noexcept {
    return m_init_date.elapsed();
}

VX_NODISCARD bool This::IsMouseCaptured() noexcept {
    return (SDL_GetWindowFlags(nullptr) & SDL_WINDOW_MOUSE_CAPTURE);
}





constexpr This::Subsystem This::M_toVexaSubsystems(uint32 sdl_flag) noexcept {
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

constexpr uint32 This::M_toSDLSubsystems(Subsystem subsys) noexcept {
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
