#include <Grafit/System/SystemInfo.hpp>

#if defined(GRAFIT_SYSTEM_WINDOWS)
    #include "Win32/SystemInfoImpl.hpp"
#elif defined(GRAFIT_SYSTEM_MACOS)
    #include "OSX/SystemInfoImpl.hpp"
#else
    #include "Unix/SystemInfoImpl.hpp"
#endif

namespace gf {

std::string SystemInfo::getHostName(void) {
    return priv::systeminfo::getHostName();
}

std::string SystemInfo::getUserName(void) {
    return priv::systeminfo::getUserName();
}

std::string SystemInfo::getUserDirectory(void) {
    return priv::systeminfo::getUserDirectory();
}

std::string SystemInfo::getTempDirectory(void) {
    return priv::systeminfo::getTempDirectory();
}

std::string SystemInfo::getApplicationDirectory(void) {
    return priv::systeminfo::getApplicationDirectory();
}

std::string SystemInfo::getEnvironment(const std::string& value) {
    return priv::systeminfo::getEnvironment(value);
}

}
