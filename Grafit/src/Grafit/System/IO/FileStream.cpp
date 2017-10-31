#include <Grafit/System/IO/FileStream.hpp>
#include <Grafit/System/Assert.hpp>

namespace gf {

FileStream::FileStream()
    : m_size(), m_path(), m_stream() {

}

FileStream::~FileStream() {
    if (m_stream.is_open()) {
        m_stream.close();
    }
}

void FileStream::open(File&& file) {
    open(file);
}

void FileStream::open(const gf::File& file) {
    m_size = file.getSize();
    m_path = file.getNativePath();
    if (m_stream.is_open()) {
        m_stream.close();
    }
    m_stream.open(m_path, std::ios_base::binary | std::ios_base::in | std::ios_base::out);
}

void FileStream::readAll(std::vector<char>& buffer) {
    m_stream.seekg(0, std::ios::end);
    std::fstream::pos_type pos = m_stream.tellg();
    std::streamsize length = pos;
    m_stream.seekg(0, std::ios::beg);
    buffer.resize(static_cast<std::size_t>(length));
    m_stream.read(&buffer[0], length);

}

void FileStream::writeAll(std::vector<char>& buffer) {
    if (!buffer.empty()) {
        write(&buffer.front(), buffer.size());
    }
}

void FileStream::write(char* buffer, std::size_t size) {
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_path.c_str());
    m_stream.write(buffer, static_cast<std::streamsize>(size));
    m_stream.flush();
}

Int64 FileStream::read(char* buffer, std::size_t size) {
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_path.c_str());
    m_stream.read(buffer, static_cast<std::streamsize>(size));
    return m_stream.gcount();
}

Int64 FileStream::seek(Int64 position) {
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_path.c_str());
    m_stream.seekg(position, std::ios_base::beg);
    std::ios_base::iostate state = m_stream.rdstate();
    GF_ASSERT(state == std::ios_base::goodbit, "Failed to set the file position", static_cast<int>(state));
    return tell();
}

Int64 FileStream::tell() {
    GF_ASSERT(m_stream.is_open(), "File does not opened", m_path.c_str());
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
