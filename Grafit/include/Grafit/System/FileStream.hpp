#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <string>
#include <Grafit/System/InputStream.hpp>
#include <Grafit/System/NonCopyable.hpp>

namespace gf {
class File;
class FileStream : public IInputStream, NonCopyable {
public:
    FileStream(const gf::File& file);

    virtual ~FileStream();

    virtual void* read(void);

    virtual Int64 seek(Int64 position);

    virtual Int64 tell(void);

    virtual Int64 getSize(void);

private:
    std::FILE* m_file;
    const gf::File& m_fileInfo;
};

}

#endif // FILESTREAM_HPP
