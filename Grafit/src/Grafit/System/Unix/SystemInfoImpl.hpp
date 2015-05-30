#ifndef SYSTEMINFOIMPL_HPP
#define SYSTEMINFOIMPL_HPP

#include <string>

namespace gf {
namespace priv {
namespace systeminfo {
    std::string getUserName(void);

    std::string getUserDirectory(void);

    std::string getHostName(void);

    std::string getTempDirectory(void);

    std::string getApplicationDirectory(void);

    std::string getEnvironment(const std::string& value);
} // systeminfo
} // priv
} // gf

#endif // SYSTEMINFOIMPL_HPP

