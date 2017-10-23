#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <string>
#include <Grafit/System/IO/InputStream.hpp>
#include <Grafit/System/NonCopyable.hpp>
#include <Grafit/System/SmartPtr.hpp>
#include <fstream>

namespace gf {
class File;

class FileInputStream : public InputStream, NonCopyable {
public:
    FileInputStream();

    virtual ~FileInputStream() override;

    void open(const gf::File* file);

    virtual void* read(void) override;

    virtual Int64 seek(Int64 position) override;

    virtual Int64 tell(void) override;

    virtual Int64 getSize(void) override;

private:
    const gf::File* m_file;
    std::fstream m_stream;
};

}

#endif // FILESTREAM_HPP
