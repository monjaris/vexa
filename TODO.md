# TODOs

1. Add fmt() methods for Rect, Vec2, Vec2i, Vec2u, Triangle, Circle etc.

2. try eliminating these headers from public API:
    <optional>  -- Event.hpp
    <algorithm>  -- Event.cpp
    <string>  -- Path.hpp, log.hpp
    <cstring>  -- StrBuf.hpp
    <cmath>  -- math.hpp

3. implement namespace vexa::input

4. time::now() returns time::TimePoint<> specilization but dev may need a different specilization.
