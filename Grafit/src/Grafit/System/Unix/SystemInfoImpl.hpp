#ifndef SYSTEMINFOIMPL_HPP
#define SYSTEMINFOIMPL_HPP

#include <string>

namespace gf {
namespace priv {

class SystemInfoImpl {
public:
    static std::string getUserName(void);

    static std::string getUserDirectory(void);

    template <typename Sequence>
    static void getPath(Sequence& path);

    static std::string getHostName(void);

    static std::string getTempDirectory(void);

    static std::string getApplicationDirectory(void);

    static std::string getEnvironment(const std::string& value);

};

template <typename Sequence>
void SystemInfoImpl::getPath(Sequence& path) {

}

}
}

#endif // SYSTEMINFOIMPL_HPP

