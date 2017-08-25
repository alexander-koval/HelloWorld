#include <Grafit/System/Unix/ThreadLocalImpl.hpp>

namespace gf {
namespace priv {

ThreadLocalImpl::ThreadLocalImpl() {
    pthread_key_create(&m_key, nullptr);
}

ThreadLocalImpl::~ThreadLocalImpl() {
    pthread_key_delete(m_key);
}

void ThreadLocalImpl::setValue(void* value) {
    pthread_setspecific(m_key, value);
}

void* ThreadLocalImpl::getValue() const {
    return pthread_getspecific(m_key);
}

} // namespace priv
}
