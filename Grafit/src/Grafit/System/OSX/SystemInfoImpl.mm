#import "SystemInfoImpl.hpp"
#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
#import <unistd.h>
#import <limits>

namespace gf {
namespace priv {

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

std::string SystemInfoImpl::getUserDirectory(void) {
    return getEnvironment("HOME");
}

std::string SystemInfoImpl::getUserName(void) {
    std::string result(getEnvironment("USER"));
    if (result.empty()) {
        result = getEnvironment("LOGNAME");
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
    std::string rpath;
    NSBundle* bundle = [NSBundle mainBundle];
    if (bundle != nil) {
        NSString* path = [bundle bundlePath];
        rpath = [path UTF8String];
    }
    return rpath;
}

std::string SystemInfoImpl::getEnvironment(const std::string& value) {
    std::string rpath;
    NSString* input = [[[NSString alloc] initWithUTF8String:value.c_str()] autorelease];
    NSString* path = [[[NSProcessInfo processInfo] environment] objectForKey:input];
    if (path != nil) {
        rpath = [path UTF8String];
    }
    return rpath;
}

}
}

