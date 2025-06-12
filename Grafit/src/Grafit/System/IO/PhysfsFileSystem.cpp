#include <Grafit/System/IO/PhysfsFileSystem.hpp>
#include <Grafit/System/IO/Stream.hpp>
#include <Grafit/System/Exception.hpp>
#include "physfs.h"

namespace gf {

class PhysfsStream : public IOStream {
public:
    PhysfsStream(PHYSFS_File* file)
        : m_file(file) {
        GF_ASSERT(m_file != nullptr, "File not found");
    }

    virtual void readAll(std::vector<char>& buffer) override;

    virtual void readAll(OutputStream& stream) override;

    virtual void writeAll(std::vector<char>& buffer) override;

    virtual void writeAll(InputStream& stream) override;

    virtual Int64 read(char* buffer, std::size_t size) override;

    virtual void write(char* buffer, std::size_t size) override;

    virtual Int64 seek(Int64 position, Origin origin) override;

    virtual Int64 tell(void) override;

    virtual Int64 getSize(void) override;
private:
    PHYSFS_File* m_file;
};


void PhysfsStream::readAll(std::vector<char>& buffer) {
    PHYSFS_uint64 length = static_cast<PHYSFS_uint64>(PHYSFS_fileLength(m_file));
    PHYSFS_seek(m_file, 0);
    buffer.resize(length);
    PHYSFS_readBytes(m_file, &buffer[0], length);
}

void PhysfsStream::readAll(OutputStream& stream) {
    std::vector<char> buffer;
    readAll(buffer);
    if (!buffer.empty()) {
        stream.writeAll(buffer);
    }
}

void PhysfsStream::writeAll(std::vector<char>& buffer) {
    if (!buffer.empty()) {
        write(&buffer.front(), buffer.size());
    }
}

void PhysfsStream::writeAll(InputStream& stream) {
    std::vector<char> buffer;
    stream.readAll(buffer);
    if (!buffer.empty()) {
        writeAll(buffer);
    }
}

Int64 PhysfsStream::read(char* buffer, std::size_t size) {
    return PHYSFS_readBytes(m_file, buffer, size);
}

void PhysfsStream::write(char* buffer, std::size_t size) {
    PHYSFS_writeBytes(m_file, buffer, size);
    PHYSFS_flush(m_file);
}

Int64 PhysfsStream::seek(Int64 position, Origin origin) {
    PHYSFS_sint64 pos = 0;
    switch (origin) {
    case Origin::Begin:
        break;
    case Origin::Current:
        pos = PHYSFS_tell(m_file) + position;
        break;
    case Origin::End:
        pos = PHYSFS_fileLength(m_file) - std::abs(position);
        break;
    }
    int result = PHYSFS_seek(m_file, static_cast<PHYSFS_uint64>(position));
    if (!result) {
        PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
        SeekFileException(PHYSFS_getErrorByCode(code), code);
    }
    return result;
}

Int64 PhysfsStream::tell(void) {
    return PHYSFS_tell(m_file);
}

Int64 PhysfsStream::getSize(void) {
    PHYSFS_sint64 file_size = PHYSFS_fileLength(m_file);
    return file_size;
}

PhysfsFileSystem::PhysfsFileSystem(const std::string& root)
    : FileSystem(root) {
    if (!PHYSFS_isInit()) {
        int result = PHYSFS_init(root.empty() ? nullptr : root.c_str());
        if (!result) {
            PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
            OpenFileException(PHYSFS_getErrorByCode(code), code);
        }
    }
}

PhysfsFileSystem::~PhysfsFileSystem() {
    if (PHYSFS_isInit() && !PHYSFS_deinit()) {

    }
}

void PhysfsFileSystem::mount(const std::string& path, const std::string& mountPoint, bool appendToEnd) {
    if (!PHYSFS_mount(path.c_str(), mountPoint.c_str(), appendToEnd ? 1 : 0)) {
        PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
        OpenFileException(PHYSFS_getErrorByCode(code), code);
    }
}

bool PhysfsFileSystem::exists(const std::string& filename) const {
    return PHYSFS_exists(filename.c_str());
}

SharedPtr<IOStream> PhysfsFileSystem::openRead(const std::string& filename) {
    PHYSFS_File* file = PHYSFS_openRead(filename.c_str());
    if (!file) {
        PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
        OpenFileException(PHYSFS_getErrorByCode(code), code);
    }
    return std::make_shared<PhysfsStream>(file);
}

SharedPtr<IOStream> PhysfsFileSystem::openWrite(const std::string& filename) {
    PHYSFS_File* file = PHYSFS_openWrite(filename.c_str());
    if (!file) {
        PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
        OpenFileException(PHYSFS_getErrorByCode(code), code);
    }
    return std::make_shared<PhysfsStream>(file);
}

SharedPtr<IOStream> PhysfsFileSystem::open(const std::string& filename) {
    return openRead(filename);
}

void PhysfsFileSystem::remove(const std::string& filename) {
    PHYSFS_delete(filename.c_str());
}

}
