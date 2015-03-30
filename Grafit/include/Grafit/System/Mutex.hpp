#ifndef MUTEX_HPP
#define MUTEX_HPP
#include <Grafit/System/Types.hpp>
#include <Grafit/System/NonCopyable.hpp>

namespace priv {
    class MutexImpl;
}

namespace gf {
class Mutex : NonCopyable {
public:

    Mutex();

    ~Mutex();

    void lock();

    void unlock();

private:

    priv::MutexImpl* m_mutexImpl; ///< OS-specific implementation
};
}

#endif // MUTEX_HPP
