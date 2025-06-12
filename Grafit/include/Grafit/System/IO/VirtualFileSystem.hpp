#ifndef VIRTUALFILESYSTEM_HPP
#define VIRTUALFILESYSTEM_HPP

#include <Grafit/System/IO/IFileSystem.hpp>
#include <Grafit/System/SmartPtr.hpp>
#include <list>
#include <string>

namespace gf {

class FileSystem;
using FileSystemPtr = SharedPtr<FileSystem>;

class VirtualFileSystem : public IFileSystem {
public:
    VirtualFileSystem();

    void mount(FileSystemPtr fs);

    void mountDirectory(const std::string& path);

    void setWriteDirectory(const std::string& path);

    const std::string& getWriteDirectory() const;

    virtual bool exists(const std::string &filename) const override;

    virtual SharedPtr<IOStream> openRead(const std::string& filename) override;

    virtual SharedPtr<IOStream> openWrite(const std::string& filename) override;

    virtual SharedPtr<IOStream> open(const std::string& filename) override;

    virtual void remove(const std::string& filename) override;

private:
    using FileSystems = std::list<FileSystemPtr>;

    FileSystems m_systems;
};

using VirtualFileSystemPtr = SharedPtr<VirtualFileSystem>;

}
#endif // VIRTUALFILESYSTEM_HPP
