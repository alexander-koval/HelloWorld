#ifndef PROMISE_HPP
#define PROMISE_HPP

#include <memory>
#include <exception>
#include <Grafit/System/Promise/AsyncBase.hpp>

namespace gf {

template <typename T, typename E>
class Stream;
template <typename T, typename E>
class Promise;
template <typename T, typename E>
using PromisePtr = std::shared_ptr<Promise<T, E>>;

template <typename T, typename E = std::exception>
class Promise : public AsyncBase<T, E> {
friend class Stream<T, E>;
public:
    using Ptr = std::shared_ptr<Promise<T, E>>;
    explicit Promise();

    bool isRejected() const;

    void reject(E& error);

    PromisePtr<T, E> then(std::function<T(T)>&& fn);

    PromisePtr<T, E> then(const std::function<T(T)>& fn);

    PromisePtr<T, E> errorThen(std::function<T(E&)>&& fn);

    PromisePtr<T, E> errorThen(const std::function<T(E&)>& fn);

    virtual void handleResolve(T value) override;

    virtual void unlink(AsyncBasePtr<T, E> to) override;

    template <typename Type>
    static PromisePtr<Type, E> promise(Type value);

protected:
    virtual AsyncBasePtr<T, E> thenImpl(std::function<T(T)>&& fn) override;

    virtual AsyncBasePtr<T, E> thenImpl(const std::function<T(T)>& fn) override;

protected:
    bool _rejected;
};

template<typename T, typename E>
 Promise<T, E>::Promise()
        : AsyncBase<T, E>()
	, _rejected(false)
{

}

template<typename T, typename E>
 bool Promise<T, E>::isRejected() const
{
	return _rejected;
}

template<typename T, typename E>
void Promise<T, E>::reject(E& error)
{
     _rejected = true;
    handleError(error);
}

template<typename T, typename E>
PromisePtr<T, E> Promise<T, E>::then(std::function<T(T)>&& fn)
{
    return std::static_pointer_cast<Promise<T, E>>(thenImpl(std::move(fn)));
}

template<typename T, typename E>
PromisePtr<T, E> Promise<T, E>::then(const std::function<T(T)>& fn)
{
    return std::static_pointer_cast<Promise<T, E>>(thenImpl(fn));
}

template<typename T, typename E>
PromisePtr<T, E> Promise<T, E>::errorThen(std::function<T(E&)>&& fn)
{
    AsyncBasePtr<T, E> promise = AsyncBase<T, E>::errorThenImpl(std::move(fn));
    return std::static_pointer_cast<Promise<T, E>>(promise);
}

template<typename T, typename E>
PromisePtr<T, E> Promise<T, E>::errorThen(const std::function<T(E&)>& fn)
{
    AsyncBasePtr<T, E> promise = AsyncBase<T, E>::errorThenImpl(fn);
    return std::static_pointer_cast<Promise<T, E>>(promise);
}


template<typename T, typename E>
AsyncBasePtr<T, E> Promise<T, E>::thenImpl(std::function<T(T)>&& fn)
{
    PromisePtr<T, E> ret = std::make_shared<Promise<T, E>>();
    AsyncBase<T, E>::link(Promise<T, E>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<T, E>>(ret), std::move(fn));
    return ret;
}

template<typename T, typename E>
AsyncBasePtr<T, E> Promise<T, E>::thenImpl(const std::function<T(T)>& fn)
{
    PromisePtr<T, E> ret = std::make_shared<Promise<T, E>>();
    AsyncBase<T, E>::link(Promise<T, E>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<T, E>>(ret), fn);
    return ret;
}


template<typename T, typename E>
 void Promise<T, E>::handleResolve(T value)
{
    if (!this->_resolved) {
        this->resolve(value);
    } else {
        throw std::logic_error("Promise has already been resolved");
    }
}

template<typename T, typename E>
 void Promise<T, E>::unlink(AsyncBasePtr<T, E> to)
{
    EventLoop::enqueue([this, to]() {
        if (this->isFulfilled()) {
            this->_update.erase(std::remove_if(this->_update.begin(), this->_update.end(),
				[&to](AsyncLink<T, E>& link) {
                                    AsyncBasePtr<T, E> ptr = link.async;
                                    return ptr == to;
            }), this->_update.end());
        } else {
            std::logic_error e("Downstream Promise is not fullfilled");
            this->handleError(e);
        };
    });
}

template<typename T, typename E>
template<typename Type>
 PromisePtr<Type, E> Promise<T, E>::promise(Type value)
{
    PromisePtr<Type, E> ret = std::make_shared<Promise<Type, E>>();
	ret->handleResolve(value);
	return ret;
}
}
#endif // PROMISE_HPP
