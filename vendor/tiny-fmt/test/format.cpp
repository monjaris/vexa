#include <string>
#include "tinyfmt/tfmt.hpp"

int main()
{
    tfmt::println("{}", 1);
    tfmt::println("{}", tfmt::format("{:.3}", 1.2345));  // 1.23
}
