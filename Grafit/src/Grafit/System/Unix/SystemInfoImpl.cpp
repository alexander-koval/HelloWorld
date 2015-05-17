#include <Grafit/System/Unix/SystemInfoImpl.hpp>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>

#ifndef GRAFIT_SYSTEM_LINUX
    #define _PSTAT64
    #include <sys/pstat.h>
    #include <sys/types.h>
#endif

namespace gf {
namespace priv {

std::string SystemInfoImpl::getUserName(void) {
    std::string result(getEnvironment("USER"));
    if (result.empty())
        result = getEnvironment("LOGNAME");

    return result;
}

std::string SystemInfoImpl::getUserDirectory(void) {
    return getEnvironment("HOME");
}

std::string SystemInfoImpl::getHostName(void) {
    char name[PATH_MAX];
    std::string result;
    if (gethostname(name, PATH_MAX) == 0) {
        result = name;
    } else {
        result = getEnvironment("HOSTNAME");
    }
    return result;
}

std::string SystemInfoImpl::getTempDirectory(void) {
#if defined(P_tmpdir)
    return P_tmpdir;
#else
    return getEnvironment("TMPDIR");
#endif
}

std::string SystemInfoImpl::getApplicationDirectory(void) {
#if defined(GRAFIT_SYSTEM_LINUX)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
#else
    char result[ PATH_MAX ];
    struct pst_status ps;
    if (pstat_getproc( &ps, sizeof( ps ), 0, getpid() ) < 0)
        return std::string();
    if (pstat_getpathname( result, PATH_MAX, &ps.pst_fid_text ) < 0)
        return std::string();
    return std::string( result );
#endif
}

std::string SystemInfoImpl::getEnvironment(const std::string& value) {
    char* variable = getenv(value.c_str());
    std::string result;
    if (variable)
        result = variable;
    return result;
}

}
}
