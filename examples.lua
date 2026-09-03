-- All VEXA example files


examples = {
    "ping-pong",  -- by @gitduck6
    "block-stacker",  -- by @abdulrahman-103
    "snake", -- by @btwmarcel
}


for _,name in ipairs(examples) do
    target(name)
    set_kind("binary")
    add_files("examples/".. name ..".cpp")
    add_deps("vexa")
    target_end()
end
