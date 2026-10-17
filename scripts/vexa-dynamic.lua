-- Link built sdl3 static lib to vexa and compile it as shared lib

local o_SDL = "sdl"
local o_GPU = "gpu"

option("renderer-backend")
    set_default(o_SDL)
    set_values(o_SDL, o_GPU)
option_end()


includes("../vendor/tiny-fmt")

target("vexa")
    set_kind("shared")
    set_languages("c++23")
    add_includedirs("../include", "../vendor")
    add_files("../src/*.cpp")

    -- local dependencies
    add_deps("sdl3", "sdl3_ttf", "tiny-fmt")
    add_syslinks("pthread", "dl", "m", "rt")
    add_shflags("-Wl,--no-undefined")


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
        target:add("shflags", {sdl, ttf})
    end)

target_end()
