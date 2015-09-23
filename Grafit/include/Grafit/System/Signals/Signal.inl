#include <Grafit/System/Signals/Signal.hpp>
#include <Grafit/System/Signals/Connection.hpp>
#include <iostream>

namespace gf {

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
