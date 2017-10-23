#include <Grafit/System/IO/FileSystem.hpp>
#include <Grafit/System/IO/FileStream.hpp>
#include <Grafit/System/File.hpp>

namespace gf {

FileSystem::FileSystem(const std::string& root)
: m_root(Path(root).toString()) {

}

bool FileSystem::exists(const std::string& filename) const {
    File file(m_root + filename);
    return file.isExist();
}

//SmartPtr<InputStream> FileSystem::openRead(const std::string& filename) {
//    File file(m_root + filename);
//    if (file.isExist() && file.isRegularFile()) {
//        gf::FileInputStream stream;
//        stream.open(&file);
//    }
//    return SmartPtr<InputStream>();
//}

//SmartPtr<OutputStream> FileSystem::openWrite(const std::string& filename) {
//    return SmartPtr<OutputStream>();
//}

void FileSystem::remove(const std::string& filename) {
    File file(m_root + filename);
    if (file.isExist()) {
        file.remove();
    }
}

}
