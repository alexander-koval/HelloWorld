#include <Grafit/System/Mutex.hpp>

#if defined(GRAFIT_SYSTEM_WINDOWS)
    #include "Win32/MutexImpl.hpp"
#else
    #include "Unix/MutexImpl.hpp"
#endif

namespace gf {
Mutex::Mutex() {
    m_mutexImpl = new priv::MutexImpl;
}

Mutex::~Mutex() {
    delete m_mutexImpl;
}

void Mutex::lock() {
    m_mutexImpl->lock();
}

void Mutex::unlock() {
    m_mutexImpl->unlock();
}
}
