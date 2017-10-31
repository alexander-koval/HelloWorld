#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

#include <cstdlib>
#include <Grafit/System/Types.hpp>
#include <Grafit/System/Destructable.hpp>
#include <Grafit/System/RefCounter.hpp>
#include <vector>

namespace gf {
class IOStream : public Destructable {
public:
    virtual void readAll(std::vector<char>& buffer) = 0;

    virtual void writeAll(std::vector<char>& buffer) = 0;

    virtual Int64 read(char* buffer, size_t size) = 0;

    virtual void write(char* buffer, size_t size) = 0;

    virtual Int64 seek(Int64 position) = 0;
    
    virtual Int64 tell(void) = 0;

    virtual Int64 getSize(void) = 0;
};
}

#endif // INPUTSTREAM_HPP
