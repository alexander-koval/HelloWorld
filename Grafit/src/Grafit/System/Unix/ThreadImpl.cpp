#include <Grafit/System/Unix/ThreadImpl.hpp>
#include <Grafit/System/Thread.hpp>
#include <iostream>
#include <cassert>

namespace gf {
namespace priv {

ThreadImpl::ThreadImpl(Thread* owner)
: m_isActive(true) {
    m_isActive = pthread_create(&m_thread, NULL, &ThreadImpl::entryPoint, owner) == 0;

    if (!m_isActive)
        std::cerr << "Failed to create thread" << std::endl;
}

void ThreadImpl::wait() {
    if (m_isActive) {
        assert(pthread_equal(pthread_self(), m_thread) == 0); // A thread cannot wait for itself!
        pthread_join(m_thread, NULL);
    }
}

void ThreadImpl::terminate() {
    if (m_isActive) {
        #ifndef GRAFIT_SYSTEM_ANDROID
            pthread_cancel(m_thread);
        #else
            // See http://stackoverflow.com/questions/4610086/pthread-cancel-al
            pthread_kill(m_thread, SIGUSR1);
        #endif
    }
}

void* ThreadImpl::entryPoint(void* userData) {
    // The Thread instance is stored in the user data
    Thread* owner = static_cast<Thread*>(userData);

    #ifndef SYSTEM_ANDROID
        // Tell the thread to handle cancel requests immediately
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    #endif

    // Forward to the owner
    owner->run();

    return NULL;
}

} // namespace priv
} // namespace gf
