#include <Grafit/System/Assert.hpp>
#include <cstdarg>

namespace gf {

Assert::Assert(const SourceInfo& sourceInfo, const char* format, ...) {

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

Assert& Assert::variable(const char* const name, int value) {
    return *this;
}

template <typename T>
Assert& Assert::variable(const char* const name, const T& value) {
    variable(name, value);
}


}

