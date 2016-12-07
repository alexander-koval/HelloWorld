#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <string>
#include <Grafit/System/InputStream.hpp>
#include <Grafit/System/NonCopyable.hpp>
#include <fstream>

namespace gf {
class File;
class FileStream : public IInputStream, NonCopyable {
public:
    FileStream();

    virtual ~FileStream();

    void open(gf::File* file);

    virtual void* read(void);

    virtual Int64 seek(Int64 position);

    virtual Int64 tell(void);

    virtual Int64 getSize(void);

private:
    gf::File* m_file;
    std::fstream m_stream;
};

}

#endif // FILESTREAM_HPP
