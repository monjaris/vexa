--- RULES/POLICIES
add_rules("mode.debug", "mode.release");
add_rules("plugin.compile_commands.autoupdate")
-- add_rules("c++.unity_build")

--- TOOLCHAIN
toolchain("vexa-llvm")
    set_kind("standalone")
    set_toolset("cc", "clang"); set_toolset("cxx", "clang++");
    set_toolset("as",    "clang"); set_toolset("ar",    "llvm-ar")
    set_toolset("ld",    "clang++"); set_toolset("sh",    "clang++")
    set_toolset("ex",    "clang++"); set_toolset("strip", "llvm-strip")
toolchain_end()

set_toolchains("vexa-llvm")


--- SCRIPT-BEGIN
    cxx_flags = {"-Wall"}
    ld_flags = {""}

    if is_mode("debug") then
        set_optimize("none")
        set_symbols("debug")
        set_strip("none")
        debug = true
        cxx_flags = {
            "-Wall", "-Wextra",
            "-fno-exceptions",
            -- "-fsanitize=address",
            -- "-fno-omit-frame-pointer",
            "-Wuninitialized", "-Werror=uninitialized",
            "-Wno-unused-parameter",
            "-Wno-unused-function",
            "-Wno-unused-variable",
            "-Wno-unused-const-variable",
            "-ftime-trace",
        };
        ld_flags = {
            -- "-fsanitize=address",
            -- "-flto=full"
        }

    elseif is_mode("release") then
        set_optimize("fastest")
        set_symbols("none")
        set_strip("all")
        debug = false
        cxx_flags = {
            "-Wall",
            "-fno-exceptions",
            "-Wno-unused-parameter",
            "-Wno-unused-function",
            "-Wno-unused-variable",
            "-Wno-unused-const-variable",
        };
        ld_flags = {
            "-flto=full"
        }

    end

--- SCRIPT-END


--- GLOBAL
set_languages("c++23")
add_includedirs("include/")
add_includedirs("include/vexa/alt")
-- add_includedirs("include/renderer_backend/renderer")
add_includedirs("vendor/SDL3/include")
set_pcxxheader("include/vexa/alt/SDL3.h")
--
add_cxxflags(table.unpack(cxx_flags))
add_ldflags(table.unpack(ld_flags))

--- OPTIONS (i put target-specific options to `./scripts/*` ;D)
option("libcxx")
    set_default("libstdc++")
    set_values("libstdc++", "libc++")
option_end()

--- config-time stuff
on_config(function ()
    local libcxx = get_config("libcxx")
    if libcxx == "libc++" then
        add_cxxflags("-stdlib=libc++")
        add_ldflags("-stdlib=libc++")
        add_shflags("-stdlib=libc++")
    elseif libcxx == "libstdc++" then
        -- gnu's C++ is default anyway
    else
        raise("unsupported libcxx '%s': use 'libstdc++' or 'libc++'", tostring(libcxx))
    end
end)


--- TARGETS
includes("scripts/sdl3-static.lua")
includes("scripts/vexa-dynamic.lua")


--- TESTS
target("game")  add_files("tests/game.cpp")  add_deps("vexa")
target("main")  add_files("tests/main.cpp")  add_deps("vexa")
target("meter")  add_files("tests/meter.cpp")  add_deps("vexa")
target("cstrlen")  add_files("tests/cstrlen.cpp")  add_deps("vexa")
target("player")  add_files("tests/player.cpp")  add_deps("vexa")
target("size")  add_files("tests/item_size.cpp")  add_deps("vexa")
target("ref")  add_files("tests/ref.cpp")  add_deps("vexa")
target("sdl3-wl")  add_files("tests/sdl3_wl.cpp")  add_deps("vexa")
target("sdl")  add_files("tests/sdl3.cpp")  add_deps("vexa")
target("bound")  add_files("tests/bound.cpp")  add_deps("vexa")
target("time")  add_files("tests/time.cpp")  add_deps("vexa")
target("entity")  add_files("tests/entity.cpp")  add_deps("vexa")

--- EXAMPLES
includes("examples.lua")
target("snake")  add_files("examples/snake.cpp")  add_deps("vexa")
