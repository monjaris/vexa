-- via CMake, build vendor/SDL3_ttf into a static library

target("sdl3_ttf")
    set_kind("phony")
    set_policy("build.fence", true)
    set_default(false)
    add_deps("sdl3")

    on_build(function (target)
        import("core.base.option")
        import("core.project.config")
        import("lib.detect.find_tool")

        local cmake = find_tool("cmake")
        assert(cmake, "cmake binary not found")

        local src  = path.join(os.projectdir(), "vendor", "SDL3_ttf")
        if not os.isfile(path.join(src, "CMakeLists.txt")) then
            src = path.join(os.projectdir(), "vendor", "SDL_ttf")
        end
        local sdl3_idir = path.join(os.projectdir(), "build", "sdl3-local")
        local bdir = path.join(os.projectdir(), "build", "sdl3_ttf-local", "cmake-build")
        local idir = path.join(os.projectdir(), "build", "sdl3_ttf-local")
        assert(os.isfile(path.join(src, "CMakeLists.txt")), "missing vendor/SDL3_ttf/CMakeLists.txt (or vendor/SDL_ttf)")
        assert(os.isdir(sdl3_idir), "sdl3 install prefix missing; build target sdl3 first")
        os.mkdir(bdir)

        local build_type = (config.mode() == "debug") and "Debug" or "Release"
        local jobs = tostring(option.get("jobs") or os.default_njob())
        local cc = find_tool("clang") and "clang" or "gcc"
        local cxx = find_tool("clang++") and "clang++" or "g++"
        local args = {
            "-S", src, "-B", bdir,
            "-DCMAKE_BUILD_TYPE=" .. build_type,
            "-DCMAKE_INSTALL_PREFIX=" .. idir,
            "-DCMAKE_INSTALL_LIBDIR=lib",
            "-DCMAKE_PREFIX_PATH=" .. sdl3_idir,
            "-DSDL3_DIR=" .. path.join(sdl3_idir, "lib", "cmake", "SDL3"),
            "-DCMAKE_C_COMPILER=" .. cc,
            "-DCMAKE_CXX_COMPILER=" .. cxx,
            "-DBUILD_SHARED_LIBS=OFF",
            "-DCMAKE_POSITION_INDEPENDENT_CODE=ON",
            "-DSDLTTF_SAMPLES=OFF",
            "-DSDLTTF_INSTALL=ON",
            "-DSDLTTF_VENDORED=ON",
            "-DSDLTTF_HARFBUZZ=ON",
            "-DSDLTTF_PLUTOSVG=ON",
        }

        local ninja = find_tool("ninja")
        if ninja then
            table.insert(args, "-G")
            table.insert(args, "Ninja")
        end

        print("SDL3_ttf: cmake configure..")
        os.vrunv(cmake.program, args)
        print("SDL3_ttf: cmake --build..")
        os.vrunv(cmake.program, {"--build", bdir, "--config", build_type, "-j", jobs})
        os.vrunv(cmake.program, {"--install", bdir, "--config", build_type})

        local libfile = path.join(idir, "lib", "libSDL3_ttf.a")
        if not os.isfile(libfile) then
            local found = os.files(path.join(idir, "**", "libSDL3_ttf*.a"))
            assert(#found > 0, "cmake did not produce libSDL3_ttf.a under " .. idir)
            os.mkdir(path.join(idir, "lib"))
            os.cp(found[1], libfile)
        end

        print("SDL3_ttf: installed: " .. libfile)
    end)

    on_clean(function (target)
        os.tryrm(path.join(os.projectdir(), "build", "sdl3_ttf-local"))
    end)

target_end()
