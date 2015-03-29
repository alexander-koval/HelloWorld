#ifndef LOCK_HPP
#define LOCK_HPP

#include <Grafit/System/NonCopyable.hpp>

namespace gf {
class Mutex;
class Lock : NonCopyable {
public:

    explicit Lock(Mutex& mutex);

    ~Lock();

private:
    Mutex& m_mutex; ///< Mutex to lock / unlock
};

}
#endif // LOCK_HPP
