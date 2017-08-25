#include <algorithm>
#include <functional>
#include <iostream>
#include <Grafit/System/Promise/AsyncBase.hpp>
#include <Grafit/System/Promise/EventLoop.hpp>

namespace gf {
template <typename T, typename E>
AsyncBase<T, E>::AsyncBase(AsyncBasePtr<T, E> d)
	: _val()
	, _resolved(false)
	, _fulfilled(false)
	, _pending(false)
	, _update()
	, _error()
	, _errored(false)
	, _errorPending(false) 
    , _errorMap()
{
//    if (d.get() != nullptr) {
//        AsyncBase::link<T, E>(d, AsyncBase<T, E>::shared_from_this(), [](T x) -> T { return x; });
//	}
}

template <typename T, typename E>
AsyncBase<T, E>::~AsyncBase() {
	int kkk = 0;
    std::cout << "DESTROY" << std::endl;
}

template<typename T, typename E>
bool AsyncBase<T, E>::isResolved() const
{
	return _resolved;
}

template<typename T, typename E>
bool AsyncBase<T, E>::isErrored() const
{
	return _errored;
}

template<typename T, typename E>
bool AsyncBase<T, E>::isErrorPending() const
{
	return _errorPending;
}

template<typename T, typename E>
bool AsyncBase<T, E>::isFulfilled() const
{
	return _fulfilled;
}

template<typename T, typename E>
bool AsyncBase<T, E>::isPending() const
{
	return _pending;
}

template<typename T, typename E>
void AsyncBase<T, E>::unlink(AsyncBasePtr<T, E> to)
{
    EventLoop::enqueue([this, &to]() {
        this->_update.erase(std::remove_if(this->_update.begin(), this->_update.end(),
            [&to](AsyncLink<T, E>& link) {
            return link.async == to;
        }), _update.end());
    });
}

template<typename T, typename E>
bool AsyncBase<T, E>::isLinked(AsyncBasePtr<T, E> to)
{
    return std::any_of(this->_update.begin(), this->_update.end(), [&to](const AsyncLink<T, E>& link) {
        return link.async == to;
    });
}

template<typename T, typename E>
void AsyncBase<T, E>::handleResolve(T value)
{
	resolve(value);
}

template<typename T, typename E>
void AsyncBase<T, E>::handleError(E error)
{
	if (!_errorPending) {
		_errorPending = true;
		_errored = true;
		_errorVal = error;
        EventLoop::enqueue([this, &error]() {
			if (this->_errorMap.operator bool()) {
                try {
                    this->onResolve(this->_errorMap(error));
                } catch(E e) {
                    onError(e);
                }
			}
			else {
				this->onError(error);
			}
		});
	}
}

template<typename T, typename E>
void AsyncBase<T, E>::resolve(T value)
{
	if (_pending) {
        EventLoop::enqueue(std::bind(&AsyncBase<T, E>::resolve, this, value));
	}
	else {
		_resolved = true;
		_pending = true;
        EventLoop::enqueue(std::bind(&AsyncBase<T, E>::onResolve, this, value));
}
}

template<typename T, typename E>
void AsyncBase<T, E>::onResolve(T value)
{
	_val = value;
    for (AsyncLink<T, E>& up : this->_update) {
        try {
            up.linkf(value);
        } catch(E e) {
            up.async->handleError(e);
        }
	}
	_fulfilled = true;
	_pending = false;
}

template<typename T, typename E>
void AsyncBase<T, E>::onError(E value)
{
	if (!_error.empty()) {
		std::for_each(_error.begin(), _error.end(), [&value](std::function<void(E)>& ef) {
			ef(value);
		});
	}
	else if (!_update.empty()) {
		std::for_each(_update.begin(), _update.end(), [&value](AsyncLink<T, E>& link) {
			link.async->handleError(value);
		});
	}
	_errorPending = false;
}

template<typename T, typename E>
AsyncBasePtr<T, E> AsyncBase<T, E>::then(std::function<T(T)>&& fn)
{
    return thenImpl(fn);
}

template<typename T, typename E>
AsyncBasePtr<T, E> AsyncBase<T, E>::then(const std::function<T(T)>& fn)
{
    return thenImpl(fn);
}

template<typename T, typename E>
AsyncBasePtr<T, E> AsyncBase<T, E>::thenImpl(std::function<T(T)>&& fn)
{
    AsyncBasePtr<T, E> ret = std::make_shared<AsyncBase<T, E>>(nullptr);// _pimpl.then<T>(fn);
    AsyncBase<T, E>::link(AsyncBase<T, E>::shared_from_this(), ret, std::move(fn));
    return ret;
}

template<typename T, typename E>
AsyncBasePtr<T, E> AsyncBase<T, E>::thenImpl(const std::function<T(T)>& fn)
{
    AsyncBasePtr<T, E> ret = std::make_shared<AsyncBase<T, E>>(nullptr);// _pimpl.then<T>(fn);
    AsyncBase<T, E>::link(AsyncBase<T, E>::shared_from_this(), ret, fn);
    return ret;
}

template<typename T, typename E>
AsyncBasePtr<T, E> AsyncBase<T, E>::errorThen(std::function<T(E)>&& fn)
{
    _errorMap = std::move(fn);
    return AsyncBase<T, E>::shared_from_this();
}

template<typename T, typename E>
AsyncBasePtr<T, E> AsyncBase<T, E>::errorThen(const std::function<T(E)>& fn)
{
    _errorMap = fn;
    return AsyncBase<T, E>::shared_from_this();
}

template<typename T, typename E>
template<typename A, typename B>
void AsyncBase<T, E>::link(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, std::function<B(A)>&& fn)
{
    AsyncLink<A, E> link = {
        next,
        [next, fn](A x) {
            next->handleResolve(fn(x));
        }
    };
    current->_update.push_back(link);
}

template<typename T, typename E>
template<typename A, typename B>
void AsyncBase<T, E>::link(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, const std::function<B(A)>& fn)
{
    AsyncLink<A, E> link = {
        next,
        [next, &fn](A x) {
            if (next.get() != nullptr) {
                next->handleResolve(fn(x));
            }
        }
    };
    current->_update.push_back(link);
}

template<typename T, typename E>
template<typename A, typename B>
void AsyncBase<T, E>::immediateLinkUpdate(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, std::function<B(A)>&& fn)
{
    if (current->isErrored() && !current->isErrorPending()) {
        //next->handleError(current->_errorVal);
    }
    if (current->isResolved() && !current->isPending()) {
        next->handleResolve(fn(current->_val));
    }
}

template<typename T, typename E>
template<typename A, typename B>
void AsyncBase<T, E>::immediateLinkUpdate(AsyncBasePtr<A, E> current, AsyncBasePtr<B, E> next, const std::function<B(A)>& fn)
{
    if (current->isErrored() && !current->isErrorPending()) {
        //next->handleError(current->_errorVal);
    }
    if (current->isResolved() && !current->isPending()) {
        next->handleResolve(fn(current->_val));
    }
}

}
