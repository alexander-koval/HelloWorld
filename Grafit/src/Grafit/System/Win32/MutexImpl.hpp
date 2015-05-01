#ifndef MUTEXIMPL_HPP
#define MUTEXIMPL_HPP

#include <Grafit/System/NonCopyable.hpp>
#include <windows.h>


namespace gf {
namespace priv {
class MutexImpl : NonCopyable {
public:

    MutexImpl();

    ~MutexImpl();

    void lock();

    void unlock();

private:

    CRITICAL_SECTION m_mutex; ///< Win32 handle of the mutex
};

} // namespace priv

} // namespace gf


#endif // MUTEXIMPL_HPP
