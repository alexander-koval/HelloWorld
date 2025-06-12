#include <Grafit/System/Signals/Connection.hpp>

namespace gf {
namespace priv { AbstractConnection::~AbstractConnection(void) { } }

void Connection::disconnect(void) const {
    if (this->isConnected()) {
        m_connection->disconnect(*this);
    }
}

}
