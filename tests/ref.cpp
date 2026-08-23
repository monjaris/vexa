#include "cone.hpp"

namespace mk = cone;

int main()
{
    int32 x = 10;
    constexpr int32 y = 10;

    mk::Ref<int> r1 = mk::Ref(x);
    mk::RefMut r2 = {x};

    CN_UNUSE(x, r1, r2);
}
