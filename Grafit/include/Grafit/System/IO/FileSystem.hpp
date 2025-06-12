#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <Grafit/System/IO/IFileSystem.hpp>
#include "Grafit/System/RefCounter.hpp"
#include <vector>
#include <string>

namespace gf {

class FileStream;
class FileSystem : public IFileSystem {
public:
    FileSystem(const std::string& root);

    virtual bool exists(const std::string& filename) const override;

    virtual SharedPtr<IOStream> openRead(const std::string& filename) override;

    virtual SharedPtr<IOStream> openWrite(const std::string& filename) override;

    virtual SharedPtr<IOStream> open(const std::string& filename) override;

    virtual void remove(const std::string& filename) override;

    const std::string& getRoot() const { return m_root; };

private:
    std::string m_root;

};

using FileSystemPtr = gf::SharedPtr<FileSystem>;

}

#endif // FILESYSTEM_HPP
