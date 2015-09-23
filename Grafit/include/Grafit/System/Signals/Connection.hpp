#ifndef CONNECTION
#define CONNECTION

#include <list>
#include <memory>
#include <utility>
#include <functional>

namespace gf {
class Connection;

namespace priv {

class IConnection {
public:
    virtual bool isConnected(void) = 0;

    virtual void disconnect(const Connection&) = 0;

    virtual IConnection * clone(void) const = 0;

    template <typename U>
    static U* clone(U* object) {
        if (!object) return nullptr;
        U* clone = static_cast<U*>(object->clone());
        GF_ASSERT(typeid(*object) == typeid(*clone), "Can't make clone object", typeid(*clone).name());
        return clone;
    }
};

template <typename R, typename ...Args>
class ConnectionImpl : public IConnection {
public:
    using DisconnectFunc = void(*)(Signal<R(Args...)>*, const Connection&);

    Signal<R(Args...)>* signal;
    DisconnectFunc disconnectFunc;

    ConnectionImpl(Signal<R(Args...)>* signal, DisconnectFunc func) : signal(signal), disconnectFunc(func) { }

    virtual bool isConnected(void) {
        return disconnectFunc != nullptr;
    }

    virtual void disconnect(const Connection& connection) {
        void (*signal_disconnect)(Signal<R(Args...)>*, const Connection&) = disconnectFunc;
        disconnectFunc = 0;
        signal_disconnect(signal, connection);
    }    

    virtual ConnectionImpl* clone(void) const {
        return new ConnectionImpl(*this);
    }
};

}

class Connection : private std::less<Connection>
        , private std::equal_to<Connection> {
public:
    using Impl = priv::IConnection;

    Connection(void) : m_connection() {}

    template <typename R, typename ...Args>
    Connection(Signal<R(Args...)>* signal, void(*func)(Signal<R(Args...)>*, const Connection&))
        : m_connection(new priv::ConnectionImpl<R, Args...>(signal, func)) { }

    Connection(const Connection& other)
        : m_connection(Impl::clone(other.m_connection.get())) { }

    ~Connection(void) {
        disconnect();
    }

    void disconnect(void) const {
        if (this->isConnected()) {
            m_connection->disconnect(*this);
        }
    }

    bool isConnected(void) const {
        return m_connection.get() && m_connection->isConnected();
    }

    bool operator ==(const Connection& other) const {
        return m_connection.get() == other.m_connection.get();
    }

    bool operator <(const Connection& other) const {
        return m_connection.get() < other.m_connection.get();
    }

    Connection& operator =(const Connection& other) {
        Connection(other).swap(*this);
        return *this;
    }

    void swap(Connection& other) {
        this->m_connection.swap(other.m_connection);
    }

private:
    void reset(Impl* con) {
        m_connection.reset(con);
    }

private:
    std::unique_ptr<Impl> m_connection;
};


}

#endif // CONNECTION

