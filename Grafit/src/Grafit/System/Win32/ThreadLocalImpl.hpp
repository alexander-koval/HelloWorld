#ifndef THREADLOCALIMPL_HPP
#define THREADLOCALIMPL_HPP

#include <Grafit/System/NonCopyable.hpp>
#include <windows.h>


namespace gf {
namespace priv {
class ThreadLocalImpl : NonCopyable {
public:

    ThreadLocalImpl();

    ~ThreadLocalImpl();

    void setValue(void* value);

    void* getValue() const;

private:

    DWORD m_index; ///< Index of our thread-local storage slot
};

} // namespace priv

} // namespace gf


#endif // THREADLOCALIMPL_HPP
