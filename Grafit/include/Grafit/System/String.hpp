#ifndef STRING_HPP
#define STRING_HPP

#include <Grafit/System/Utf.hpp>
#include <locale>
#include <string>

namespace gf {

class String {
public:

    typedef std::basic_string<Uint32>::iterator       Iterator;      ///< Iterator type
    typedef std::basic_string<Uint32>::const_iterator ConstIterator; ///< Read-only iterator type

    static const std::size_t InvalidPos; ///< Represents an invalid position in the string

    String();

    String(char ansiChar, const std::locale& locale = std::locale());

    String(wchar_t wideChar);

    String(Uint32 utf32Char);

    String(const char* ansiString, const std::locale& locale = std::locale());

    String(const std::string& ansiString, const std::locale& locale = std::locale());

    String(const wchar_t* wideString);

    String(const std::wstring& wideString);

    String(const Uint32* utf32String);

    String(const std::basic_string<Uint32>& utf32String);

    String(const String& copy);

    template <typename T>
    static String fromUtf8(T begin, T end);

    template <typename T>
    static String fromUtf16(T begin, T end);

    template <typename T>
    static String fromUtf32(T begin, T end);

    operator std::string() const;

    operator std::wstring() const;

    std::string toAnsiString(const std::locale& locale = std::locale()) const;

    std::wstring toWideString() const;

    std::basic_string<Uint8> toUtf8() const;

    std::basic_string<Uint16> toUtf16() const;

    std::basic_string<Uint32> toUtf32() const;

    String& operator =(const String& right);

    String& operator +=(const String& right);

    Uint32 operator [](std::size_t index) const;

    Uint32& operator [](std::size_t index);

    void clear();

    std::size_t getSize() const;

    bool isEmpty() const;

    void erase(std::size_t position, std::size_t count = 1);

    void insert(std::size_t position, const String& str);

    std::size_t find(const String& str, std::size_t start = 0) const;

    void replace(std::size_t position, std::size_t length, const String& replaceWith);

    void replace(const String& searchFor, const String& replaceWith);

    String substring(std::size_t position, std::size_t length = InvalidPos) const;

    const Uint32* getData() const;

    Iterator begin();

    ConstIterator begin() const;

    Iterator end();

    ConstIterator end() const;

private:

    friend bool operator ==(const String& left, const String& right);
    friend bool operator <(const String& left, const String& right);

    std::basic_string<Uint32> m_string; ///< Internal string of UTF-32 characters
};

bool operator ==(const String& left, const String& right);

bool operator !=(const String& left, const String& right);

bool operator <(const String& left, const String& right);

bool operator >(const String& left, const String& right);

bool operator <=(const String& left, const String& right);

bool operator >=(const String& left, const String& right);

String operator +(const String& left, const String& right);

#include <Grafit/System/String.inl>

}
#endif // STRING_HPP
