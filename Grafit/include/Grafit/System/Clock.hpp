#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <Grafit/System/Types.hpp>
#include <Grafit/System/Time.hpp>

namespace gf {

class Clock {
public:
    Clock();

    Time getElapsedTime() const;

    Time restart();

private:

    Time m_startTime; ///< Time of last reset, in microseconds
};

}
#endif // CLOCK_HPP
