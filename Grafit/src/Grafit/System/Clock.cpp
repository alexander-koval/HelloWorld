#include <Grafit/System/Clock.hpp>

#if defined(GRAFIT_SYSTEM_WINDOWS)
    #include <Grafit/System/Win32/ClockImpl.hpp>
#else
    #include <Grafit/System/Unix/ClockImpl.hpp>
#endif

namespace gf {

Clock::Clock() :
m_startTime(priv::ClockImpl::getCurrentTime()) {
}

Time Clock::getElapsedTime() const {
    return priv::ClockImpl::getCurrentTime() - m_startTime;
}

Time Clock::restart() {
    Time now = priv::ClockImpl::getCurrentTime();
    Time elapsed = now - m_startTime;
    m_startTime = now;

    return elapsed;
}

}
