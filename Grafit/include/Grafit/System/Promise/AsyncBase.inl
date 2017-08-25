#include <algorithm>
#include <functional>
#include <Grafit/System/Promise/AsyncBase.hpp>
#include <Grafit/System/Promise/EventLoop.hpp>

namespace gf {
template <typename T, typename E>
AsyncBase<T, E>::AsyncBase(AsyncBase<T, E>* d) 
	: _val()
	, _resolved(false)
	, _fulfilled(false)
	, _pending(false)
	, _update()
	, _error()
	, _errored(false)
	, _errorPending(false) 
{
	if (d != nullptr) {
		AsyncBase::link<T, T>(d, this, [](T x) -> T { return x; });
	}
}

template <typename T, typename E>
AsyncBase<T, E>::~AsyncBase() {
	int kkk = 0;
}

template<typename T, typename E>
inline bool AsyncBase<T, E>::isResolved() const
{
	return _resolved;
}

template<typename T, typename E>
inline bool AsyncBase<T, E>::isErrored() const
{
	return _errored;
}

template<typename T, typename E>
inline bool AsyncBase<T, E>::isErrorPending() const
{
	return _errorPending;
}

template<typename T, typename E>
inline bool AsyncBase<T, E>::isFulfilled() const
{
	return _fulfilled;
}

template<typename T, typename E>
inline bool AsyncBase<T, E>::isPending() const
{
	return _pending;
}

template<typename T, typename E>
inline void AsyncBase<T, E>::unlink(AsyncBase<T, E>* to)
{
    EventLoop::enqueue([this, &to]() {
		_update.erase(std::remove_if(_update.begin(), _update.end(), 
			[&to](AsyncLink<T, E>& link) {
			return link.async == to;
		}), _update.end());
	});
}

template<typename T, typename E>
inline bool AsyncBase<T, E>::isLinked(AsyncBase<T, E>* to)
{
	return std::any_of(_update.begin(), _update.end(), [&to](const AsyncLink<T, E>& link) {
		return link.async == to;
	});
}

template<typename T, typename E>
inline void AsyncBase<T, E>::handleResolve(T value)
{
	resolve(value);
}

template<typename T, typename E>
inline void AsyncBase<T, E>::handleError(E error)
{
	if (!_errorPending) {
		_errorPending = true;
		_errored = true;
		_errorVal = error;
        EventLoop::enqueue([this, &error]() {
			if (this->_errorMap.operator bool()) {
				this->onResolve(this->_errorMap(error));
			}
			else {
				this->onError(error);
			}
		});
	}
}

template<typename T, typename E>
inline void AsyncBase<T, E>::resolve(T value)
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
inline void AsyncBase<T, E>::onResolve(T value)
{
	_val = value;
	for (const AsyncLink<T, E>& up : _update) {
		up.linkf(value);
	}
	_fulfilled = true;
	_pending = false;
}

template<typename T, typename E>
inline void AsyncBase<T, E>::onError(E value)
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
inline AsyncBase<T, E>* AsyncBase<T, E>::then(const std::function<T(T)>& fn)
{
	AsyncBase<T, E>* ret = new AsyncBase<T, E>(nullptr);// _pimpl.then<T>(fn);
	link(this, ret, fn);
	return ret;
}

template<typename T, typename E>
inline AsyncBase<T, E>* AsyncBase<T, E>::errorThen(std::function<T(E)>&& fn)
{
	_errorMap = std::move(fn);
	return this;
}

template<typename T, typename E>
template<typename A, typename B>
inline void AsyncBase<T, E>::link(AsyncBase<A, E>* current, AsyncBase<B, E>* next, const std::function<B(A)>& fn)
{
	AsyncLink<A, E> link = { next, [=](A x) { next->handleResolve(fn(x)); } };
	current->_update.push_back(link);
}

template<typename T, typename E>
template<typename A, typename B>
inline void AsyncBase<T, E>::immediateLinkUpdate(AsyncBase<A, E>* current, AsyncBase<B, E>* next, const std::function<B(A)>& fn)
{
	if (current->isErrored() && !current->isErrorPending()) {
		//next->handleError(current->_errorVal);
	}
	if (current->isResolved() && !current->isPending()) {
		next->handleResolve(fn(current->_val));
	}
}

}
