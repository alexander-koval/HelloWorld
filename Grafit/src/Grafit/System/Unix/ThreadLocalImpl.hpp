#ifndef THREADLOCALIMPL_HPP
#define THREADLOCALIMPL_HPP

#include <Grafit/System/NonCopyable.hpp>
#include <pthread.h>

namespace gf {
namespace priv {

class ThreadLocalImpl : NonCopyable {
public:

    ThreadLocalImpl();

    ~ThreadLocalImpl();

    void setValue(void* value);

    void* getValue() const;

private:
    pthread_key_t m_key; ///< Index of our thread-local storage slot
};

} // namespace priv
}

#endif // THREADLOCALIMPL_HPP
