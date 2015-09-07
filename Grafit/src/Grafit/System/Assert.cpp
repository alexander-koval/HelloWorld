#include <Grafit/System/Assert.hpp>
#include <cassert>
#include <sstream>
#include <cstring>

namespace gf {

Assert::Assert(const SourceInfo& sourceInfo, const char* assertion_info, const char* message, ...)
    : m_os()
    , m_sourceInfo(sourceInfo) {
    m_os << assertion_info;
    m_os << "Reason: " << message;
    m_os << "\n\tFILE: " << m_sourceInfo.getFile();
    m_os << "\n\tLINE: " << m_sourceInfo.getLine();
    m_os << "\n\tFUNC: " << m_sourceInfo.getFunc();
}

Assert& Assert::variable(const char* const name, bool value) {
    m_os << "\n\t" << name << " " << value;
    return *this;
}

Assert& Assert::variable(const char* const name, char value) {
    m_os << "\n\t" << name << " " << value;
    return *this;
}

Assert& Assert::variable(const char* const name, const char* value) {
    m_os << "\n\t" << name << " " << value;
    return *this;
}

Assert& Assert::variable(const char* const name, short value) {
    m_os << "\n\t" << name << " " << value;
    return *this;
}

Assert& Assert::variable(const char* const name, int value) {
    m_os << "\n\tVariable: " << name << " " << value;
    return *this;
}

Assert& Assert::variable(const char* const name, long value) {
    m_os << "\n\tVariable: " << name << " " << value;
    return *this;
}

Assert& Assert::variable(const char* const name, std::nullptr_t value) {
    m_os << "\n\tVariable: " << name << " " << static_cast<void*>(value);
    return *this;
}

template <typename T>
Assert& Assert::variable(const char* const name, const T& value) {
    variable(name, value);
}

void Assert::operator ()(void) const {
    std::cerr << m_os.str() << std::endl;
}

}

