#include <memory>

template<class T, class U=std::default_delete<T>>
using Uptr = std::unique_ptr<T, U>;
