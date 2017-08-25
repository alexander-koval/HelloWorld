#include <Grafit/System/Win32/ThreadImpl.hpp>
#include <Grafit/System/Thread.hpp>
#include <cassert>
#include <iostream>
#include <process.h>


namespace gf {
namespace priv {
ThreadImpl::ThreadImpl(Thread* owner) {
    m_thread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, &ThreadImpl::entryPoint, owner, 0, &m_threadId));

    if (!m_thread)
        std::cerr << "Failed to create thread" << std::endl;
}

ThreadImpl::~ThreadImpl() {
    if (m_thread)
        CloseHandle(m_thread);
}

void ThreadImpl::wait() {
    if (m_thread)
    {
        assert(m_threadId != GetCurrentThreadId()); // A thread cannot wait for itself!
        WaitForSingleObject(m_thread, INFINITE);
    }
}

void ThreadImpl::terminate() {
    if (m_thread)
        TerminateThread(m_thread, 0);
}

unsigned int __stdcall ThreadImpl::entryPoint(void* userData) {
    // The Thread instance is stored in the user data
    Thread* owner = static_cast<Thread*>(userData);

    // Forward to the owner
    owner->run();

    // Optional, but it is cleaner
    _endthreadex(0);

    return 0;
}

} // namespace priv

} // namespace gf
