#include "vexa/alt/SDL3.h"
#include "vexa/Engine.hpp"
NAMESPACE_BEGIN(vexa)

using This = Engine;


bool This::Init(Subsystem initial_subsystems) noexcept {
    if (!m_init) {
        m_init = true;
        m_subsystems = initial_subsystems;
        return SDL_Init(m_subsystems.intValue());
    }
    return false;
}


void This::Close() noexcept {
    if (m_init) {
        m_init = false;
        m_subsystems.reset();
        SDL_Quit();
    }
}


bool This::InitSubsystems(Subsystem subsystems) noexcept {
    m_subsystems.add(subsystems);
    return SDL_InitSubSystem(m_subsystems.intValue());
}


void This::CloseSubsystems(Subsystem subsystems) noexcept {
    m_subsystems.sub(subsystems);
    SDL_QuitSubSystem(m_subsystems.intValue());
}


bool This::setMouseCaptured(bool yes) noexcept {
    return SDL_CaptureMouse(yes);
}

VX_NODISCARD bool This::IsMouseCaptured() noexcept {
    return (SDL_GetWindowFlags(nullptr) & SDL_WINDOW_MOUSE_CAPTURE);
}


NAMESPACE_END(vexa)
