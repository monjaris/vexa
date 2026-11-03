if is_mode("debug") then
    add_cxxflags(
        "-Wall", "-Wextra",
        "-Wuninitialized", "-Werror=uninitialized",
        "-Wno-unused-parameter",
        "-Wno-unused-function",
        "-Wno-unused-variable",
        "-Wno-unused-const-variable"
    )
end


--- DEPS
add_repositories("mj-xrepo https://github.com/monjaris/mj-xrepo")
add_requires("tiny-fmt", {public = true})
add_requires("libsdl3", {public = true})
add_requires("libsdl3_ttf", {public = true})

--- CONFIG
add_rules("mode.debug", "mode.release");
add_rules("plugin.compile_commands.autoupdate")

set_languages("c++23")
add_includedirs("include/", {public = true})
add_cxxflags(
    "-fno-exceptions", "-fno-rtti",
    "-Wno-sequence-point"
)


--- TARGETS
includes("scripts/vexa-dynamic.lua")

--- TESTS
target("game")  add_files("tests/game.cpp")  add_deps("vexa")
target("main")  add_files("tests/main.cpp")  add_deps("vexa")
target("bench")  add_files("tests/bench.cpp")  add_deps("vexa")
target("sdl")  add_files("tests/sdl3.cpp")  add_deps("vexa")  add_packages("libsdl3")
target("font")  add_files("tests/font.cpp")  add_deps("vexa")
target("time")  add_files("tests/time.cpp")  add_deps("vexa")

--- EXAMPLES
includes("examples.lua")
