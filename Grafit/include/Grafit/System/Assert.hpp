#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <Grafit/System/SourceInfo.hpp>
#include <sstream>
#include <cstring>
#include <iostream>
#include <cassert>

#define GF_ASSERT_IMPL_VAR(value) .variable(GF_STRINGIFY(value), value)
#define GF_ASSERT_IMPL_VARS(...) GF_EXPAND_ARGS(GF_ASSERT_IMPL_VAR, __VA_ARGS__)

#define GF_ASSERT_IMPL(condition, message, ...) do { \
    if (!(condition)) { \
        if (GF_VA_NUM_ARGS_EMPTY(__VA_ARGS__)) \
            (gf::Assert(GF_SOURCEINFO, "Assertion \"" #condition "\" failed. ", message))(); \
        else \
            (gf::Assert(GF_SOURCEINFO, "Assertion \"" #condition "\" failed. ", message, GF_VA_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)GF_ASSERT_IMPL_VARS(__VA_ARGS__))(); \
        assert(condition); \
    } } while(0)

#define GF_ASSERT_1(condition) GF_ASSERT_IMPL(condition, "", nullptr)
#define GF_ASSERT_2(condition, ...) GF_ASSERT_IMPL(condition, "", __VA_ARGS__)
#define GF_ASSERT_3(condition, message, ...) GF_ASSERT_IMPL(condition, message, __VA_ARGS__)
#define GF_ASSERT(...) GF_JOIN(GF_ASSERT_, GF_VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

namespace gf {
class String;
class Assert {
public:
    Assert(const SourceInfo& sourceInfo, const char* assertion_info, const char* message = "", ...);

    Assert& variable(const char* const name, bool value);

    Assert& variable(const char* const name, char value);

    Assert& variable(const char* const name, const std::string& value);

    Assert& variable(const char* const name, const gf::String& value);

    Assert& variable(const char* const name, const char* value);

    Assert& variable(const char* const name, short value);

    Assert& variable(const char* const name, unsigned short value);

    Assert& variable(const char* const name, int value);

    Assert& variable(const char* const name, long value);

    Assert& variable(const char* const name, std::nullptr_t value);

    template <typename T>
    Assert& variable(const char* const name, const T& value);

    void operator ()(void) const;


private:
    std::ostringstream m_os;
    SourceInfo m_sourceInfo;
};

}

#endif // ASSERT_HPP

