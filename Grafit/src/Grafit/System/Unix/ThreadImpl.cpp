#include "ThreadImpl.hpp"
#include <Grafit/System/Exception.hpp>
#include <Grafit/System/Thread.hpp>
#include <iostream>
#include <cassert>

namespace gf {
namespace priv {

ThreadImpl::ThreadImpl(Thread* owner)
: m_isActive(true) {
    m_isActive = pthread_create(&m_thread, nullptr, &ThreadImpl::entryPoint, owner) == 0;

    if (!m_isActive) {
        NoThreadAvailableException("Failed to create thread");
    }
}

void ThreadImpl::wait() {
    if (m_isActive) {
        assert(pthread_equal(pthread_self(), m_thread) == 0); // A thread cannot wait for itself!
        pthread_join(m_thread, nullptr);
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
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);
    #endif

    // Forward to the owner
    owner->run();

    return nullptr;
}

} // namespace priv
} // namespace gf
