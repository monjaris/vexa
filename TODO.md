# TODOs

1. implement vexa::input::*

2. try eliminating these headers from public API:
    <optional>  -- Event.hpp
    <string>  -- Path.hpp, log.hpp
    <cmath>  -- math.hpp
    <type_traits>  -- defs.hpp
    <cstring>  -- StrBuf.hpp

3. make Renderer::setMode() return reference to *this
