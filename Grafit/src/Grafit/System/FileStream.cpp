#include <Grafit/System/FileStream.hpp>
#include <Grafit/System/Assert.hpp>
#include <Grafit/System/File.hpp>

namespace gf {

FileStream::FileStream(const gf::File& file) : m_file(nullptr), m_fileInfo(file) {
    if (m_file) { delete m_file; }
    const std::string& name(file.getNativePath());
    m_file = std::fopen(name.c_str(), "rb");
}

FileStream::~FileStream() {
    if (m_file) {
        std::fclose(m_file);
    }
}

void* FileStream::read(void) {
    Uint64 size = m_fileInfo.getSize();
    char* buffer = new char[size];
    GF_ASSERT(m_file != nullptr, "File does not opened", m_fileInfo.getName());
    std::fread(buffer, 1, static_cast<std::size_t>(m_fileInfo.getSize()), m_file);
    return buffer;
}

Int64 FileStream::seek(Int64 position) {
    GF_ASSERT(m_file != nullptr, "File does not opened", m_fileInfo.getName());
    int result = std::fseek(m_file, position, SEEK_SET);
    GF_ASSERT(result > -1, "Failed to set the file position", std::ferror(m_file));
    return tell();
}

Int64 FileStream::tell() {
    GF_ASSERT(m_file != nullptr, "File does not opened", m_fileInfo.getName());
    return std::ftell(m_file);
}

Int64 FileStream::getSize() {
    if (m_file) {
        Int64 position = tell();
        std::fseek(m_file, 0, SEEK_END);
        Int64 size = tell();
        seek(position);
        return size;
    }
    return -1;
}

}
