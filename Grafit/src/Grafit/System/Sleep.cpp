#include <Grafit/System/Sleep.hpp>

#if defined(SYSTEM_WINDOWS)
    #include "Win32/SleepImpl.hpp"
#else
    #include "Unix/SleepImpl.hpp"
#endif

namespace gf {

void sleep(Time duration) {
    if (duration >= Time::Zero)
        priv::sleepImpl(duration);
}

}
