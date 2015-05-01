#ifndef MUTEX_HPP
#define MUTEX_HPP
#include <Grafit/System/Types.hpp>
#include <Grafit/System/NonCopyable.hpp>

namespace gf {
namespace priv {
class MutexImpl;
}

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
