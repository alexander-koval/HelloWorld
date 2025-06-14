#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <string>
#include <Grafit/System/IO/Stream.hpp>
#include <Grafit/System/NonCopyable.hpp>
#include <Grafit/System/SmartPtr.hpp>
#include <Grafit/System/RefCounter.hpp>
#include <Grafit/System/File.hpp>
#include <fstream>

namespace gf {
class File;

class FileStream : public IOStream {
public:
    FileStream();

    virtual ~FileStream() override;

    void open(gf::File&& file);

    void open(const gf::File& file);

    virtual void readAll(std::vector<char>& buffer) override;

    virtual void readAll(OutputStream& stream) override;

    virtual void writeAll(std::vector<char>& buffer) override;

    virtual void writeAll(InputStream& stream) override;

    virtual Int64 read(char* buffer, size_t size) override;

    virtual void write(char* buffer, size_t size) override;

    virtual Int64 seek(Int64 position, Origin origin) override;

    virtual Int64 tell(void) override;

    virtual Int64 getSize(void) override;

private:
    Uint64 m_size;
    std::string m_path;
    std::fstream m_stream;
};

using FileSreamPtr = SharedPtr<FileStream>;

}

#endif // FILESTREAM_HPP
