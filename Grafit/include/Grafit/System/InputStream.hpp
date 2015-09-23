#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

#include <Grafit/System/Types.hpp>
#include <Grafit/System/IDestructable.hpp>

namespace gf {
class IInputStream : public Destructable {
public:
    virtual Int64 read(void* data, Int64 size) = 0;

    virtual Int64 seek(Int64 position) = 0;
    
    virtual Int64 tell(void) = 0;

    virtual Int64 getSize(void) = 0;
};

}

#endif // INPUTSTREAM_HPP
