#include "SystemInfoImpl.hpp"
#include <Grafit/System/String.hpp>
#include <lmcons.h>
#include <shlobj.h>
#include <winsock2.h>
#include <windows.h>

namespace gf {
namespace priv {
namespace systeminfo {

std::string getUserName(void) {
    TCHAR username[UNLEN + 1];
    DWORD length = UNLEN + 1;
    GetUserName(username, &length);
    return username;
}

std::string getUserDirectory(void) {
    WCHAR path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_PROFILE, nullptr, 0, path))) {
        gf::String str(path);
        return str.toAnsiString();
    }
    return "";
}

std::string getHostName(void) {
    TCHAR hostname[MAX_COMPUTERNAME_LENGTH];
    DWORD size = MAX_COMPUTERNAME_LENGTH;
    if (GetComputerName(hostname, &size) == TRUE) {
        return hostname;
    }
    return "";
}

std::string getTempDirectory(void) {
    TCHAR buffer[MAX_PATH];
    if (GetTempPath(MAX_PATH, buffer) != 0) {
        return buffer;
    }
    return "";
}

std::string getApplicationDirectory(void) {
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH );
    std::string::size_type pos = std::string(buffer).find_last_of( "\\/" );
    return std::string(buffer).substr(0, pos);
}

std::string getEnvironment(const std::string& value) {
    const char* env = std::getenv(value.c_str());
    return env;
}

}
}
}
