#pragma once
#include "Window.hpp"
#include "time.hpp"
NAMESPACE_BEGIN(vexa)


class Engine VX_STATIC_CLASS
{
public:
    enum class Subsystem : uint16 {
        NONE = 1 << 0,
        EVENT = 1 << 1,
        VIDEO = 1 << 2,
        AUDIO = 1 << 3,
        JOYSTICK = 1 << 4,
        HAPTIC = 1 << 5,
        GAMEPAD = 1 << 6,
        SENSOR = 1 << 7,
        CAMERA = 1 << 8,
        //
        FONT
    };

    using enum Subsystem;
    static constexpr auto NON_COMPAT = Subsystem(-1);  // known overflow

private:
    static inline bool m_init = false;
    static inline Flags<Subsystem> m_subsystems;
    static inline time::Date m_init_date;

    static constexpr Subsystem M_toVexaSubsystems(uint32 sdl_flag);
    static constexpr uint32 M_toSDLSubsystems(Subsystem sdl_flag);

public:
    static bool Init(Subsystem initial_subsystems);
    static void Quit();
    static bool InitSubsystems(Subsystem subsystems);
    static void QuitSubsystems(Subsystem subsystems);

    static bool setMouseCaptured(bool yes);

    static time::Date InitDate();
    static time::Nanos Uptime();
    static bool IsMouseCaptured();
};


// generate bit operators for Subsystem enum
GEN_BITOPS(Engine::Subsystem, enum_t<Engine::Subsystem>);


NAMESPACE_END(vexa)
