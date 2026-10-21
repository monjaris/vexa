add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate")


--- CONFIG
add_cxxflags(table.unpack({
    "-std=c++23",
    "-Wall", "-Wextra",
    "-fno-exceptions", "-fno-rtti",
}))



--- TARGET
after_build(function (target)
    os.cp(target:targetfile(), "$(projectdir)/")
end)


target("tiny-fmt")
    set_kind("$(kind)")
    add_files("src/format.cpp")
    add_includedirs("include", {public = true})
    add_headerfiles("include/(**.hpp)")

    if is_kind("shared") then
        add_defines("TFMT_SHARED")
    else
        add_cxxflags("-fPIC")

        after_build(function (target)
            local targetfile = target:targetfile()
            local so_file = targetfile:match("^(.*)%.[^.]+$")..".so"
            os.rm(so_file)
        end)
    end

    if is_plat("windows") then
        add_cxxflags("/utf-8")
    end


--- TESTS
-- target("main") add_files("test/main.cpp") add_deps("tiny-fmt")
target("format") add_files("test/format.cpp") add_deps("tiny-fmt")
target("format_to") add_files("test/format_to.cpp") add_deps("tiny-fmt")
