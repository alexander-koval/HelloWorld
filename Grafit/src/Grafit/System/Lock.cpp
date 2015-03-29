#include <Grafit/System/Lock.hpp>
#include <Grafit/System/Mutex.hpp>

namespace gf {

Lock::Lock(Mutex& mutex) :
m_mutex(mutex) {
    m_mutex.lock();
}

Lock::~Lock() {
    m_mutex.unlock();
}

}
