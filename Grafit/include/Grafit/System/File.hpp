#ifndef FILE_HPP
#define FILE_HPP

#include <string>

namespace gf {

class File {
public:
    File(const std::string& path);

    ~File(void);

    bool isExist(void) const;

    bool isDirectory(void) const;

    bool isHidden(void) const;

    bool isSymbolicLink(void) const;

    bool isRegularFile(void) const;

    const std::string& getName(void) const;

    const std::string& getExtension(void) const;

    const std::string& getNativePath(void) const;

    const File& getParent(void) const;

    const std::string& getSeparator(void) const;

    float getSize(void) const;

    float getSpaceAvailable(void) const;

    const std::string& getType(void) const;
};

} // namespace gf

#endif // FILE_HPP

