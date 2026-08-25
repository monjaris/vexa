-- Link built sdl3 static lib to vexa and compile it as shared lib

option("renderer_backend")
    set_default("sdl_renderer")
    set_values("sdl_renderer", "sdl_gpu")
option_end()


target("vexa")
    set_kind("shared")
    set_languages("c++23")
    add_includedirs(path.join(os.projectdir(), "include"), {public = true})
    add_files(path.join(os.projectdir(), "src/*.cpp"))

    add_deps("sdl3")
    add_syslinks("pthread", "dl", "m", "rt")
    add_shflags("-Wl,--no-undefined", {force = true})

    on_config(function (target)
        local lib = path.join(os.projectdir(), "build", "sdl3-local", "lib", "libSDL3.a")

        target:add("shflags", {
            "-Wl,--whole-archive",
            lib,
            "-Wl,--no-whole-archive",
        }, {force = true})
    end)

target_end()
