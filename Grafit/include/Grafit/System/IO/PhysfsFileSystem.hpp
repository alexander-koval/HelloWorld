#ifndef PHYSFSFILESYSTEM_HPP
#define PHYSFSFILESYSTEM_HPP

#include <Grafit/System/IO/FileSystem.hpp>

namespace gf {

class PhysfsFileSystem : public FileSystem {
public:
    PhysfsFileSystem(const std::string& root);

    virtual ~PhysfsFileSystem() override;

    void mount(const std::string& path, const std::string& mountPoint, bool appendToEnd = true);

    bool exists(const std::string& filename) const override;

    virtual SharedPtr<IOStream> openRead(const std::string& filename) override;

    virtual SharedPtr<IOStream> openWrite(const std::string& filename) override;

    virtual SharedPtr<IOStream> open(const std::string& filename) override;

    virtual void remove(const std::string& filename) override;
};

using PhysfsFileSystemPtr = gf::SharedPtr<PhysfsFileSystem>;

}

#endif // PHYSFSFILESYSTEM_HPP
