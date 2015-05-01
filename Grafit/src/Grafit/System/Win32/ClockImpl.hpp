#ifndef CLOCKIMPLWIN32_HPP
#define CLOCKIMPLWIN32_HPP

#include <Grafit/System/Time.hpp>

namespace gf {
namespace priv {
class ClockImpl {
public:

    static Time getCurrentTime();
};

} // namespace priv

} // namespace gf


#endif // CLOCKIMPLWIN32_HPP
