#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <Grafit/System/String.hpp>
#include <boost/filesystem/operations.hpp>

namespace gf {

class File {
public:
    File(const String& path);

    ~File(void);

    bool isExist(void) const;

    bool isDirectory(void) const;

    bool isHidden(void) const;

    bool isSymbolicLink(void) const;

    bool isRegularFile(void) const;

    String getName(void) const;

    String getExtension(void) const;

    String getNativePath(void) const;

    const File& getParent(void) const;

    static String getSeparator(void);

    float getSize(void) const;

    float getSpaceAvailable(void) const;

    String getType(void) const;

private:
    boost::filesystem::path m_path;
    boost::filesystem::file_status m_status;
};

} // namespace gf

#endif // FILE_HPP

