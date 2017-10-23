#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <Grafit/System/Path.hpp>
#include <Grafit/System/Types.hpp>

namespace gf {
class FileImpl;

class File {
public:
    File(const std::string& path);

    File(const Path& path);

    ~File(void);

    bool isExist(void) const;

    bool isDirectory(void) const;

    bool isHidden(void) const;

    bool isSymbolicLink(void) const;

    bool isRegularFile(void) const;

    std::string getName(void) const;

    std::string getExtension(void) const;

    std::string getNativePath(void) const;

    Uint64 getSize(void) const;

    float getSpaceAvailable(void) const;

    void remove();

public:
    static const char Separator;

private:
    FileImpl* m_pimpl;
};

} // namespace gf

#endif // FILE_HPP

