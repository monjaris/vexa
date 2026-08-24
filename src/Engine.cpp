#include "alt/SDL3.h"
#include "Engine.hpp"
NAMESPACE_BEGIN(vexa)

bool Engine::Init(const Flags initial_subsystems) noexcept {
    if (!m_init) {
        m_init = true;
        m_subsystems = initial_subsystems;
        return SDL_Init(m_subsystems.value());
    }
    return false;
}


void Engine::Close() noexcept {
    if (m_init) {
        m_init = false;
        m_subsystems.reset();
        SDL_Quit();
    }
}


bool Engine::InitSubsystems(Flags subsystems) noexcept {
    m_subsystems.add(subsystems);
    return SDL_InitSubSystem(m_subsystems.value());
}


void Engine::CloseSubsystems(Flags subsystems) noexcept {
    subsystems.sub(subsystems);
    SDL_QuitSubSystem(subsystems.value());
}


bool Engine::setMouseCaptured(bool yes) noexcept {
    return SDL_CaptureMouse(yes);
}

VX_NODISCARD bool Engine::IsMouseCaptured() noexcept {
    return (SDL_GetWindowFlags(nullptr) & SDL_WINDOW_MOUSE_CAPTURE);
}


NAMESPACE_END(vexa)
