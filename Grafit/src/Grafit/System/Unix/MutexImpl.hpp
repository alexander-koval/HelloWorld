#ifndef MUTEXIMPL_HPP
#define MUTEXIMPL_HPP

#include <Grafit/System/NonCopyable.hpp>
#include <pthread.h>

namespace gf {
namespace priv {

class MutexImpl : NonCopyable {
public:

    MutexImpl();

    ~MutexImpl();

    void lock();

    void unlock();

private:
    pthread_mutex_t m_mutex; ///< pthread handle of the mutex
};

} // namespace priv

}
#endif // MUTEXIMPL_HPP
