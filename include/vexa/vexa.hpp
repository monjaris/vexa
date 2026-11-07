#pragma once
//
#include "Renderer.hpp"
#include "Window.hpp"
#include "Event.hpp"
#include "Image.hpp"
#include "time.hpp"
#include "input.hpp"
#include "os.hpp"
#include "rng.hpp"


NAMESPACE_BEGIN(vexa)

enum class Core : uint16 {
    NONE = 1 << 0,
    EVENT = 1 << 1,
    VIDEO = 1 << 2,
    AUDIO = 1 << 3,
    JOYSTICK = 1 << 4,
    HAPTIC = 1 << 5,
    GAMEPAD = 1 << 6,
    SENSOR = 1 << 7,
    CAMERA = 1 << 8,
    FONT = 1 << 15
};

static constexpr auto NON_COMPAT = Core(-1);  // intentional overflow


bool initCores(Core initial_subsystems);
// void quitCores();

bool setMouseCaptured(bool yes);

time::Date InitDate();
time::Nanos Uptime();
bool IsMouseCaptured();


// generate bit operators for Core enum
GEN_BITOPS(Core, enum_t<Core>);


NAMESPACE_END(vexa)
