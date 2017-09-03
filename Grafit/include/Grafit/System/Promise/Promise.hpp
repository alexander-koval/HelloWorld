#ifndef PROMISE_HPP
#define PROMISE_HPP

#include <memory>
#include <exception>
#include <Grafit/System/Promise/AsyncBase.hpp>

namespace gf {

template <typename T>
class Stream;
template <typename T>
class Promise;
template <typename T>
using PromisePtr = std::shared_ptr<Promise<T>>;

template <typename T>
class Promise : public AsyncBase<T> {
friend class Stream<T>;
public:
    using Ptr = std::shared_ptr<Promise<T>>;
    explicit Promise();

    bool isRejected() const;

    void reject(std::exception& error);

    template <typename A>
    PromisePtr<A> then(std::function<A(T)>&& fn);

    template <typename A>
    PromisePtr<A> then(const std::function<A(T)>& fn);

    PromisePtr<T> catchError(std::function<void(std::exception_ptr)>&& fn);

    PromisePtr<T> catchError(const std::function<void(std::exception_ptr)>& fn);

    PromisePtr<T> errorThen(std::function<T(std::exception_ptr)>&& fn);

    PromisePtr<T> errorThen(const std::function<T(std::exception_ptr)>& fn);

    virtual void handleResolve(T value) override;

    virtual void unlink(AsyncBasePtr<T> to) override;

    template <typename Type>
    static PromisePtr<Type> promise(Type value);

protected:
    bool _rejected;
};

template<typename T>
 Promise<T>::Promise()
        : AsyncBase<T>()
	, _rejected(false)
{

}

template<typename T>
 bool Promise<T>::isRejected() const
{
	return _rejected;
}

template<typename T>
void Promise<T>::reject(std::exception& error)
{
     _rejected = true;
     std::exception_ptr ptr = std::make_exception_ptr(error);
     AsyncBase<T>::handleError(ptr);
}

template<typename T>
template<typename A>
PromisePtr<A> Promise<T>::then(std::function<A(T)>&& fn)
{
    PromisePtr<A> ret = std::make_shared<Promise<A>>();
    AsyncBase<T>::link(Promise<T>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<A>>(ret), std::move(fn));
    return ret;
}

template<typename T>
template<typename A>
PromisePtr<A> Promise<T>::then(const std::function<A(T)>& fn)
{
    PromisePtr<A> ret = std::make_shared<Promise<A>>();
    AsyncBase<T>::link(Promise<T>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<A>>(ret), fn);
    return ret;
}

template<typename T>
PromisePtr<T> Promise<T>::catchError(std::function<void(std::exception_ptr)>&& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::catchErrorImpl(std::move(fn));
    return std::static_pointer_cast<Promise<T>>(promise);
}

template<typename T>
PromisePtr<T> Promise<T>::catchError(const std::function<void(std::exception_ptr)>& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::catchErrorImpl(fn);
    return std::static_pointer_cast<Promise<T>>(promise);	
}

template<typename T>
PromisePtr<T> Promise<T>::errorThen(std::function<T(std::exception_ptr)>&& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::errorThenImpl(std::move(fn));
    return std::static_pointer_cast<Promise<T>>(promise);
}

template<typename T>
PromisePtr<T> Promise<T>::errorThen(const std::function<T(std::exception_ptr)>& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::errorThenImpl(fn);
    return std::static_pointer_cast<Promise<T>>(promise);
}

template<typename T>
 void Promise<T>::handleResolve(T value)
{
    if (!this->_resolved) {
        this->resolve(value);
    } else {
        throw std::logic_error("Promise has already been resolved");
    }
}

template<typename T>
 void Promise<T>::unlink(AsyncBasePtr<T> to)
{
    EventLoop::enqueue([this, to]() {
        if (this->isFulfilled()) {
            this->_update.erase(std::remove_if(this->_update.begin(), this->_update.end(),
                                [&to](AsyncLink<T>& link) {
                                    IAsyncBasePtr ptr = link.async;
                                    return ptr == to;
            }), this->_update.end());
        } else {
            std::logic_error e("Downstream Promise is not fullfilled");
            this->handleError(e);
        };
    });
}

template<typename T>
template<typename Type>
 PromisePtr<Type> Promise<T>::promise(Type value)
{
    PromisePtr<Type> ret = std::make_shared<Promise<Type>>();
	ret->handleResolve(value);
	return ret;
}
}
#endif // PROMISE_HPP
