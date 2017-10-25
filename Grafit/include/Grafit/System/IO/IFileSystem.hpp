#ifndef IFILESYSTEM_HPP
#define IFILESYSTEM_HPP

#include <vector>
#include <string>
#include <Grafit/System/Destructable.hpp>
#include <Grafit/System/IO/IOStream.hpp>
#include <Grafit/System/SmartPtr.hpp>
#include <Grafit/System/Path.hpp>

namespace gf {

class IFileSystem : public Destructable
{
public:
    const std::string& getRoot() const;

    virtual bool exists(const std::string& filename) const = 0;

    virtual SmartPtr<IOStream> openRead(const std::string& filename) = 0;

    virtual SmartPtr<IOStream> openWrite(const std::string& filename) = 0;

    virtual SmartPtr<IOStream> open(const std::string& filename) = 0;

    virtual void remove(const std::string& filename) = 0;
};

}
#endif // FILESYSTEM_HPP
