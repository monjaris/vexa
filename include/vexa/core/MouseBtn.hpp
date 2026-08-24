#pragma once
#include "common.hpp"
NAMESPACE_BEGIN(vexa)


enum class MouseBtn : uint8
{
    NONE = 0,

    // Left, Middle, Right
    LEFT = 1,
    MIDDLE = 2,
    RIGHT = 3,

    // Extra buttons that some mouse have
    EXTRA_1 = 4,
    EXTRA_2 = 5
};


// Bitmasks for the mouse buttons above
enum class MouseBtnMask : uint8
{
    NONE = 0,

    LEFT = 1 << CAST(int8, MouseBtn::LEFT),
    MIDDLE = 1 << CAST(int8, MouseBtn::MIDDLE),
    RIGHT = 1 << CAST(int8, MouseBtn::RIGHT),

    EXTRA_1 = 1 << CAST(int8, MouseBtn::EXTRA_1),
    EXTRA_2 = 1 << CAST(int8, MouseBtn::EXTRA_2),
};


NAMESPACE_END(vexa)
