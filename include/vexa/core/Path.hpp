#include <string>
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)

class VX_NODISCARD Path {
    using CharT = char;
    using ValueT = std::basic_string<CharT>;

    ValueT m_path = {};

public:
    Path() = default;
    ~Path() = default;

    Path(const CharT* path): m_path() {}

    auto value() { return m_path; }

    Path& append(const CharT* str) { m_path.append(str);  return *this; }
    Path& append(const CharT ch) { m_path += ch;  return *this; }
};

NAMESPACE_END(vexa)
