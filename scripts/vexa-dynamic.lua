-- Link built sdl3 static lib to vexa and compile it as shared lib

local o_SDL = "sdl"
local o_GPU = "gpu"

option("renderer-backend")
    set_default(o_SDL)
    set_values(o_SDL, o_GPU)
option_end()


target("vexa")
    set_kind("shared")
    set_languages("c++23")
    add_includedirs(path.join(os.projectdir(), "vendor", "SDL3_ttf", "include"), {public = true})
    add_files(path.join(os.projectdir(), "src/*.cpp"))

    -- local dependencies
    add_deps("sdl3", "sdl3_ttf")
    add_syslinks("pthread", "dl", "m", "rt")
    add_shflags("-Wl,--no-undefined", {force = true})

    on_load(function (target)
        local rb = get_config("renderer-backend") or o_SDL

        if rb == o_SDL then
            target:add("files", path.join(os.projectdir(), "src/renderer_backend/sdl/*.cpp"))
            target:add("defines", "VEXA_RENDERER_SDL")
        elseif rb == o_GPU then
            target:add("files", path.join(os.projectdir(), "src/renderer_backend/gpu/*.cpp"))
            target:add("defines", "VEXA_RENDERER_GPU")
        else
            raise("unsupported renderer-backend: use 'sdl' or 'gpu'")
        end
    end)


    on_config(function (target)
        local sdl  = path.join(os.projectdir(), "build", "sdl3-local", "lib", "libSDL3.a")
        local ttf  = path.join(os.projectdir(), "build", "sdl3_ttf-local", "lib", "libSDL3_ttf.a")
        target:add("shflags", {
            "-Wl,--whole-archive",
            sdl, ttf,
            "-Wl,--no-whole-archive",
        }, {force = true})
    end)

target_end()
