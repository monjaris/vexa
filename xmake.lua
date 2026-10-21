--- RULES/POLICIES
add_rules("mode.debug", "mode.release");
add_rules("plugin.compile_commands.autoupdate")
-- add_rules("c++.unity_build")


--- SCRIPT-BEGIN
    cxx_flags = {"-W-attributes"}
    ld_flags = {""}

    if is_mode("debug") then
        set_optimize("none")
        set_strip("none")
        debug = true
        cxx_flags = {
            -- "-Wall", "-Wextra",
            "-fno-exceptions",
            "-fno-rtti",
            "-Wuninitialized", "-Werror=uninitialized",
            "-Wno-unused-parameter",
            "-Wno-unused-function",
            "-Wno-unused-variable",
            "-Wno-unused-const-variable",
        };
        ld_flags = {
            -- "-fsanitize=address",
            -- "-flto"
        }

    elseif is_mode("release") then
        set_optimize("fastest")
        set_strip("all")
        debug = false
        cxx_flags = {
            -- "-Wall",
            "-fno-exceptions",
            "-fno-rtti",
            "-Wno-unused-parameter",
            "-Wno-unused-function",
            "-Wno-unused-variable",
            "-Wno-unused-const-variable",
        };
        ld_flags = {
            "-flto"
        }

    end

--- SCRIPT-END


--- GLOBAL
set_languages("c++23")
add_includedirs("include/")
add_includedirs("include/vexa/alt")
add_includedirs("vendor/SDL3/include")
--
add_cxxflags(table.unpack(cxx_flags))
add_ldflags(table.unpack(ld_flags))

--- OPTIONS (i put target-specific options to `./scripts/*`)
option("libcxx")
    set_default("libstdc++")
    set_values("libstdc++", "libc++")
option_end()

--- ON-CONFIG
on_config(function ()
    local libcxx = get_config("libcxx")
    if libcxx == "libc++" then
        add_cxxflags("-stdlib=libc++")
        add_ldflags("-stdlib=libc++")
        add_shflags("-stdlib=libc++")
    elseif libcxx == "libstdc++" then
        -- stdlibc++ is default anyway
    else
        raise(string.format("unsupported libcxx '%s': use 'libstdc++' or 'libc++'", libcxx))
    end
end)


--- TARGETS
includes("scripts/sdl3-static.lua")
includes("scripts/sdl3_ttf-static.lua")
includes("scripts/vexa-dynamic.lua")

--- TESTS
target("game")  add_files("tests/game.cpp")  add_deps("vexa")
target("main")  add_files("tests/main.cpp")  add_deps("vexa")
target("bench")  add_files("tests/bench.cpp")  add_deps("vexa")
target("sdl")  add_files("tests/sdl3.cpp")  add_deps("vexa")
target("font")  add_files("tests/font.cpp")  add_deps("vexa")
target("time")  add_files("tests/time.cpp")  add_deps("vexa")

--- EXAMPLES
includes("examples.lua")
