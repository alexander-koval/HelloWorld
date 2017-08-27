#ifndef ASYNCBASE_HPP
#define ASYNCBASE_HPP

#include <vector>
#include <memory>
#include <functional>

namespace gf {

//namespace priv {
//template <typename R, typename B, typename ... Args>
//class ThenImpl {
//public:
//    using Fn = B(Args...);
//    using ResultType = R;

//    ThenImpl(const Fn& fun) : m_fun(fun) { }

//    ThenImpl(Fn&& fun) : m_fun(std::move(fun)) { }

//    virtual R then(std::function<B(Args...)>&& fn) = 0;

//    virtual R then(const std::function<B(Args...)>& fn) = 0;

//protected:
//    Fn m_fun;
//};

//template <typename Parent, typename A, typename B>
//class AsyncThenImpl : public Parent::Impl {

//};
//}

template <typename T, typename E>
class AsyncBase;
template <typename T, typename E>
using AsyncBasePtr = std::shared_ptr<AsyncBase<T, E>>;
template <typename T, typename E>
using AsyncBaseWeakPtr = std::weak_ptr<AsyncBase<T, E>>;

template <typename T, typename E>
struct AsyncLink {
    AsyncBasePtr<T, E> async;
    std::function<void(T)> linkf;
};

template <typename T, typename E>
class AsyncBase : public std::enable_shared_from_this<AsyncBase<T, E>>
{
public:
    AsyncBase();

    virtual ~AsyncBase();

    bool isResolved() const;

    bool isErrored() const;

    bool isErrorPending() const;

    bool isFulfilled() const;

    bool isPending() const;

    AsyncBasePtr<T, E> errorThen(std::function<T(E&)>&& fn);

    AsyncBasePtr<T, E> errorThen(const std::function<T(E&)>& fn);

    template <typename A>
    AsyncBasePtr<A, E> then(std::function<A(T)>&& fn);

    template <typename A>
    AsyncBasePtr<A, E> then(const std::function<A(T)>& fn);

    virtual void unlink(AsyncBasePtr<T, E> to);

    virtual bool isLinked(AsyncBasePtr<T, E> to);

    template <typename A, typename B>
    static void link(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, std::function<B(A)>&& fn);

    template <typename A, typename B>
    static void link(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, const std::function<B(A)>& fn);

    template <typename A, typename B>
    static void immediateLinkUpdate(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, std::function<B(A)>&& fn);

    template <typename A, typename B>
    static void immediateLinkUpdate(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, const std::function<B(A)>& fn);

    virtual void handleResolve(T value);

    template <typename Error>
    void handleError(Error& error);

    void handleError(std::exception_ptr error);
protected:
    virtual AsyncBasePtr<T, E> errorThenImpl(std::function<T(E&)>&& fn);

    virtual AsyncBasePtr<T, E> errorThenImpl(const std::function<T(E&)>& fn);

    virtual AsyncBasePtr<T, E> thenImpl(std::function<T(T)>&& fn);

    virtual AsyncBasePtr<T, E> thenImpl(const std::function<T(T)>& fn);

    void resolve(T value);

    void onResolve(T value);

    void onError(E& value);

    template <typename Error>
    void processError(Error& error);

protected:
    T _val;
    bool _resolved;
    bool _fulfilled;
    bool _pending;
    std::vector<AsyncLink<T, E>> _update;
    std::unique_ptr<E> _errorVal;
    bool _errored;
    bool _errorPending;
    std::function<T(E&)> _errorMap;
    std::vector<std::function<void(E)>> _error;
};

}

#include <Grafit/System/Promise/AsyncBase.inl>
#endif // ASYNCBASE_HPP
