#include <Grafit/System/IO/PhysfsFileSystem.hpp>
#include <Grafit/System/IO/Stream.hpp>
#include "physfs.h"

namespace gf {

class PhysfsStream : public IOStream {
public:
    PhysfsStream(PHYSFS_File* file)
        : m_file(file) {

    }

    virtual void readAll(std::vector<char>& buffer) override {
        PHYSFS_sint64 length = PHYSFS_fileLength(m_file);
        PHYSFS_seek(m_file, 0);
        buffer.resize(length);
        PHYSFS_readBytes(m_file, &buffer[0], length);
    }

    virtual void writeAll(std::vector<char>& buffer) override {

    }

    Int64 read(char* buffer, std::size_t size) override {
        return PHYSFS_readBytes(m_file, buffer, size);
    }

    virtual void write(char* buffer, std::size_t size) override {
        PHYSFS_writeBytes(m_file, buffer, size);
    }

    virtual Int64 seek(Int64 position) override{
        return PHYSFS_seek(m_file, static_cast<PHYSFS_uint64>(position));
    }

    virtual Int64 tell(void) override {
        return PHYSFS_tell(m_file);
    }

    virtual Int64 getSize(void) override {
        PHYSFS_sint64 file_size = PHYSFS_fileLength(m_file);
        return file_size;
    }

private:
    PHYSFS_File* m_file;
};


PhysfsFileSystem::PhysfsFileSystem(const std::string& root)
    : FileSystem(root) {
    if (!PHYSFS_isInit()) {
        PHYSFS_init(root.empty() ? nullptr : root.c_str());
    }
}

PhysfsFileSystem::~PhysfsFileSystem() {
    if (PHYSFS_isInit() && !PHYSFS_deinit()) {

    }
}

void PhysfsFileSystem::mount(const std::string& path, const std::string& mountPoint, bool appendToEnd) {
    if (!PHYSFS_mount(path.c_str(), mountPoint.c_str(), appendToEnd ? 1 : 0)) {
        std::cout << PHYSFS_getLastError() << std::endl;
    }
}

bool PhysfsFileSystem::exists(const std::string& filename) const {
    return PHYSFS_exists(filename.c_str());
}

SharedPtr<IOStream> PhysfsFileSystem::openRead(const std::string& filename) {
    PHYSFS_File* file = PHYSFS_openRead(filename.c_str());
    if (!file) {
        std::cout << PHYSFS_getLastError() << std::endl;
        return SharedPtr<IOStream>();
    }
    return std::make_shared<PhysfsStream>(file);
}

SharedPtr<IOStream> PhysfsFileSystem::openWrite(const std::string& filename) {
    PHYSFS_File* file = PHYSFS_openWrite(filename.c_str());
    if (!file) {
        std::cout << PHYSFS_getLastError() << std::endl;
        return SharedPtr<IOStream>();
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
