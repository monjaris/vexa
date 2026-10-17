#include <cstdlib>  // for ::exit()
#include "tinyfmt/tfmt.hpp"
#include <string>

int main()
{
    char buffer[120];
    auto [buffer_end, buffer_err] = tfmt::format_to(buffer, "{}, {}, {}", 1, 2, 3);

    int val;
    tfmt::vformat("{}", tfmt::make_format_args(val));

    if (buffer_err) {
        tfmt::println("failed to do formatting!");
        ::exit(1);
    }

    // construct a string_view out of formatted buffer
    tfmt::string_view sv = {buffer, tfmt::usize(buffer_end - buffer)};

    tfmt::println("{{{}}}", sv);
    // {1, 2, 3}
}
