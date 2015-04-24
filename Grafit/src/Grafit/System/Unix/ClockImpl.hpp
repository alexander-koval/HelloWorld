#ifndef CLOCKIMPLUNIX_HPP
#define CLOCKIMPLUNIX_HPP

#include <Grafit/System/Time.hpp>

namespace priv {

class ClockImpl {
public:

    static Time getCurrentTime();
};

} // namespace priv

#endif // CLOCKIMPLUNIX_HPP
