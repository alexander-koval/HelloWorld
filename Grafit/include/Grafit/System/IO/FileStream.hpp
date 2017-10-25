#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <string>
#include <Grafit/System/IO/IOStream.hpp>
#include <Grafit/System/NonCopyable.hpp>
#include <Grafit/System/SmartPtr.hpp>
#include <Grafit/System/RefCounter.hpp>
#include <fstream>

namespace gf {
class File;

class FileStream : public IOStream, public NonCopyable {
public:
    FileStream();

    virtual ~FileStream() override;

    void open(const gf::File* file);

    virtual void write(char* buffer, size_t size) override;

    virtual char* read(void) override;

    virtual Int64 seek(Int64 position) override;

    virtual Int64 tell(void) override;

    virtual Int64 getSize(void) override;

private:
    const gf::File* m_file;
    std::fstream m_stream;
};

using FileSreamPtr = gf::SmartPtr<FileStream>;

}

#endif // FILESTREAM_HPP
