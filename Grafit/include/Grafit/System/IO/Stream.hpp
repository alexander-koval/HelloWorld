#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

#include <cstdlib>
#include <Grafit/System/Types.hpp>
#include <Grafit/System/Destructable.hpp>
#include <Grafit/System/RefCounter.hpp>
#include <Grafit/System/NonCopyable.hpp>
#include <Grafit/System/Destructable.hpp>
#include <vector>

namespace gf {
enum class Origin {
    Begin,
    Current,
    End
};

class Seekable : public Destructable, public NonCopyable {
public:
    Seekable() : NonCopyable() {}

    virtual ~Seekable();

    virtual Int64 seek(Int64 position, Origin origin) = 0;

    virtual Int64 tell() = 0;

    virtual Int64 getSize(void) = 0;
};

class OutputStream;
class InputStream : virtual public Seekable {
public:
    virtual Int64 read(char* buffer, size_t size) = 0;

    virtual void readAll(std::vector<char>& buffer) = 0;

    virtual void readAll(OutputStream& stream) = 0;
};

class OutputStream : virtual public Seekable {
public:
    virtual void write(char* buffer, size_t size) = 0;

    virtual void writeAll(std::vector<char>& buffer) = 0;

    virtual void writeAll(InputStream& stream) = 0;
};

class IOStream : public InputStream, public OutputStream {};
}

#endif // INPUTSTREAM_HPP
