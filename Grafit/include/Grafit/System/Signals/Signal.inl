#include <Grafit/System/Signals/Signal.hpp>
#include <Grafit/System/Signals/Connection.hpp>

namespace gf {

template <typename R, typename ... Args>
Connection& Signal<R(Args...)>::connect(const std::function<R(Args...)>& listener, bool once/* = false*/, int priority/* = 0*/,
                                        ConnectPosition pos/* = ConnectPosition::Back*/) {
    registerListener(listener, once, priority, pos);
}

template <typename R, typename ... Args>
bool Signal<R(Args...)>::disconnect(const Connection& connection) {
    if (connection.isConnected()) {
        for (Iterator it = m_slotMap.begin(); it != m_slotMap.end(); ++it) {
            if (it->first == connection) {
                m_slotMap.erase(it);
                return true;
            }
        }
    }
    return false;
}

template <typename R, typename ... Args>
void Signal<R(Args...)>::disconnectAll(void) {
    m_slotMap.clear();
}

template <typename R, typename ... Args>
void Signal<R(Args...)>::dispatch(Args&& ...args) {
    Iterator it = m_slotMap.begin();
    while (it != m_slotMap.end()) {
        if (it->first.isConnected()) {
            const Slot<R(Args...)>& slot = it->second;
            slot.execute(std::forward<Args>(args)...);
            if (slot.isOnce()) {
                m_slotMap.erase(it++);
                continue;
            }
        }
        ++it;
    }
}

template <typename R, typename ... Args>
int Signal<R(Args...)>::numSlots(void) const {
    std::size_t count = 0;
    for (ConstIterator it = m_slotMap.begin(); it != m_slotMap.end(); ++it) {
        const Connection& con = it->first;
        if (it->first.isConnected()) ++count;
    }
    return count;
}

template <typename R, typename ... Args>
Connection& Signal<R(Args...)>::registerListener(const std::function<R(Args...)>& listener,
                                                 bool once, int priority, ConnectPosition pos) {
    void (*signal_disconnect)(Signal<R(Args...)>*, const Connection&) = &Signal<R(Args...)>::disconnect;

    typename SlotMap<Slot<R(Args...)>>::Iterator it = m_slotMap.insert(priority,
                                                                       Connection(this, signal_disconnect),
                                                                       Slot<R(Args...)>(listener, once, priority),
                                                                       pos);
    return (*it).first;
}

}
