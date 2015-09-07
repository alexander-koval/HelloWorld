#include <Grafit/System/Signals/Signal.hpp>
#include <Grafit/System/Signals/Connection.hpp>

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
    std::cout << listener.target_type().name() << std::endl;

    void (*signal_disconnect)(Signal<R(Args...)>*, const Connection&) = &Signal<R(Args...)>::disconnect;

    typename SlotMap<Slot<R(Args...)>>::Iterator it = m_slotMap.insert(priority,
                                                                       Connection(this, signal_disconnect),
                                                                       Slot<R(Args...)>(listener, once, priority),
                                                                       pos);
    return (*it).first;
//    const std::shared_ptr<priv::ConnectionImpl>& impl = connection.getConnection();
//    impl->disconnect = &Signal<R(Args...)>::disconnect;
//    impl->signal = this;
//    return connection;
}

}
