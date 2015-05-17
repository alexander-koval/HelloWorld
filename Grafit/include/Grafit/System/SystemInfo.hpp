#ifndef SYSTEMINFO
#define SYSTEMINFO

#include <string>

namespace gf {
namespace priv {
class SystemInfoImpl;
}

class SystemInfo {
public:
    static std::string getHostName(void);

    static std::string getUserName(void);

    static std::string getUserDirectory(void);

    static std::string getTempDirectory(void);

    static std::string getApplicationDirectory(void);

    static std::string getEnvironment(const std::string& value);
};

}

#endif // SYSTEMINFO

