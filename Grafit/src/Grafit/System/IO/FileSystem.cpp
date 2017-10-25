#include <Grafit/System/IO/FileSystem.hpp>
#include <Grafit/System/IO/FileStream.hpp>
#include <Grafit/System/File.hpp>
#include <memory>

namespace gf {

FileSystem::FileSystem(const std::string& root)
: m_root(Path(root).toString()) {

}

bool FileSystem::exists(const std::string& filename) const {
    File file(m_root + filename);
    return file.isExist();
}

//TODO: FIXME Утечка
SmartPtr<IOStream> FileSystem::open(const std::string& filename) {
    File* file = new File(m_root + File::Separator + filename);
    if (file->isExist() && file->isRegularFile()) {
        gf::FileStream* stream = new FileStream();
        stream->open(file);
        SmartPtr<IOStream> ptr(stream);
        return ptr;
    }
    return SmartPtr<IOStream>();
}

SmartPtr<IOStream> FileSystem::openRead(const std::string& filename) {
    return open(filename);
}

SmartPtr<IOStream> FileSystem::openWrite(const std::string& filename) {
    return open(filename);
}

void FileSystem::remove(const std::string& filename) {
    File file(m_root + filename);
    if (file.isExist()) {
        file.remove();
    }
}

}
