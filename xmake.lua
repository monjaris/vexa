--- SETUP
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
add_requires("libsdl3")
add_requires("libsdl3_ttf")

--- CONFIG
add_rules("mode.debug", "mode.release");
add_rules("plugin.compile_commands.autoupdate")

set_languages("c++23")
add_includedirs("include/", {public = true})
add_cxxflags(
    "-fno-exceptions", "-fno-rtti",
    "-Wno-sequence-point"
)

-- whether vexa should be compiled as shared or static library
option("lib")
    set_default("shared")
    set_values("shared", "static")
    set_showmenu(true)
option_end()

-- copy targets' output file to the project root with a .(mode) suffix
after_build(function(target)
    local out = target:filename() .. "." .. get_config("mode")
    os.cp(target:targetfile(), "$(projectdir)/" .. out)
end)



--- TARGETS
target("vexa")
    set_kind(get_config("lib"))
    set_version("0.4.0")
    set_languages("c++23")

    add_files("src/*.cpp")
    add_files("src/renderer_backend/sdl/gfx.cpp")
    add_headerfiles("include/(vexa/**.hpp)")

    add_packages("tiny-fmt", {public = true, system = false})
    add_packages("libsdl3", {system = false})
    add_packages("libsdl3_ttf", {system = false})
    add_shflags("-Wl,--no-undefined")

    after_build(function(target)
        os.cp(target:targetfile(), "$(projectdir)/")
    end)


--- TESTS
target("game")  add_files("tests/game.cpp")  add_deps("vexa")
target("main")  add_files("tests/main.cpp")  add_deps("vexa")
target("bench")  add_files("tests/bench.cpp")  add_deps("vexa")
target("sdl")  add_files("tests/sdl3.cpp")  add_deps("vexa")  add_packages("libsdl3")
target("font")  add_files("tests/font.cpp")  add_deps("vexa")
target("time")  add_files("tests/time.cpp")  add_deps("vexa")

--- EXAMPLES
includes("examples.lua")
