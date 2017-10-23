#ifndef IFILESYSTEM_HPP
#define IFILESYSTEM_HPP

#include <vector>
#include <string>
#include <Grafit/System/Destructable.hpp>
#include <Grafit/System/IO/InputStream.hpp>
#include <Grafit/System/SmartPtr.hpp>
#include <Grafit/System/Path.hpp>

namespace gf {

class IFileSystem : public Destructable
{
public:
    const std::string& getRoot() const;

    virtual bool exists(const std::string& filename) const = 0;

//    virtual SmartPtr<InputStream> openRead(const std::string& filename) = 0;

//    virtual SmartPtr<OutputStream> openWrite(const std::string& filename) = 0;

//    virtual SmartPtr<IStream> open(const std::string& filename) = 0;

    virtual void remove(const std::string& filename) = 0;
};

}
#endif // FILESYSTEM_HPP
