#ifndef THREADIMPL_HPP
#define THREADIMPL_HPP

#include <Grafit/System/NonCopyable.hpp>
#include <pthread.h>

namespace gf {
class Thread;

namespace priv {

class ThreadImpl : NonCopyable {
public:

    ThreadImpl(Thread* owner);

    void wait();

    void terminate();

private:

    static void* entryPoint(void* userData);

    pthread_t m_thread;   ///< pthread thread instance
    bool      m_isActive; ///< Thread state (active or inactive)
};

} // namespace priv

} // namespace gf

#endif // THREADIMPL_HPP
