#ifndef OUTPUTSTREAM_HPP
#define OUTPUTSTREAM_HPP

#include <Grafit/System/Types.hpp>
#include <Grafit/System/Destructable.hpp>

namespace gf {

class OutputStream : public Destructable {
public:
    virtual void write(char* buffer, std::size_t length) = 0;

    virtual Int64 seek(Int64 position) = 0;

    virtual Int64 tell(void) = 0;

    virtual Int64 getSize(void) = 0;
};

}

#endif // OUTPUTSTREAM_HPP
