**tiny-fmt** is an open-source fork of {fmt} library, stripping heavy features into core utilities.
NOTE: header-only mode is deliberatly not supported

# Features

- Simple [format API](https://fmt.dev/latest/api/) with positional
  arguments for localization
- Implementation of [C++20
  std::format](https://en.cppreference.com/w/cpp/utility/format) and
  [C++23 std::print](https://en.cppreference.com/w/cpp/io/print)
- [Format string syntax](https://fmt.dev/latest/syntax/) similar
  to Python\'s
  [format](https://docs.python.org/3/library/stdtypes.html#str.format)
- Fast IEEE 754 floating-point formatter with correct rounding,
  shortness and round-trip guarantees using the
  [Dragonbox](https://github.com/jk-jeon/dragonbox) algorithm
- Portable Unicode support
- Safe [printf
  implementation](https://fmt.dev/latest/api/#printf-api)
  including the POSIX extension for positional arguments
- Extensibility: [support for user-defined
  types](https://fmt.dev/latest/api/#formatting-user-defined-types)
- High performance: faster than common standard library
  implementations of `(s)printf`, iostreams, `to_string` and
  `to_chars`, see [Speed tests](#speed-tests) and [Converting a
  hundred million integers to strings per
  second](https://vitaut.net/posts/2020/fast-int-to-string-revisited/)
- Safety: the library is fully type-safe, errors in format strings can
  be reported at compile time, automatic memory management prevents
  buffer overflow errors
- Ease of use: small self-contained code base, no external
  dependencies, permissive MIT
  [license](https://github.com/monjaris/tiny-fmt/blob/master/LICENSE)
- [Portability](https://fmt.dev/latest/#portability) with
  consistent output across platforms and support for older compilers
- Clean warning-free codebase even on high warning levels such as
  `-Wall -Wextra -pedantic`
- Locale independence by default

See the [documentation](https://fmt.dev) for more details.

# Examples

**Print to stdout** ([run](https://godbolt.org/z/Tevcjh))

``` c++
#include <tinyfmt/tfmt.hpp>

int main() {
  tfmt::println("Hello, World!");
}
```

**Format a string** ([run](https://godbolt.org/z/oK8h33))

``` c++
std::string s = tfmt::format("The answer is {}.", 42);
// s == "The answer is 42."
```

**Format a string using positional arguments**
([run](https://godbolt.org/z/Yn7Txe))

``` c++
std::string s = tfmt::format("I'd rather be {1} than {0}.", "light-weight", "feature-bloat");
// s == "I'd rather be light-weight than feature-bloat."
```


**Print a container** ([run](https://godbolt.org/z/MxM1YqjE7))

``` c++
#include <vector>
#include <tinyfmt/tfmt.hpp>

int main() {
  std::vector<int> v = {1, 2, 3};
  tfmt::print("{}\n", v);
}
```

Output:

    [1, 2, 3]

**Check a format string at compile time**

``` c++
std::string s = tfmt::format("{:d}", "I am not a number");
```

This gives a compile-time error in C++20 because `d` is an invalid
format specifier for a string.


This can be [up to 9 times faster than `fprintf`](
https://vitaut.net/posts/2020/optimal-file-buffer-size/).

**Print with colors and text styles**

``` c++
#include <tinyfmt/colors.hpp>

int main() {
  tfmt::print(fg(tfmt::color::crimson) | tfmt::emphasis::bold,
             "Hello, {}!\n", "world");
  tfmt::print(fg(tfmt::color::floral_white) | bg(tfmt::color::slate_gray) |
             tfmt::emphasis::underline, "Olá, {}!\n", "Mundo");
  tfmt::print(fg(tfmt::color::steel_blue) | tfmt::emphasis::italic,
             "你好{}！\n", "世界");
}
```


# Performance

tfmt can be tens of percent to 20–30 times faster than `sprintf` and
iostreams, especially for numeric formatting. It minimizes dynamic memory
allocations and can optionally [compile format strings](
https://fmt.dev/latest/api/#compile-api) into efficient formatting code.


`ostringstream` and `sprintf` are omitted because they are an order of
magnitude slower than the other methods.


# Projects already using tfmt
*vexa* - https://github.com/monjaris/vexa
*gshell* - https://github.com/gosti37/gshell
