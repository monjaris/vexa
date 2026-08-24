#include "vexa.hpp"

namespace mk = vexa;

int main()
{
    int32 x = 10;
    constexpr int32 y = 10;

    mk::Ref<int> r1 = mk::Ref(x);
    mk::RefMut r2 = {x};

    VX_UNUSE(x, r1, r2);
}
