#include "FileImpl.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/statfs.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <exception>
#include <Grafit/System/Assert.hpp>

namespace gf {
FileImpl::FileImpl() {

}

FileImpl::FileImpl(const std::string &path) : m_path(path) {
    std::string::size_type n = m_path.size();
    if (n > 1 && m_path[n - 1] == '/') {
        m_path.resize(n - 1);
    }
}

FileImpl::~FileImpl() {

}

void FileImpl::swapImpl(FileImpl& file)
{
    std::swap(m_path, file.m_path);
}

void FileImpl::setPathImpl(const std::string& path)
{
    m_path = path;
    std::string::size_type n = m_path.size();
    if (n > 1 && m_path[n - 1] == '/') {
        m_path.resize(n - 1);
    }
}

bool FileImpl::existsImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    return stat(m_path.c_str(), &st) == 0;
}

bool FileImpl::canReadImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0) {
        if (st.st_uid == geteuid()) {
            return (st.st_mode & S_IRUSR) != 0;
        } else if (st.st_gid ==getegid()) {
            return (st.st_mode & S_IRGRP) != 0;
        } else {
            return (st.st_mode & S_IROTH) != 0 || geteuid() == 0;
        }
    }
    return false;
}

bool FileImpl::canWriteImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0)
    {
        if (st.st_uid == geteuid()) {
            return (st.st_mode & S_IWUSR) != 0;
        } else if (st.st_gid == getegid()) {
            return (st.st_mode & S_IWGRP) != 0;
        } else {
            return (st.st_mode & S_IWOTH) != 0 || geteuid() == 0;
        }
    }
    return false;
}

bool FileImpl::canExecuteImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0)
    {
        if (st.st_uid == geteuid() || geteuid() == 0) {
            return (st.st_mode & S_IXUSR) != 0;
        } else if (st.st_gid == getegid()) {
            return (st.st_mode & S_IXGRP) != 0;
        } else {
            return (st.st_mode & S_IXOTH) != 0;
        }
    }
    return false;
}

bool FileImpl::isFileImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0) {
        return S_ISREG(st.st_mode);
    } else {
            handleLastErrorImpl(m_path);
    }
    return false;

}

bool FileImpl::isDirectoryImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0) {
        return S_ISDIR(st.st_mode);
    } else {
        handleLastErrorImpl(m_path);
    }
    return false;
}

bool FileImpl::isLinkImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    if (lstat(m_path.c_str(), &st) == 0) {
        return S_ISLNK(st.st_mode);
    } else {
        handleLastErrorImpl(m_path);
    }
    return false;
}

bool FileImpl::isDeviceImpl() const
{
//    GF_ASSERT(!m_path.empty(), "File path is empty");
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0) {
        return S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode);
    } else {
              handleLastErrorImpl(m_path);
    }
    return false;

}

bool FileImpl::isHiddenImpl() const
{
    Path p(m_path);
    p.makeFile();

    return p.getFileName()[0] == '.';
}

FileImpl::FileSizeImpl FileImpl::getSizeImpl() const
{
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0) {
        return st.st_size;
    } else {
        handleLastErrorImpl(m_path);
    }
    return 0;
}

void FileImpl::setSizeImpl(FileImpl::FileSizeImpl size)
{
    if (truncate(m_path.c_str(), size) != 0) {
        handleLastErrorImpl(m_path);
    }
}

void FileImpl::setWriteableImpl(bool flag)
{
    struct stat st;
    if (stat(m_path.c_str(), &st) != 0)
            handleLastErrorImpl(m_path);
    mode_t mode;
    if (flag)
    {
            mode = st.st_mode | S_IWUSR;
    }
    else
    {
            mode_t wmask = S_IWUSR | S_IWGRP | S_IWOTH;
            mode = st.st_mode & ~wmask;
    }
    if (chmod(m_path.c_str(), mode) != 0)
            handleLastErrorImpl(m_path);
}

void FileImpl::setExecutableImpl(bool flag)
{
    struct stat st;
    if (stat(m_path.c_str(), &st) != 0)
            handleLastErrorImpl(m_path);
    mode_t mode;
    if (flag)
    {
            mode = st.st_mode | S_IXUSR;
    }
    else
    {
            mode_t wmask = S_IXUSR | S_IXGRP | S_IXOTH;
            mode = st.st_mode & ~wmask;
    }
    if (chmod(m_path.c_str(), mode) != 0)
            handleLastErrorImpl(m_path);
}

void FileImpl::renameToImpl(const std::string& path)
{
    if (rename(m_path.c_str(), path.c_str()) != 0)
            handleLastErrorImpl(m_path);
}

const std::string &FileImpl::getPathImpl() const {
    return m_path;
}

void FileImpl::removeImpl()
{
    int rc;
    if (!isLinkImpl() && isDirectoryImpl())
            rc = rmdir(m_path.c_str());
    else
            rc = unlink(m_path.c_str());
    if (rc) handleLastErrorImpl(m_path);
}

bool FileImpl::createFileImpl()
{
    int n = open(m_path.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (n != -1) {
        close(n);
        return true;
    }
    if (n == -1 && errno == EEXIST)
            return false;
    else
            handleLastErrorImpl(m_path);
    return false;
}

bool FileImpl::createDirectoryImpl()
{
    struct stat st;
    if (stat(m_path.c_str(), &st) == 0)
            return S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode);
    else
            handleLastErrorImpl(m_path);
    return false;
}

std::string FileImpl::getName() const
{
    Path p(m_path);
    return p.getFileName();
}

std::string FileImpl::getExtension() const
{
    Path p(m_path);
    return p.getExtension();
}

FileImpl::FileSizeImpl FileImpl::totalSpaceImpl() const
{
    struct statfs stats;
    if (statfs(m_path.c_str(), &stats) != 0)
            handleLastErrorImpl(m_path);

    return (FileSizeImpl)stats.f_blocks * (FileSizeImpl)stats.f_bsize;
}

FileImpl::FileSizeImpl FileImpl::usableSpaceImpl() const
{
    struct statfs stats;
    if (statfs(m_path.c_str(), &stats) != 0)
            handleLastErrorImpl(m_path);

    return (FileSizeImpl)stats.f_bavail * (FileSizeImpl)stats.f_bsize;
}

FileImpl::FileSizeImpl FileImpl::freeSpaceImpl() const
{
    struct statfs stats;
    if (statfs(m_path.c_str(), &stats) != 0)
            handleLastErrorImpl(m_path);

    return (FileSizeImpl)stats.f_bfree * (FileSizeImpl)stats.f_bsize;
}

void FileImpl::handleLastErrorImpl(const std::string& path)
{
        switch (errno) {
        case EIO:
            throw std::logic_error(path);
        case EPERM:
            throw std::logic_error(path);
        case EACCES:
            throw std::logic_error(path);
        case ENOENT:
            throw std::logic_error(path);
        case ENOTDIR:
            throw std::logic_error(path);
        case EISDIR:
            throw std::logic_error(path);
        case EROFS:
            throw std::logic_error(path);
        case EEXIST:
            throw std::logic_error(path);
        case ENOSPC:
            throw std::logic_error(path);
        case ENOTEMPTY:
            throw std::logic_error(path);
        case ENAMETOOLONG:
            throw std::logic_error(path);
        case ENFILE:
        case EMFILE:
            throw std::logic_error(path);
        default:
            throw std::logic_error(path);
        }
}


}
