#include <Grafit/System/ThreadLocal.hpp>

#if defined(SYSTEM_WINDOWS)
    #include <Grafit/System/Win32/ThreadLocalImpl.hpp>
#else
    #include <Grafit/System/Unix/ThreadLocalImpl.hpp>
#endif


ThreadLocal::ThreadLocal(void* value) {
    m_impl = new priv::ThreadLocalImpl;
    setValue(value);
}

ThreadLocal::~ThreadLocal() {
    delete m_impl;
}

void ThreadLocal::setValue(void* value) {
    m_impl->setValue(value);
}


void* ThreadLocal::getValue() const {
    return m_impl->getValue();
}
