#include <Grafit/System/IO/FileSystem.hpp>
#include <Grafit/System/IO/FileStream.hpp>
#include <Grafit/System/File.hpp>
#include <memory>

namespace gf {

FileSystem::FileSystem(const std::string& root)
: m_root(Path(root).toString()) {

}

bool FileSystem::exists(const std::string& filename) const {
    File file(m_root + File::Separator + filename);
    return file.isExist();
}

SharedPtr<IOStream> FileSystem::open(const std::string& filename) {
    File file(m_root + File::Separator + filename);
    if (file.isExist() && file.isRegularFile()) {
        SharedPtr<FileStream> streamPtr = make_shared<FileStream>();
        streamPtr->open(std::move(file));
        return streamPtr;
    }
    return SharedPtr<IOStream>();
}

SharedPtr<IOStream> FileSystem::openRead(const std::string& filename) {
    return open(filename);
}

SharedPtr<IOStream> FileSystem::openWrite(const std::string& filename) {
    return open(filename);
}

void FileSystem::remove(const std::string& filename) {
    File file(m_root + File::Separator + filename);
    if (file.isExist()) {
        file.remove();
    }
}

}
