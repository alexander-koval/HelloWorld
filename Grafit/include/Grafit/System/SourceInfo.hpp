#ifndef SOURCEINFO_HPP
#define SOURCEINFO_HPP

#include <string>

#define GF_STRINGIFY(x) #x
#define GF_TOSTRING(x) GF_STRINGIFY(x)

#define GF_SOURCEINFO gf::SourceInfo(__FILE__, GF_TOSTRING(__LINE__), __FUNCTION__)

namespace gf {

class SourceInfo {
public:
    inline SourceInfo(const char* file, const char* line, const char* func)
        : m_file(file)
        , m_line(line)
        , m_func(func) { }

    inline const char* getFile(void) const { return m_file; }

    inline const char* getLine(void) const { return m_line; }

    inline const char* getFunc(void) const { return m_func; }

private:
    const char* m_file;
    const char* m_line;
    const char* m_func;

};

inline std::string operator+(const std::string& what, const SourceInfo& info) {
    return std::string(info.getFile()) + ':' + info.getLine() + ": " += what;
}

inline std::string operator+(const char* what, const SourceInfo& info) {
    return std::string(info.getFile()) + ':' + info.getLine() + ": " += what;
}

inline std::string operator+(const SourceInfo& info, const std::string& what) {
    return std::string(info.getFile()) + ':' + info.getLine() + ": " += what;
}

inline std::string operator+(const SourceInfo& info, const char* what) {
    return std::string(info.getFile()) + ':' + info.getLine() + ": " += what;
}

} // namespace gf

#endif // SOURCEINFO_HPP

