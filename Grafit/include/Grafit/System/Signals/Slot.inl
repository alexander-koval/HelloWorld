#include <functional>
#include <Grafit/System/Signals/Slot.hpp>

namespace gf {

template <typename R, typename ... Args>
Slot<R(Args...)>::Slot(const std::function<R(Args...)>& listener, bool once, int priority)
    : m_priority(priority)
    , m_listener(listener)
    , m_isEnabled(true)
    , m_isOnce(once) { }

template <typename R, typename ... Args>
bool Slot<R(Args...)>::isOnce(void) const {
    return m_isOnce;
}

template <typename R, typename ... Args>
int Slot<R(Args...)>::getPriority(void) const {
    return m_priority;
}

template <typename R, typename ... Args>
void Slot<R(Args...)>::execute(Args&&... args) const {
    if (m_isEnabled) {
        const std::function<R(Args...)>& listener = m_listener;
        listener(std::forward<Args>(args)...);
    }
}

}
