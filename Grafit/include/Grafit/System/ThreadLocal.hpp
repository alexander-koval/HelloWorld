#ifndef THREADLOCAL_HPP
#define THREADLOCAL_HPP

#include <Grafit/System/NonCopyable.hpp>
#include <cstdlib>

namespace priv {
    class ThreadLocalImpl;
}

class ThreadLocal : NonCopyable {
public:

    ThreadLocal(void* value = NULL);

    ~ThreadLocal();

    void setValue(void* value);

    void* getValue() const;

private:

    priv::ThreadLocalImpl* m_impl; ///< Pointer to the OS specific implementation
};

#endif // THREADLOCAL_HPP
