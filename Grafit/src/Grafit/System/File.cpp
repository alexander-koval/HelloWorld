#include <Grafit/System/File.hpp>
#include <Grafit/System/String.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#if defined(GRAFIT_SYSTEM_WINDOWS)
    #include "Win32/FileImpl.hpp"
#else
    #include "Unix/FileImpl.hpp"
#endif

namespace gf {

const char File::Separator = Path::separator();

File::File()
: m_pimpl(new FileImpl()) {

}

File::File(const File& that) {
    m_pimpl = that.m_pimpl;
}

File::File(File&& that) {
    m_pimpl = that.m_pimpl;
}

File::File(const std::string& path)
: m_pimpl(new FileImpl(path)) {

}

File::File(const Path& path)
: m_pimpl(new FileImpl(path.toString())) {

}

File::~File(void) {
    delete m_pimpl;
}

bool File::isExist(void) const {
    return m_pimpl->existsImpl();
}

bool File::isDirectory(void) const {
    return m_pimpl->isDirectoryImpl();
}

bool File::isHidden(void) const {
    return m_pimpl->isHiddenImpl();
}

bool File::isSymbolicLink(void) const {
    return m_pimpl->isLinkImpl();
}

bool File::isRegularFile(void) const {
    return m_pimpl->isFileImpl();
}

std::string File::getName(void) const {
    return m_pimpl->getName();
}

std::string File::getExtension(void) const {
    return m_pimpl->getExtension();
}

std::string File::getNativePath(void) const {
    return m_pimpl->getPathImpl();
}

Uint64 File::getSize(void) const {
    return m_pimpl->getSizeImpl();
}

float File::getSpaceAvailable(void) const {
    return m_pimpl->freeSpaceImpl();
}

void File::swap(File&& that) {
    std::swap(m_pimpl, that.m_pimpl);
}

void File::remove() {
    m_pimpl->removeImpl();
}

}
