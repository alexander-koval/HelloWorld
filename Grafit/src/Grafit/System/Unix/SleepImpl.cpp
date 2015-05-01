#include <Grafit/System/Unix/SleepImpl.hpp>
#include <errno.h>
#include <time.h>

namespace gf {

namespace priv {

void sleepImpl(Time time) {
    Uint64 usecs = time.asMicroseconds();

    // Construct the time to wait
    timespec ti;
    ti.tv_nsec = (usecs % 1000000) * 1000;
    ti.tv_sec = usecs / 1000000;

    // Wait...
    // If nanosleep returns -1, we check errno. If it is EINTR
    // nanosleep was interrupted and has set ti to the remaining
    // duration. We continue sleeping until the complete duration
    // has passed. We stop sleeping if it was due to an error.
    while ((nanosleep(&ti, &ti) == -1) && (errno == EINTR))
    {
    }
}

} // namespace priv

} // namespace gf
