#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <Grafit/System/IO/IFileSystem.hpp>
#include "Grafit/System/RefCounter.hpp"
#include <vector>
#include <string>

namespace gf {

class FileStream;
class FileSystem : public RefCounter, public IFileSystem {
public:
    FileSystem(const std::string& root);

    virtual bool exists(const std::string& filename) const override;

    virtual SmartPtr<IOStream> openRead(const std::string& filename) override;

    virtual SmartPtr<IOStream> openWrite(const std::string& filename) override;

    virtual SmartPtr<IOStream> open(const std::string& filename) override;

    virtual void remove(const std::string& filename) override;

private:
    std::string m_root;

};

using FileSystemPtr = gf::SmartPtr<FileSystem>;

}

#endif // FILESYSTEM_HPP
