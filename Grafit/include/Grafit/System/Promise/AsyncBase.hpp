#ifndef ASYNCBASE_HPP
#define ASYNCBASE_HPP

#include <vector>
#include <memory>
#include <functional>

namespace gf {

template <typename T>
class AsyncBase;
template <typename T>
using AsyncBasePtr = std::shared_ptr<AsyncBase<T>>;
template <typename T>
using AsyncBaseWeakPtr = std::weak_ptr<AsyncBase<T>>;

template <typename T>
struct AsyncLink {
    AsyncBasePtr<T> async;
    std::function<void(T)> linkf;
};

template <typename T>
class AsyncBase : public std::enable_shared_from_this<AsyncBase<T>>
{
public:
    AsyncBase();

    virtual ~AsyncBase();

    bool isResolved() const;

    bool isErrored() const;

    bool isErrorPending() const;

    bool isFulfilled() const;

    bool isPending() const;

    AsyncBasePtr<T> errorThen(std::function<T(std::exception&)>&& fn);

    AsyncBasePtr<T> errorThen(const std::function<T(std::exception&)>& fn);

    template <typename A>
    AsyncBasePtr<A> then(std::function<A(T)>&& fn);

    template <typename A>
    AsyncBasePtr<A> then(const std::function<A(T)>& fn);

    virtual void unlink(AsyncBasePtr<T> to);

    virtual bool isLinked(AsyncBasePtr<T> to);

    template <typename A, typename B>
    static void link(AsyncBasePtr<A> current, AsyncBasePtr<B> next, std::function<B(A)>&& fn);

    template <typename A, typename B>
    static void link(AsyncBasePtr<A> current, AsyncBasePtr<B> next, const std::function<B(A)>& fn);

    template <typename A, typename B>
    static void immediateLinkUpdate(AsyncBasePtr<A> current, AsyncBasePtr<B> next, std::function<B(A)>&& fn);

    template <typename A, typename B>
    static void immediateLinkUpdate(AsyncBasePtr<A> current, AsyncBasePtr<B> next, const std::function<B(A)>& fn);

    virtual void handleResolve(T value);

    template <typename Error>
    void handleError(Error& error);

    void handleError(std::exception_ptr error);
protected:
    virtual AsyncBasePtr<T> errorThenImpl(std::function<T(std::exception&)>&& fn);

    virtual AsyncBasePtr<T> errorThenImpl(const std::function<T(std::exception&)>& fn);

    virtual AsyncBasePtr<T> thenImpl(std::function<T(T)>&& fn);

    virtual AsyncBasePtr<T> thenImpl(const std::function<T(T)>& fn);

    void resolve(T value);

    void onResolve(T value);

    void onError(std::exception& value);

    template <typename Error>
    void processError(Error& error);

protected:
    T _val;
    bool _resolved;
    bool _fulfilled;
    bool _pending;
    std::vector<AsyncLink<T>> _update;
    std::unique_ptr<std::exception> _errorVal;
    bool _errored;
    bool _errorPending;
    std::function<T(std::exception&)> _errorMap;
    std::vector<std::function<void(std::exception&)>> _error;
};

}

#include <Grafit/System/Promise/AsyncBase.inl>
#endif // ASYNCBASE_HPP
