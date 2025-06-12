#include <Grafit/System/Thread.hpp>

#if defined(GRAFIT_SYSTEM_WINDOWS)
    #include "Win32/ThreadImpl.hpp"
#else
    #include "Unix/ThreadImpl.hpp"
#endif

namespace gf {

Thread::~Thread() {
    wait();
    delete m_entryPoint;
}

void Thread::launch() {
    wait();
    m_impl = new priv::ThreadImpl(this);
}

void Thread::wait() {
    if (m_impl) {
        m_impl->wait();
        delete m_impl;
        m_impl = nullptr;
    }
}

void Thread::terminate() {
    if (m_impl) {
        m_impl->terminate();
        delete m_impl;
        m_impl = nullptr;
    }
}

void Thread::run() {
    m_entryPoint->run();
}

} // namespace gf
