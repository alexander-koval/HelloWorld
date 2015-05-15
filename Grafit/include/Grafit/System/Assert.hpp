#ifndef ASSERT
#define ASSERT

#include <Grafit/System/SourceInfo.hpp>

#define GF_ASSERT_IMPL_VAR(value) .variable(GF_STRINGIFY(value), value)
#define GF_ASSERT_IMPL_VARS(...) GF_EXPAND_ARGS(GF_ASSERT_IMPL_VAR, __VA_ARGS__)

#define GF_ASSERT(condition, format, ...) do {  \
    if (!condition) { \
            (gf::Assert(GF_SOURCEINFO, "Assertion \"" #condition "\" failed. ", __VA_ARGS__) GF_ASSERT_IMPL_VARS(__VA_ARGS__)); \
    } } while(0)


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

