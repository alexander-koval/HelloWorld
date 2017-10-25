#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

#include <cstdlib>
#include <Grafit/System/Types.hpp>
#include <Grafit/System/Destructable.hpp>
#include <Grafit/System/RefCounter.hpp>

namespace gf {
class IOStream : public Destructable, public RefCounter {
public:
    virtual void write(char* buffer, size_t size) = 0;

    virtual char* read(void) = 0;

    virtual Int64 seek(Int64 position) = 0;
    
    virtual Int64 tell(void) = 0;

    virtual Int64 getSize(void) = 0;
};

}

#endif // INPUTSTREAM_HPP
