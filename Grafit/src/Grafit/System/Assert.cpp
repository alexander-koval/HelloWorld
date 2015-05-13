#include <Grafit/System/Assert.hpp>
#include <cstdarg>

namespace gf {

Assert::Assert(const SourceInfo& sourceInfo, const char* format, ...) {
    va_list ap;
//    va_start(ap, GF_VA_NUM_ARGS(...));
//    int kkk = 0;
}

Assert& Assert::variable(const char* const name, bool value) {
    return *this;
}

Assert& Assert::variable(const char* const name, char value) {
    return *this;
}

Assert& Assert::variable(const char* const name, short value) {
    return *this;
}

template <typename T>
Assert& Assert::variable(const char* const name, const T& value) {
    variable(name, value);
}


}

