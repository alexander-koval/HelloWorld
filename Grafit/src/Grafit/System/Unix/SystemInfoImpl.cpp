#include <Grafit/System/Unix/SystemInfoImpl.hpp>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#if defined(GRAFIT_SYSTEM_MACOS)
    #include <mach-o/dyld.h>
#endif
//    #define _PSTAT64
//    #include <sys/pstat.h>
//    #include <sys/types.h>
#include <iostream>

namespace gf {
namespace priv {
namespace systeminfo {

std::string getUserName(void) {
    std::string result(getEnvironment("USER"));
    if (result.empty())
        result = getEnvironment("LOGNAME");

    return result;
}

std::string getUserDirectory(void) {
    return getEnvironment("HOME");
}

std::string getHostName(void) {
    char name[PATH_MAX];
    std::string result;
    if (gethostname(name, PATH_MAX) == 0) {
        result = name;
    } else {
        result = getEnvironment("HOSTNAME");
    }
    return result;
}

std::string getTempDirectory(void) {
#if defined(P_tmpdir)
    return P_tmpdir;
#else
    return getEnvironment("TMPDIR");
#endif
}

std::string getApplicationDirectory(void) {
    return get_current_dir_name();
//    char result[PATH_MAX];
//    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
//    return std::string(result, (count > 0) ? count : 0);
}

std::string getEnvironment(const std::string& value) {
    char* variable = getenv(value.c_str());
    std::string result;
    if (variable)
        result = variable;
    return result;
}

}
}
}
