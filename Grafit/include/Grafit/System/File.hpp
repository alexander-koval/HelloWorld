#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <Grafit/System/String.hpp>
#include <boost/filesystem/operations.hpp>

namespace gf {

class File {
public:
    enum Type {
        UNDEFINED = boost::filesystem::file_type::status_error,
        NOT_FOUND = boost::filesystem::file_type::file_not_found,
        FILE = boost::filesystem::file_type::regular_file,
        DIRECTORY = boost::filesystem::file_type::directory_file,
        SYMLINK = boost::filesystem::file_type::symlink_file,
        BLOCK = boost::filesystem::file_type::block_file,
        CHARACTER = boost::filesystem::file_type::character_file,
        FIFO = boost::filesystem::file_type::fifo_file,
        SOCKET = boost::filesystem::file_type::socket_file,
        REPARSE = boost::filesystem::file_type::reparse_file,
        UNKNOWN = boost::filesystem::file_type::type_unknown
    };

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

    float getSize(void) const;

    float getSpaceAvailable(void) const;

    File::Type getType(void) const;

public:
    static const String& Separator;

private:
    boost::filesystem::path m_path;
    boost::filesystem::file_status m_status;
};

} // namespace gf

#endif // FILE_HPP

