#ifndef THREAD_HPP
#define THREAD_HPP

#include <Grafit/System/Types.hpp>
#include <Grafit/System/NonCopyable.hpp>
#include <cstdlib>

namespace gf {
namespace priv {
    class ThreadImpl;
    struct ThreadFunc;
};

class Thread : NonCopyable {
public:

    template <typename F>
    Thread(F function);

    template <typename F, typename A>
    Thread(F function, A argument);

    template <typename C>
    Thread(void(C::*function)(), C* object);

    ~Thread();

    void launch();

    void wait();

    void terminate();

private:

    friend class priv::ThreadImpl;

    void run();

    priv::ThreadImpl* m_impl;       ///< OS-specific implementation of the thread
    priv::ThreadFunc* m_entryPoint; ///< Abstraction of the function to run
};

} // namespace gf

#include <Grafit/System/Thread.inl>
#endif


////////////////////////////////////////////////////////////
/// \class gf::Thread
/// \ingroup system
///
/// Threads provide a way to run multiple parts of the code
/// in parallel. When you launch a new thread, the execution
/// is split and both the new thread and the caller run
/// in parallel.
///
/// To use a gf::Thread, you construct it directly with the
/// function to execute as the entry point of the thread.
/// gf::Thread has multiple template constructors, which means
/// that you can use several types of entry points:
/// \li non-member functions with no argument
/// \li non-member functions with one argument of any type
/// \li functors with no argument (this one is particularly useful for compatibility with boost/std::%bind)
/// \li functors with one argument of any type
/// \li member functions from any class with no argument
///
/// The function argument, if any, is copied in the gf::Thread
/// instance, as well as the functor (if the corresponding
/// constructor is used). Class instances, however, are passed
/// by pointer so you must make sure that the object won't be
/// destroyed while the thread is still using it.
///
/// The thread ends when its function is terminated. If the
/// owner gf::Thread instance is destroyed before the
/// thread is finished, the destructor will wait (see wait())
///
/// Usage examples:
/// \code
/// // example 1: non member function with one argument
///
/// void threadFunc(int argument)
/// {
///     ...
/// }
///
/// gf::Thread thread(&threadFunc, 5);
/// thread.launch(); // start the thread (internally calls threadFunc(5))
/// \endcode
///
/// \code
/// // example 2: member function
///
/// class Task
/// {
/// public:
///     void run()
///     {
///         ...
///     }
/// };
///
/// Task task;
/// gf::Thread thread(&Task::run, &task);
/// thread.launch(); // start the thread (internally calls task.run())
/// \endcode
///
/// \code
/// // example 3: functor
///
/// struct Task
/// {
///     void operator()()
///     {
///         ...
///     }
/// };
///
/// gf::Thread thread(Task());
/// thread.launch(); // start the thread (internally calls operator() on the Task instance)
/// \endcode
///
/// Creating parallel threads of execution can be dangerous:
/// all threads inside the same process share the same memory space,
/// which means that you may end up accessing the same variable
/// from multiple threads at the same time. To prevent this
/// kind of situations, you can use mutexes (see gf::Mutex).
///
/// \see gf::Mutex
///
////////////////////////////////////////////////////////////
