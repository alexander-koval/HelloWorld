#include <Grafit/System/IO/VirtualFileSystem.hpp>
#include <Grafit/System/IO/FileSystem.hpp>
#include <Grafit/System/File.hpp>
#include <Grafit/System/Path.hpp>
#include <algorithm>

namespace gf {

VirtualFileSystem::VirtualFileSystem() : m_systems() {
    m_systems.push_back(make_shared<FileSystem>("."));
}

void VirtualFileSystem::mount(FileSystemPtr fs) {
    m_systems.insert(std::next(m_systems.begin()), fs);
}

void VirtualFileSystem::mountDirectory(const std::string &path) {
    mount(make_shared<FileSystem>(path));
}

void VirtualFileSystem::setWriteDirectory(const std::string &path) {
    m_systems.begin()->reset(new FileSystem(path));
}

const std::string &VirtualFileSystem::getWriteDirectory() const {
    return (*m_systems.begin())->getRoot();
}

bool VirtualFileSystem::exists(const std::string &filename) const {
    Path path(filename);
    if (path.isRelative()) {
        return std::any_of(m_systems.begin(), m_systems.end(),
                           [&filename](const FileSystemPtr& system) {
            return system->exists(filename);
        });
    }
    return false;
}

SharedPtr<IOStream> VirtualFileSystem::openRead(const std::string &filename) {
    Path path(filename);
    if (path.isRelative()) {
        for (FileSystems::const_iterator it = m_systems.begin(); it != m_systems.end(); ++it) {
            SharedPtr<IOStream> stream = (*it)->openRead(filename);
            if (stream) {
                return stream;
            }
        }
    }
    return SharedPtr<IOStream>();
}

SharedPtr<IOStream> VirtualFileSystem::openWrite(const std::string &filename) {
    Path path(filename);
    if (path.isRelative()) {
        return (*m_systems.begin())->openWrite(filename);
    }
    return SharedPtr<IOStream>();
}

SharedPtr<IOStream> VirtualFileSystem::open(const std::string &filename) {
    return openRead(filename);
}

void VirtualFileSystem::remove(const std::string &filename) {
    Path path(filename);
    if (path.isRelative()) {
        (*m_systems.begin())->remove(filename);
    }
}

}
