#ifndef CLOCKIMPLUNIX_HPP
#define CLOCKIMPLUNIX_HPP

#include <Grafit/System/Time.hpp>

namespace gf {
namespace priv {

class ClockImpl {
public:

    static Time getCurrentTime();
};

} // namespace priv

} // namespace gf

#endif // SFML_CLOCKIMPLUNIX_HPP
