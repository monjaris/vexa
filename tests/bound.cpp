#include <vector>
#include <csetjmp>
#include <csignal>
#include "vexa.hpp"

#define TEST_TEMPLATE  "TEST {}(): - {}"

namespace mk = vexa;
constexpr const char* bool_to_msg(bool status);
static sigjmp_buf jump_env;
void bounds_signal_handler(int);

static const char* array_bounds_name;
static const char* stdVector_bounds_name;

bool array_bounds() {
    array_bounds_name = __func__;

    constexpr auto MAXIMUM = 24;
    constexpr auto VIOLATE = 25;

    int arr[MAXIMUM];
    arr[VIOLATE] = 1;

    return true;
}

bool stdVector_bounds() {
    stdVector_bounds_name = __func__;
    ::signal(SIGABRT, bounds_signal_handler);

    using TYPE = int32;
    constexpr auto MAXIMUM = 24;
    constexpr auto VIOLATE = 25;

    if (sigsetjmp(jump_env, 1) == 0)
    {
        auto vec = std::vector<TYPE>(MAXIMUM);
        vec[VIOLATE] = 1;

        return true;
    }

    return false;
}


int main()
{
    auto test1 = array_bounds();
    auto test2 = stdVector_bounds();

    mk::log::info(TEST_TEMPLATE, array_bounds_name, bool_to_msg(test1));
    mk::log::info(TEST_TEMPLATE, stdVector_bounds_name, bool_to_msg(test2));
}


constexpr const char* bool_to_msg(bool status) {
    return (status)?
        ("\033[32m[SUCCESS]\033[0m")
    :
        ("\033[31m[FAILURE]\033[0m")
    ;
}

void bounds_signal_handler(int) {
    siglongjmp(jump_env, 1);
}
