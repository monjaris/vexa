#pragma once
#include "Window.hpp"
NAMESPACE_BEGIN(vexa)

class Engine VX_STATIC_CLASS
{
public:
    enum class Subsystem : uint8 { VIDEO, AUDIO, EVENT };
    using Subsystem::VIDEO;
    using Subsystem::AUDIO;
    using Subsystem::EVENT;

private:
    static inline bool m_init = false;
    static inline Flags<Subsystem> m_subsystems;

public:
    static bool Init(Subsystem initial_subsystems) noexcept;
    static void Close() noexcept;
    static bool InitSubsystems(Subsystem subsystems) noexcept;
    static void CloseSubsystems(Subsystem subsystems) noexcept;

    static bool setMouseCaptured(bool yes) noexcept;
    static bool IsMouseCaptured() noexcept;
};


// generate bit operators for Subsystem enum
GEN_BITOPS(Engine::Subsystem, underlying_t<Engine::Subsystem>);


NAMESPACE_END(vexa)
