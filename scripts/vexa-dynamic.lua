--- Link built sdl3 static lib to vexa and compile it as shared library
---@diagnostic disable param-type-not-match

target("vexa")
    set_kind("shared")
    set_version("0.2.0")
    set_languages("c++23")

    add_files("../src/*.cpp")
    add_files("../src/renderer_backend/sdl/gfx.cpp")
    add_headerfiles("../include/(vexa/**.hpp)")

    add_packages("tiny-fmt", {public = true})
    add_packages("libsdl3", {system = false})
    add_packages("libsdl3_ttf", {system = false})
    add_syslinks("pthread", "dl", "m", "rt")
    add_shflags("-Wl,--no-undefined")

target_end()
