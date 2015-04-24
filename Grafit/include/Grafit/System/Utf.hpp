#ifndef UTF_HPP
#define UTF_HPP

#include <algorithm>
#include <locale>
#include <string>
#include <cstdlib>
#include <Grafit/System/Types.hpp>


template <unsigned int N>
class Utf;

template <>
class Utf<8> {
public:

    template <typename In>
    static In decode(In begin, In end, Uint32& output, Uint32 replacement = 0);

    template <typename Out>
    static Out encode(Uint32 input, Out output, Uint8 replacement = 0);

    template <typename In>
    static In next(In begin, In end);

    template <typename In>
    static std::size_t count(In begin, In end);

    template <typename In, typename Out>
    static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale());

    template <typename In, typename Out>
    static Out fromWide(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out fromLatin1(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale& locale = std::locale());

    template <typename In, typename Out>
    static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

    template <typename In, typename Out>
    static Out toLatin1(In begin, In end, Out output, char replacement = 0);

    template <typename In, typename Out>
    static Out toUtf8(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toUtf16(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toUtf32(In begin, In end, Out output);
};

template <>
class Utf<16> {
public:

    template <typename In>
    static In decode(In begin, In end, Uint32& output, Uint32 replacement = 0);

    template <typename Out>
    static Out encode(Uint32 input, Out output, Uint16 replacement = 0);

    template <typename In>
    static In next(In begin, In end);

    template <typename In>
    static std::size_t count(In begin, In end);

    template <typename In, typename Out>
    static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale());

    template <typename In, typename Out>
    static Out fromWide(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out fromLatin1(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale& locale = std::locale());

    template <typename In, typename Out>
    static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

    template <typename In, typename Out>
    static Out toLatin1(In begin, In end, Out output, char replacement = 0);

    template <typename In, typename Out>
    static Out toUtf8(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toUtf16(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toUtf32(In begin, In end, Out output);
};

template <>
class Utf<32> {
public:

    template <typename In>
    static In decode(In begin, In end, Uint32& output, Uint32 replacement = 0);

    template <typename Out>
    static Out encode(Uint32 input, Out output, Uint32 replacement = 0);

    template <typename In>
    static In next(In begin, In end);

    template <typename In>
    static std::size_t count(In begin, In end);

    template <typename In, typename Out>
    static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale());

    template <typename In, typename Out>
    static Out fromWide(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out fromLatin1(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale& locale = std::locale());

    template <typename In, typename Out>
    static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

    template <typename In, typename Out>
    static Out toLatin1(In begin, In end, Out output, char replacement = 0);

    template <typename In, typename Out>
    static Out toUtf8(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toUtf16(In begin, In end, Out output);

    template <typename In, typename Out>
    static Out toUtf32(In begin, In end, Out output);

    template <typename In>
    static Uint32 decodeAnsi(In input, const std::locale& locale = std::locale());

    template <typename In>
    static Uint32 decodeWide(In input);

    template <typename Out>
    static Out encodeAnsi(Uint32 codepoint, Out output, char replacement = 0, const std::locale& locale = std::locale());

    template <typename Out>
    static Out encodeWide(Uint32 codepoint, Out output, wchar_t replacement = 0);
};

#include <Grafit/System/Utf.inl>

typedef Utf<8>  Utf8;
typedef Utf<16> Utf16;
typedef Utf<32> Utf32;



#endif // UTF_HPP
