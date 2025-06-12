#include <Grafit/System/ThreadLocal.hpp>

#if defined(GRAFIT_SYSTEM_WINDOWS)
    #include "Win32/ThreadLocalImpl.hpp"
#else
    #include "Unix/ThreadLocalImpl.hpp"
#endif

namespace gf {

ThreadLocal::ThreadLocal(void* value) {
    m_impl = new priv::ThreadLocalImpl();
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

}
