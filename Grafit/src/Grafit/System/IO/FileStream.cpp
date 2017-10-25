#include <Grafit/System/IO/FileStream.hpp>
#include <Grafit/System/Assert.hpp>
#include <Grafit/System/File.hpp>

namespace gf {

FileStream::FileStream() : m_file(nullptr) {

}

FileStream::~FileStream() {
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

void FileStream::open(const gf::File *file) {
    m_file = file;
    if (m_stream.is_open()) {
        m_stream.close();
    }
    const std::string& name(file->getNativePath());
    m_stream.open(name, std::ios_base::binary | std::ios_base::in);
}

void FileStream::write(char* buffer, std::size_t size) {
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_file->getName().c_str());
    m_stream.write(buffer, static_cast<std::streamsize>(size));
    m_stream.flush();
}

char* FileStream::read(void) {
    Uint64 size = m_file->getSize();
    char* buffer = new char[size];
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_file->getName().c_str());
    seek(0);
    m_stream.read(buffer, static_cast<std::streamsize>(m_file->getSize()));
    return buffer;
}

Int64 FileStream::seek(Int64 position) {
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_file->getName().c_str());
    m_stream.seekg(position, std::ios_base::beg);
    std::ios_base::iostate state = m_stream.rdstate();
    GF_ASSERT(state == std::ios_base::goodbit, "Failed to set the file position", static_cast<int>(state));
    return tell();
}

Int64 FileStream::tell() {
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_file->getName().c_str());
    return m_stream.tellg();
}

Int64 FileStream::getSize() {
    if (m_stream.is_open()) {
        Int64 position = tell();
        m_stream.seekg(0, std::ios_base::end);
        Int64 size = tell();
        seek(position);
        return size;
    }
    return -1;
}

}
