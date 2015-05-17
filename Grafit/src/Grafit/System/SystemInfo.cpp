#include <Grafit/System/SystemInfo.hpp>

#if defined(GRAFIT_SYSTEM_WINDOWS)
//    #include <Grafit/System/Win32/ThreadImpl.hpp>
#else
    #include <Grafit/System/Unix/SystemInfoImpl.hpp>
#endif

namespace gf {

std::string SystemInfo::getHostName(void) {
    return priv::SystemInfoImpl::getHostName();
}

std::string SystemInfo::getUserName(void) {
    return priv::SystemInfoImpl::getUserName();
}

std::string SystemInfo::getUserDirectory(void) {
    return priv::SystemInfoImpl::getUserDirectory();
}

std::string SystemInfo::getTempDirectory(void) {
    return priv::SystemInfoImpl::getTempDirectory();
}

std::string SystemInfo::getApplicationDirectory(void) {
    return priv::SystemInfoImpl::getApplicationDirectory();
}

std::string SystemInfo::getEnvironment(const std::string& value) {
    return priv::SystemInfoImpl::getEnvironment(value);
}

}
