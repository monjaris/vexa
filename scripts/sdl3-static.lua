-- via CMake, build vendor/SDL3 into a static library

o_X11="x11"
o_WL="wayland"

option("window-backend")
    set_default(o_WL)
    set_values(o_X11, o_WL)
option_end()


target("sdl3")
    set_kind("phony")
    set_policy("build.fence", true)
    set_default(false)

    on_build(function (target)
        import("core.base.option")
        import("core.project.config")
        import("lib.detect.find_tool")

        local cmake = find_tool("cmake")
        assert(cmake, "cmake binary not found")

        local src  = path.join(os.projectdir(), "vendor", "SDL3")
        local bdir = path.join(os.projectdir(), "build", "sdl3-local", "cmake-build")
        local idir = path.join(os.projectdir(), "build", "sdl3-local")
        assert(os.isfile(path.join(src, "CMakeLists.txt")), "missing vendor/SDL3/CMakeLists.txt")
        os.mkdir(bdir)

        local build_type = (config.mode() == "debug") and "Debug" or "Release"
        local jobs = tostring(option.get("jobs") or os.default_njob())
        local video = option.get("window-backend") or o_WL
        local cc = find_tool("clang") and "clang" or "gcc"
        local cxx = find_tool("clang++") and "clang++" or "g++"
        local args = {
            "-S", src, "-B", bdir,
            -- build/install
            "-DCMAKE_BUILD_TYPE=" .. build_type,
            "-DCMAKE_INSTALL_PREFIX=" .. idir,
            "-DCMAKE_INSTALL_LIBDIR=lib",
            -- compiler choices
            "-DCMAKE_C_COMPILER=" .. cc,
            "-DCMAKE_CXX_COMPILER=" .. cxx,
            "-DSDL_SHARED=OFF",
            "-DBUILD_SHARED_LIBS=OFF",
            "-DSDL_STATIC=ON",
            "-DCMAKE_POSITION_INDEPENDENT_CODE=ON",
            -- misc
            "-DSDL_INSTALL=ON",
            "-DSDL_TEST_LIBRARY=OFF",
            "-DSDL_TESTS=OFF",
            "-DSDL_EXAMPLES=OFF",
            "-DSDL_DEPS_SHARED=ON",
        }

        if video == o_WL then
            table.insert(args, "-DSDL_X11=OFF")
            table.insert(args, "-DSDL_WAYLAND=ON")
        elseif video == o_X11 then
            table.insert(args, "-DSDL_X11=ON")
            table.insert(args, "-DSDL_WAYLAND=OFF")
        else
            raise("unsupported window-backend: use o_X11 or o_WL")
        end


        local ninja = find_tool("ninja")
        if ninja then
            table.insert(args, "-G")
            table.insert(args, "Ninja")
        end


        print("SDL3: cmake configure..")
        os.vrunv(cmake.program, args)
        print("SDL3: cmake --build..")
        os.vrunv(cmake.program, {"--build", bdir, "--config", build_type, "-j", jobs})
        os.vrunv(cmake.program, {"--install", bdir, "--config", build_type})

        local libfile = path.join(idir, "lib", "libSDL3.a")
        if not os.isfile(libfile) then
            local found = os.files(path.join(idir, "**", "libSDL3*.a"))
            assert(#found > 0, "cmake did not produce libSDL3.a under " .. idir)
            os.mkdir(path.join(idir, "lib"))
            os.cp(found[1], libfile)
        end

        print("SDL3: installed: " .. libfile)
    end)


    on_clean(function (target)
        os.tryrm(path.join(os.projectdir(), "build", "sdl3-local"))
    end)

target_end()
