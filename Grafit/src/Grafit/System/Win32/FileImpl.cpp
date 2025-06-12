#include "FileImpl.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <exception>
#include <windows.h>
#include <algorithm>
#include <Grafit/System/Assert.hpp>

namespace gf {

class FileHandle {
public:
    FileHandle(std::string& path, DWORD access, DWORD share, DWORD disp) {
        m_handle = CreateFile(path.c_str(), access, share, 0, disp, 0, 0);
        if (m_handle == INVALID_HANDLE_VALUE) {
            FileImpl::handleLastErrorImpl(path);
        }
    }

    ~FileHandle() {
        if (m_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(m_handle);
        }
    }

    HANDLE get() const {
        return m_handle;
    }
private:
    HANDLE m_handle;
};

FileImpl::FileImpl() {

}

FileImpl::FileImpl(const std::string &path) : m_path(path) {
    std::string::size_type n = m_path.size();
    if (n > 1 && (m_path[n - 1] == '\\' || m_path[n - 1] == '/') && !((n == 3 && m_path[1] == ':'))) {
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
    if (n > 1 && (m_path[n - 1] == '\\' || m_path[n - 1] == '/') && !((n == 3 && m_path[1] == ':'))) {
        m_path.resize(n - 1);
    }
}

bool FileImpl::existsImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    DWORD attr = GetFileAttributes(m_path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        switch (GetLastError()) {
            case ERROR_FILE_NOT_FOUND:
            case ERROR_PATH_NOT_FOUND:
            case ERROR_NOT_READY:
            case ERROR_INVALID_DRIVE:
                return false;
        default:
            handleLastErrorImpl(m_path);
        }
    }
    return true;
}

bool FileImpl::canReadImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    DWORD attr = GetFileAttributes(m_path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        switch (GetLastError()) {
            case ERROR_ACCESS_DENIED:
                return false;
            default:
                handleLastErrorImpl(m_path);
        }
    }
    return true;
}

bool FileImpl::canWriteImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    DWORD attr = GetFileAttributes(m_path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        handleLastErrorImpl(m_path);
    }
    return (attr & FILE_ATTRIBUTE_READONLY) == 0;
}

bool FileImpl::canExecuteImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    Path p(m_path);
    std::string ext = p.getExtension();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return (ext.compare("exe") == 0);
}

bool FileImpl::isFileImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    return !isDirectoryImpl() && !isDeviceImpl();
}

bool FileImpl::isDirectoryImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    DWORD attr = GetFileAttributes(m_path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        handleLastErrorImpl(m_path);
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

bool FileImpl::isLinkImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    return false;
}

bool FileImpl::isDeviceImpl() const
{
    GF_ASSERT(!m_path.empty(), "File path is empty");
    return false;
}

bool FileImpl::isHiddenImpl() const
{
    DWORD attr = GetFileAttributesA(m_path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        handleLastErrorImpl(m_path);
    }
    return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
}

FileImpl::FileSizeImpl FileImpl::getSizeImpl() const
{
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if (GetFileAttributesEx(m_path.c_str(), GetFileExInfoStandard, &fad) == 0) {
        handleLastErrorImpl(m_path);
    }
    LARGE_INTEGER li;
    li.LowPart = fad.nFileSizeLow;
    li.HighPart = fad.nFileSizeHigh;
    return li.QuadPart;
}

void FileImpl::setSizeImpl(FileImpl::FileSizeImpl size)
{
    FileHandle handle(m_path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
    LARGE_INTEGER li;
    li.QuadPart = size;
    if (SetFilePointer(handle.get(), li.LowPart, &li.HighPart, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
        handleLastErrorImpl(m_path);
    }
    if (SetEndOfFile(handle.get()) == 0) {
        handleLastErrorImpl(m_path);
    }
}

void FileImpl::setWriteableImpl(bool flag)
{
    DWORD attr = GetFileAttributes(m_path.c_str());
    if (attr == -1) {
        handleLastErrorImpl(m_path);
    }
    if (flag) {
        attr &= ~FILE_ATTRIBUTE_READONLY;
    } else {
        attr |= FILE_ATTRIBUTE_READONLY;
    }
    if (SetFileAttributes(m_path.c_str(), attr) == 0) {
        handleLastErrorImpl(m_path);
    }
}

void FileImpl::setExecutableImpl(bool flag)
{
}

void FileImpl::renameToImpl(const std::string& path)
{
    if (MoveFileExA(m_path.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING) == 0) {
        handleLastErrorImpl(m_path);
    }
}

const std::string &FileImpl::getPathImpl() const {
    return m_path;
}

void FileImpl::removeImpl()
{
    if (isDirectoryImpl()) {
        if (RemoveDirectoryA(m_path.c_str()) == 0) {
            handleLastErrorImpl(m_path);
        }
    } else {
        if (DeleteFileA(m_path.c_str()) == 0) {
            handleLastErrorImpl(m_path);
        }
    }
}

bool FileImpl::createFileImpl()
{
    HANDLE handle = CreateFileA(m_path.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
    if (handle != INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
        return true;
    } else if (GetLastError() == ERROR_FILE_EXISTS) {
        return false;
    } else {
        handleLastErrorImpl(m_path);
    }
    return false;
}

bool FileImpl::createDirectoryImpl()
{
    if (existsImpl() && isDirectoryImpl()) {
        return false;
    }
    if (CreateDirectoryA(m_path.c_str(), 0) == 0) {
        handleLastErrorImpl(m_path);
    }
    return true;
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
    ULARGE_INTEGER space;
    if (!GetDiskFreeSpaceEx(m_path.c_str(), nullptr, &space, nullptr)) {
        handleLastErrorImpl(m_path);
    }
    return space.QuadPart;
}

FileImpl::FileSizeImpl FileImpl::usableSpaceImpl() const
{
    ULARGE_INTEGER space;
    if (!GetDiskFreeSpaceEx(m_path.c_str(), &space, nullptr, nullptr)) {
        handleLastErrorImpl(m_path);
    }
    return space.QuadPart;
}

FileImpl::FileSizeImpl FileImpl::freeSpaceImpl() const
{
    ULARGE_INTEGER space;
    if (!GetDiskFreeSpaceEx(m_path.c_str(), nullptr, nullptr, &space)) {
        handleLastErrorImpl(m_path);
    }
    return space.QuadPart;
}

void FileImpl::handleLastErrorImpl(const std::string& path)
{
    DWORD err = GetLastError();
    switch (err)
    {
    case ERROR_FILE_NOT_FOUND:
        throw std::logic_error("ERROR_FILE_NOT_FOUND");
    case ERROR_PATH_NOT_FOUND:
    case ERROR_BAD_NETPATH:
    case ERROR_CANT_RESOLVE_FILENAME:
    case ERROR_INVALID_DRIVE:
        throw std::logic_error("ERROR_PATH_NOT_FOUND");
    case ERROR_ACCESS_DENIED:
        throw std::logic_error("ERROR_ACCESS_DENIED");
    case ERROR_ALREADY_EXISTS:
    case ERROR_FILE_EXISTS:
        throw std::logic_error("ERROR_FILE_EXISTS");
    case ERROR_INVALID_NAME:
    case ERROR_DIRECTORY:
    case ERROR_FILENAME_EXCED_RANGE:
    case ERROR_BAD_PATHNAME:
        throw std::logic_error("ERROR_INVALID_NAME");
    case ERROR_FILE_READ_ONLY:
        throw std::logic_error("ERROR_FILE_READ_ONLY");
    case ERROR_CANNOT_MAKE:
        throw std::logic_error("ERROR_CANNOT_MAKE");
    case ERROR_DIR_NOT_EMPTY:
        throw std::logic_error("ERROR_DIR_NOT_EMPTY");
    case ERROR_WRITE_FAULT:
        throw std::logic_error("ERROR_WRITE_FAULT");
    case ERROR_READ_FAULT:
        throw std::logic_error("ERROR_READ_FAULT");
    case ERROR_SHARING_VIOLATION:
        throw std::logic_error("ERROR_SHARING_VIOLATION");
    case ERROR_LOCK_VIOLATION:
        throw std::logic_error("ERROR_LOCK_VIOLATION");
    case ERROR_HANDLE_EOF:
        throw std::logic_error("ERROR_HANDLE_EOF");
    case ERROR_HANDLE_DISK_FULL:
    case ERROR_DISK_FULL:
        throw std::logic_error("ERROR_DISK_FULL");
    case ERROR_NEGATIVE_SEEK:
        throw std::logic_error("ERROR_NEGATIVE_SEEK");
    default:
        throw std::logic_error("ERROR_FILE");
    }
}


}
