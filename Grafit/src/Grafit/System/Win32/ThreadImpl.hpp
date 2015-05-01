#ifndef THREADIMPL_HPP
#define THREADIMPL_HPP

#include <Grafit/System/NonCopyable.hpp>
#include <windows.h>

#if defined(GRAFIT_SYSTEM_WINDOWS) && (defined(__clang__) || defined(__GNUC__))

    #define ALIGN_STACK __attribute__((__force_align_arg_pointer__))

#else

    #define ALIGN_STACK

#endif


namespace gf {
class Thread;

namespace priv {
class ThreadImpl : NonCopyable {
public:

    ThreadImpl(Thread* owner);

    ~ThreadImpl();

    void wait();

    void terminate();

private:

    ALIGN_STACK static unsigned int __stdcall entryPoint(void* userData);

    HANDLE m_thread; ///< Win32 thread handle
    unsigned int m_threadId; ///< Win32 thread identifier
};

} // namespace priv

} // namespace gf


#endif // THREADIMPL_HPP
