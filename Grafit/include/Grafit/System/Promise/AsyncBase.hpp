#ifndef ASYNCBASE_HPP
#define ASYNCBASE_HPP

#include <vector>
#include <memory>
#include <functional>
#include <Grafit/System/Promise/Any.hpp>
#include <Grafit/System/Promise/Optional.hpp>

namespace gf {

class IAsyncBase;
using IAsyncBasePtr = std::shared_ptr<IAsyncBase>;
template <typename T>
class AsyncBase;
template <typename T>
using AsyncBasePtr = std::shared_ptr<AsyncBase<T>>;
template <typename T>
using AsyncBaseWeakPtr = std::weak_ptr<AsyncBase<T>>;

template <typename T>
struct AsyncLink {
    IAsyncBasePtr async;
    std::function<void(T)> linkf;
};

class IAsyncBase {
public:
	virtual ~IAsyncBase() {};

	virtual void resolveDone(Any value) = 0;

	virtual void resolveFail(std::exception_ptr value) = 0;

	virtual void resolveFail(std::exception& value) = 0;
};

template <typename T>
class AsyncBase : public IAsyncBase,
        public std::enable_shared_from_this<AsyncBase<T>>
{
public:
    AsyncBase();

    virtual ~AsyncBase();

    bool isResolved() const;

    bool isErrored() const;

    bool isErrorPending() const;

    bool isFulfilled() const;

    bool isPending() const;

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

	virtual void resolveDone(Any value);

	virtual void resolveFail(std::exception_ptr value);

	virtual void resolveFail(std::exception& value);

protected:
	virtual AsyncBasePtr<T> catchErrorImpl(std::function<void(std::exception_ptr)>&& fn);

	virtual AsyncBasePtr<T> catchErrorImpl(const std::function<void(std::exception_ptr)>& fn);
	
    virtual AsyncBasePtr<T> errorThenImpl(std::function<T(std::exception_ptr)>&& fn);

    virtual AsyncBasePtr<T> errorThenImpl(const std::function<T(std::exception_ptr)>& fn);

    void resolve(T value);

    void onResolve(T value);

    void onError(std::exception_ptr error);

	void processError(std::exception_ptr error);

protected:
    T _val;
    bool _resolved;
    bool _fulfilled;
    bool _pending;
    std::vector<AsyncLink<T>> _update;
    std::unique_ptr<std::exception> _errorVal;
    bool _errored;
    bool _errorPending;
    std::function<T(std::exception_ptr)> _errorMap;
    std::vector<std::function<void(std::exception_ptr)>> _error;
};

}

#include <Grafit/System/Promise/AsyncBase.inl>
#endif // ASYNCBASE_HPP
