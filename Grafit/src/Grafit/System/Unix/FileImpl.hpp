#ifndef FILEIMPL_HPP
#define FILEIMPL_HPP

#include <Grafit/System/Types.hpp>
#include <Grafit/System/Path.hpp>
#include <string>

namespace gf {

class FileImpl {
public:
    using FileSizeImpl = Uint64;

    FileImpl();

    FileImpl(const std::string &path);

    virtual ~FileImpl();

    void swapImpl(FileImpl &file);

    void setPathImpl(const std::string &path);

    const std::string &getPathImpl() const;

    bool existsImpl() const;

    bool canReadImpl() const;

    bool canWriteImpl() const;

    bool canExecuteImpl() const;

    bool isFileImpl() const;

    bool isDirectoryImpl() const;

    bool isLinkImpl() const;

    bool isDeviceImpl() const;

    bool isHiddenImpl() const;

    FileSizeImpl getSizeImpl() const;

    void setSizeImpl(FileSizeImpl size);

    void setWriteableImpl(bool flag = true);

    void setExecutableImpl(bool flag = true);

    void copyToImpl(const std::string &path) const;

    void renameToImpl(const std::string &path);

    void removeImpl();

    bool createFileImpl();

    bool createDirectoryImpl();

    std::string getName() const;

    std::string getExtension() const;

    FileSizeImpl totalSpaceImpl() const;

    FileSizeImpl usableSpaceImpl() const;

    FileSizeImpl freeSpaceImpl() const;

    static void handleLastErrorImpl(const std::string& path);

private:
    std::string m_path;
};

}
#endif // FILEIMPL_HPP
