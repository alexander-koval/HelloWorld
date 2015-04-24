#include <Grafit/System/Unix/ClockImpl.hpp>
#if defined(GRAFIT_SYSTEM_MACOS) || defined(GRAFIT_SYSTEM_IOS)
    #include <mach/mach_time.h>
#else
    #include <time.h>
#endif


namespace priv {

Time ClockImpl::getCurrentTime() {
#if defined(GRAFIT_SYSTEM_MACOS) || defined(GRAFIT_SYSTEM_IOS)

    // Mac OS X specific implementation (it doesn't support clock_gettime)
    static mach_timebase_info_data_t frequency = {0, 0};
    if (frequency.denom == 0)
        mach_timebase_info(&frequency);
    Uint64 nanoseconds = mach_absolute_time() * frequency.numer / frequency.denom;
    return microseconds(nanoseconds / 1000);

#else

    // POSIX implementation
    timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return microseconds(static_cast<Uint64>(time.tv_sec) * 1000000 + time.tv_nsec / 1000);

#endif
}

} // namespace priv
