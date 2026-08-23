--- RULES/POLICIES
add_rules("mode.debug", "mode.release", "mode.tsan");
add_rules("plugin.compile_commands.autoupdate")
set_policy("build.progress_style", "multirow")
-- add_rules("c++.unity_build")

--- TOOLCHAIN
toolchain("cone-llvm")
    set_kind("standalone")
    set_toolset("cc", "clang"); set_toolset("cxx", "clang++");
    set_toolset("as",    "clang"); set_toolset("ar",    "llvm-ar")
    set_toolset("ld",    "clang++"); set_toolset("sh",    "clang++")
    set_toolset("ex",    "clang++"); set_toolset("strip", "llvm-strip")
toolchain_end()

set_toolchains("cone-llvm")


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
            "-Wno-unused-function",
            "-Wno-unused-variable",
            "-Wno-unused-const-variable",
            "-Wuninitialized", "-Werror=uninitialized",
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
        };
        ld_flags = {
            "-flto=full"
        }

    end

--- SCRIPT-END


--- GLOBAL
set_languages("c++23")
add_includedirs("include/")
add_includedirs("vendor/SDL3/include", {public = true})
add_includedirs("vendor/SDL3/include/build_config")
add_includedirs("vendor/SDL3/src/")
add_includedirs("vendor/SDL3/src/video/")
add_includedirs("vendor/SDL3/src/video/wayland")
set_pcxxheader("include/alt/SDL3.h")
--
add_defines("_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG")
add_cxxflags("-stdlib=libc++")  add_ldflags("-stdlib=libc++")
add_cxxflags(table.unpack(cxx_flags))
add_ldflags(table.unpack(ld_flags))


--- OPTIONS
OPT_backend="backend"
option(OPT_backend)
    set_default("wayland")
    set_values("x11", "wayland")
option_end()



--- TARGETS
target("vendor-sdl3")
    set_kind("static")
    set_languages("c")
    -- set_optimize("fastest")
    add_options("backend")
    add_cxflags("-fPIC", {force = true})

    add_defines("SDL_DYNAMIC_API=0")
    add_defines("SDL_VIDEO_RENDER_OGL_ES2=1")
    add_defines("SDL_VIDEO_OPENGL=0", "SDL_VIDEO_OPENGL_ES2=1")

    -- ============================================================
    -- Explicit list of every directory that is safe / required on Linux
    -- ============================================================
    add_files(
        -- force the Unix filesystem implementation
        "vendor/SDL3/src/filesystem/unix/SDL_sysfilesystem.c",
        "vendor/SDL3/src/core/linux/SDL_extra_stubs.c"
    )
    add_files("vendor/SDL3/src/video/SDL_egl.c")
    add_defines("SDL_VIDEO_OPENGL_EGL=1")
    add_files("vendor/SDL3/src/render/opengles2/*.c")
    add_syslinks("GLESv2")
    add_files("vendor/SDL3/src/core/linux/SDL_sysfilesystem_stubs.c")
    add_files(
        -- top-level core
        "vendor/SDL3/src/*.c",

        -- atomic / cpuinfo / events
        "vendor/SDL3/src/atomic/*.c",
        "vendor/SDL3/src/cpuinfo/*.c",
        "vendor/SDL3/src/events/*.c",

        -- filesystem (unix only)
        "vendor/SDL3/src/filesystem/unix/*.c",

        -- io (needed for the SDL_*IO symbols)
        "vendor/SDL3/src/io/*.c",
        "vendor/SDL3/src/io/generic/*.c",

        -- libm / loadso / locale / misc
        "vendor/SDL3/src/libm/*.c",
        "vendor/SDL3/src/loadso/dlopen/*.c",
        "vendor/SDL3/src/locale/unix/*.c",
        "vendor/SDL3/src/misc/*.c",
        "vendor/SDL3/src/misc/unix/*.c",

        -- main (callbacks)
        "vendor/SDL3/src/main/*.c",
        "vendor/SDL3/src/main/generic/*.c",

        -- power / process
        "vendor/SDL3/src/power/linux/*.c",
        "vendor/SDL3/src/process/posix/*.c",

        -- render (software is enough for now)
        "vendor/SDL3/src/render/*.c",
        "vendor/SDL3/src/render/software/*.c",

        -- stdlib / storage
        "vendor/SDL3/src/stdlib/*.c",
        "vendor/SDL3/src/storage/generic/*.c",

        -- thread / time / timer
        "vendor/SDL3/src/thread/pthread/*.c",
        "vendor/SDL3/src/time/unix/*.c",
        "vendor/SDL3/src/timer/unix/*.c",
        "vendor/SDL3/src/timer/*.c",

        -- tray
        "vendor/SDL3/src/tray/*.c",
        "vendor/SDL3/src/tray/unix/*.c",

        -- video core + yuv
        "vendor/SDL3/src/video/*.c",
        "vendor/SDL3/src/video/yuv2rgb/*.c",

        -- audio (dummy only)
        "vendor/SDL3/src/audio/*.c",
        "vendor/SDL3/src/audio/dummy/*.c",

        -- joystick / hidapi (linux + hidapi)
        "vendor/SDL3/src/joystick/*.c",
        "vendor/SDL3/src/joystick/linux/*.c",
        "vendor/SDL3/src/joystick/hidapi/*.c",
        "vendor/SDL3/src/hidapi/*.c",

        -- haptic / sensor / camera (dummy / disabled)
        "vendor/SDL3/src/haptic/dummy/*.c",
        "vendor/SDL3/src/sensor/*.c",
        "vendor/SDL3/src/sensor/dummy/*.c",
        "vendor/SDL3/src/camera/*.c",
        "vendor/SDL3/src/camera/dummy/*.c",

        -- dialog / messagebox helpers (zenity etc.)
        "vendor/SDL3/src/dialog/*.c",
        "vendor/SDL3/src/dialog/unix/*.c",

        "vendor/SDL3/src/core/linux/SDL_gtk_stubs.c",

        "vendor/SDL3/src/filesystem/*.c",          -- the common filesystem code
        "vendor/SDL3/src/filesystem/unix/*.c",     -- already there
        "vendor/SDL3/src/misc/*.c",                -- already there (GetAppID / GetExeName)
        "vendor/SDL3/src/locale/*.c",              -- already there (GetPreferredLocales)
        "vendor/SDL3/src/io/*.c",                  -- already there (IOReady)
        "vendor/SDL3/src/audio/dummy/*.c",         -- already there (DUMMY_bootstrap)

        "vendor/SDL3/src/video/dummy/*.c",

        "vendor/SDL3/src/core/linux/SDL_evdev.c",
        "vendor/SDL3/src/core/linux/SDL_evdev_capabilities.c",
        "vendor/SDL3/src/core/linux/SDL_evdev_kbd.c",
        "vendor/SDL3/src/core/linux/SDL_dbus.c",          -- keep only if you later enable DBus
        "vendor/SDL3/src/core/linux/SDL_ime.c",
        -- "vendor/SDL3/src/core/linux/SDL_system_theme.c",
        "vendor/SDL3/src/core/linux/SDL_threadprio.c",
        -- "vendor/SDL3/src/core/linux/SDL_sandbox.c",

        -- missing pieces that the linker is still asking for
        -- "vendor/SDL3/src/core/linux/*.c",          -- GTK helpers, linux thread priority, etc.
        "vendor/SDL3/src/thread/*.c",              -- common thread / TLS / condition / semaphore code
        "vendor/SDL3/src/joystick/dummy/*.c",      -- DUMMY_bootstrap / SDL_DUMMY_JoystickDriver
        "vendor/SDL3/src/process/*.c"              -- core process helpers (Crea
    )
    -- inside the wayland branch, after the add_files for wayland:

    -- ============================================================
    -- Video backend (only one)
    -- ============================================================
    if get_config("backend") == "wayland" then
        add_includedirs("vendor/SDL3/src/video/wayland/generated")
        add_files("vendor/SDL3/src/video/wayland/*.c")
        add_files("vendor/SDL3/src/video/wayland/generated/*.c")   -- ← this line
        add_defines(
            "HAVE_SIGTIMEDWAIT=1",
            "SDL_VIDEO_DRIVER_WAYLAND=1"
            -- do NOT define SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        )
        add_defines("SDL_VIDEO_DRIVER_WAYLAND_COLOR_MANAGEMENT=0")
        add_syslinks("wayland-client", "wayland-cursor", "wayland-egl", "xkbcommon", "EGL")
    else
        add_files("vendor/SDL3/src/video/x11/*.c")
        add_defines(
            "SDL_VIDEO_DRIVER_X11=1",
            "SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS=1",
            "SDL_VIDEO_DRIVER_X11_XCURSOR=1",
            "SDL_VIDEO_DRIVER_X11_XINPUT2=1",
            "SDL_VIDEO_DRIVER_X11_XRANDR=1",
            "SDL_VIDEO_DRIVER_X11_XFIXES=1",
            "SDL_VIDEO_DRIVER_X11_XSYNC=1"
        )
        add_syslinks("X11", "Xext", "Xrandr", "Xcursor", "Xi", "Xfixes", "Xss")
    end

    -- ============================================================
    -- Defines
    add_defines("SDL_VIDEO_RENDER_SW=1")
    add_defines(
        "SDL_STATIC=1",
        "SDL_VIDEO=1",
        "SDL_RENDER=1",
        "SDL_EVENTS=1",
        "SDL_TIMERS=1",
        "SDL_FILESYSTEM=1",
        "SDL_THREAD=1",
        "SDL_ATOMIC=1",
        "SDL_LOADSO=1",
        "SDL_CPUINFO=1",
        "SDL_LOCALE=1",
        "SDL_MISC=1",
        "SDL_POWER=1",
        "SDL_PROCESS=1",
        "SDL_AUDIO=1",
        "SDL_JOYSTICK=1",
        "SDL_HAPTIC=0",
        "SDL_SENSOR=0",
        "SDL_CAMERA=0",
        "SDL_GPU=0",
        "SDL_VULKAN=0",
        "SDL_OPENGL=1",
        "SDL_OPENGLES=1",
        "HAVE_LIBC=1",
        "HAVE_STDIO_H=1",
        "HAVE_STRING_H=1",
        "HAVE_CTYPE_H=1",
        "HAVE_MATH_H=1",
        "HAVE_SIGNAL_H=1",
        "HAVE_SETJMP_H=1",
        "HAVE_SYS_TYPES_H=1",
        "HAVE_PTHREAD=1",
        "HAVE_PTHREAD_SETNAME_NP=1",
        "HAVE_CLOCK_GETTIME=1",
        "HAVE_NANOSLEEP=1",
        "HAVE_GETPAGESIZE=1",
        "HAVE_MPROTECT=1",
        "HAVE_SEM_TIMEDWAIT=1",
        "SDL_THREAD_PTHREAD=1",
        "SDL_TIMER_UNIX=1",
        "SDL_FILESYSTEM_UNIX=1",
        "SDL_POWER_LINUX=1",
        "SDL_LOADSO_DLOPEN=1",
        "SDL_LOCALE_UNIX=1",
        "SDL_MISC_UNIX=1",
        "SDL_PROCESS_POSIX=1"
    )

    -- ============================================================
    -- Include paths
    -- ============================================================
    add_includedirs(
        "vendor/SDL3/include",
        "vendor/SDL3/include/build_config",
        "vendor/SDL3/src",
        "vendor/SDL3/src/video",
        "vendor/SDL3/src/video/wayland",
        "vendor/SDL3/src/render",
        "vendor/SDL3/src/events",
        "vendor/SDL3/src/stdlib",
        "vendor/SDL3/src/thread",
        "vendor/SDL3/src/timer",
        "vendor/SDL3/src/atomic",
        "vendor/SDL3/src/cpuinfo",
        "vendor/SDL3/src/filesystem",
        "vendor/SDL3/src/libm",
        "vendor/SDL3/src/loadso",
        "vendor/SDL3/src/locale",
        "vendor/SDL3/src/misc",
        "vendor/SDL3/src/power",
        "vendor/SDL3/src/process",
        "vendor/SDL3/src/audio",
        "vendor/SDL3/src/joystick",
        "vendor/SDL3/src/hidapi",
        "vendor/SDL3/src/haptic",
        "vendor/SDL3/src/sensor",
        "vendor/SDL3/src/storage",
        "vendor/SDL3/src/tray",
        "vendor/SDL3/src/io",
        "vendor/SDL3/src/main",
        "vendor/SDL3/src/camera",
        "vendor/SDL3/src/dialog"
    )

    add_syslinks("m", "dl", "pthread", "rt")
target_end()


target("cone")
    set_kind("shared")
    add_files("src/*.cpp")
    add_deps("vendor-sdl3")
    add_includedirs("include/", {public = true})
target_end()


-- TESTS
target("game")  add_files("tests/game.cpp")  add_deps("cone")
target("main")  add_files("tests/main.cpp")  add_deps("cone")
target("meter")  add_files("tests/meter.cpp")  add_deps("cone")
target("cstrlen")  add_files("tests/cstrlen.cpp")  add_deps("cone")
target("size")  add_files("tests/item_size.cpp")  add_deps("cone")
target("ref")  add_files("tests/ref.cpp")  add_deps("cone")
target("sdl3-wl")  add_files("tests/sdl3_wl.cpp")  add_deps("cone")
target("sdl")  add_files("tests/sdl3.cpp")  add_deps("cone")
target("bound")  add_files("tests/bound.cpp")  add_deps("cone")
target("time")  add_files("tests/time.cpp")  add_deps("cone")
target("entity")  add_files("tests/entity.cpp")  add_deps("cone")
