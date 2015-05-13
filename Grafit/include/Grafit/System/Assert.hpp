#ifndef ASSERT
#define ASSERT

#include <Grafit/System/SourceInfo.hpp>

#define GF_VA_NUM_ARGS(...) GF_VA_NUM_ARGS_HELPER(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define GF_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define GF_JOIN(x, y) x##y
#define GF_ASSERT_IMPL_VAR(variable) .variable(GF_STRINGIFY(variable), variable)
#define GF_ASSERT(condition, format, ...) \
    if (!condition) {\
        gf::Assert(GF_SOURCEINFO, "Assertion \"" #condition "\" failed. ", __VA_ARGS__); \
    }

namespace gf {

class Assert {
public:
    Assert(const SourceInfo& sourceInfo, const char* format, ...);

    Assert& variable(const char* const name, bool value);

    Assert& variable(const char* const name, char value);

    Assert& variable(const char* const name, short value);

    Assert& variable(const char* const name, int value);

    template <typename T>
    Assert& variable(const char* const name, const T& value);
};

}


#endif // ASSERT

