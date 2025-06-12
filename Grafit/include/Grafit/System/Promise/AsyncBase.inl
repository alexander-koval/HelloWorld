#include <algorithm>
#include <functional>

namespace gf {
template <typename T>
AsyncBase<T>::AsyncBase()
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

}

template <typename T>
AsyncBase<T>::~AsyncBase() {

}

template<typename T>
bool AsyncBase<T>::isResolved() const
{
	return _resolved;
}

template<typename T>
bool AsyncBase<T>::isErrored() const
{
	return _errored;
}

template<typename T>
bool AsyncBase<T>::isErrorPending() const
{
	return _errorPending;
}

template<typename T>
bool AsyncBase<T>::isFulfilled() const
{
	return _fulfilled;
}

template<typename T>
bool AsyncBase<T>::isPending() const
{
	return _pending;
}

template<typename T>
void AsyncBase<T>::unlink(AsyncBasePtr<T> to)
{
    EventLoop::enqueue([this, to]() {
        this->_update.erase(std::remove_if(this->_update.begin(), this->_update.end(),
            [&to](AsyncLink<T>& link) {
                                if (IAsyncBasePtr ptr = link.async) {
                                    return ptr == to;
                                }
                                return false;
                            }), _update.end());
    });
}

template<typename T>
bool AsyncBase<T>::isLinked(AsyncBasePtr<T> to)
{
    return std::any_of(this->_update.begin(), this->_update.end(), [&to](const AsyncLink<T>& link) {
        if (IAsyncBasePtr ptr = link.async) {
            return ptr == to;
        }
        return false;
    });
}

template<typename T>
void AsyncBase<T>::handleResolve(T value)
{
	resolve(value);
}

template<typename T>
template<typename Error>
void AsyncBase<T>::handleError(Error& error)
{
    if (!_errorPending) {
        _errorPending = true;
        _errored = true;
		handleError(std::make_exception_ptr(error));
    }
}

template<typename T>
void AsyncBase<T>::handleError(std::exception_ptr error)
{
    if (!_errorPending) {
        _errorPending = true;
        _errored = true;
		AsyncBasePtr<T> this_ptr = AsyncBase<T>::shared_from_this();
        EventLoop::enqueue([this_ptr, error]() {
			if (error) {
				this_ptr->processError(error);
			}
        });
    }
}

template<typename T>
inline void AsyncBase<T>::resolveDone(Any value)
{
        T data = gf::castAny<T>(value);
	handleResolve(data);
}

template<typename T>
inline void AsyncBase<T>::resolveFail(std::exception_ptr value)
{
	handleError(value);
}

template<typename T>
inline void AsyncBase<T>::resolveFail(std::exception & value)
{
	handleError(value);
}

template<typename T>
void AsyncBase<T>::processError(std::exception_ptr error)
{
   if (this->_errorMap.operator bool()) {
        try {
            this->onResolve(this->_errorMap(error));
        } catch(std::exception& e) {
            this->onError(std::make_exception_ptr(e));
        }
    } else {
        this->onError(error);
    }
}

template<typename T>
void AsyncBase<T>::resolve(T value)
{
	if (_pending) {
            EventLoop::enqueue(std::bind(&AsyncBase<T>::resolve,
                                         AsyncBase<T>::shared_from_this(), value));
        }
	else {
            _resolved = true;
            _pending = true;
            EventLoop::enqueue(std::bind(&AsyncBase<T>::onResolve,
                    AsyncBase<T>::shared_from_this(), value));
}
}

template<typename T>
void AsyncBase<T>::onResolve(T value)
{
    _val = value;
    for (AsyncLink<T>& up : this->_update) {
        IAsyncBasePtr ptr = up.async;
        if (ptr != nullptr) {
        try {
               up.linkf(value);
            } catch (...) {
                std::exception_ptr e = std::current_exception();
				ptr->resolveFail(e);
            }
        }
    }
    _fulfilled = true;
    _pending = false;
}

template<typename T>
void AsyncBase<T>::onError(std::exception_ptr value)
{
	if (!_error.empty()) {
                std::for_each(_error.begin(), _error.end(), [&value](std::function<void(std::exception_ptr)>& ef) {
			ef(value);
		});
	}
	else if (!_update.empty()) {
                std::for_each(_update.begin(), _update.end(), [&value](AsyncLink<T>& link) {
                    if (IAsyncBasePtr ptr = link.async) {
                        ptr->resolveFail(value);
                    }
		});
	}
	_errorPending = false;
}

template<typename T>
AsyncBasePtr<T> AsyncBase<T>::catchErrorImpl(std::function<void(std::exception_ptr)>&& fn)
{
	_error.push_back(std::move(fn));
    return AsyncBase<T>::shared_from_this();
}

template<typename T>
AsyncBasePtr<T> AsyncBase<T>::catchErrorImpl(const std::function<void(std::exception_ptr)>& fn)
{
	_error.push_back(fn);
    return AsyncBase<T>::shared_from_this();
}

template<typename T>
AsyncBasePtr<T> AsyncBase<T>::errorThenImpl(std::function<T(std::exception_ptr)>&& fn)
{
    _errorMap = std::move(fn);
    return AsyncBase<T>::shared_from_this();
}

template<typename T>
AsyncBasePtr<T> AsyncBase<T>::errorThenImpl(const std::function<T(std::exception_ptr)>& fn)
{
    _errorMap = fn;
    return AsyncBase<T>::shared_from_this();
}


//#ifdef PROMHX_ERROR
template<typename T>
template<typename A, typename B>
void AsyncBase<T>::link(AsyncBasePtr<A> current, AsyncBasePtr<B> next, std::function<B(A)>&& fn)
{
    AsyncLink<A> link = {
        next,
        [next, fn](A x) {
            next->handleResolve(fn(x));
        }
    };
    current->_update.push_back(link);
}
//#else

template<typename T>
template<typename A, typename B>
void AsyncBase<T>::link(AsyncBasePtr<A> current, AsyncBasePtr<B> next, const std::function<B(A)>& fn)
{
    AsyncLink<A> link = {
        next,
        [next, fn](A x) {
			//std::bind(next->resolveFail, next);
            next->handleResolve(fn(x));
        }
    };
    current->_update.push_back(link);
}
//#endif

template<typename T>
template<typename A, typename B>
void AsyncBase<T>::immediateLinkUpdate(AsyncBasePtr<A> current, AsyncBasePtr<B> next, std::function<B(A)>&& fn)
{
    if (current->isErrored() && !current->isErrorPending()) {
        next->handleError(current->_errorVal);
    }
    if (current->isResolved() && !current->isPending()) {
        next->handleResolve(fn(current->_val));
    }
}

template<typename T>
template<typename A, typename B>
void AsyncBase<T>::immediateLinkUpdate(AsyncBasePtr<A> current, AsyncBasePtr<B> next, const std::function<B(A)>& fn)
{
    if (current->isErrored() && !current->isErrorPending()) {
        next->handleError(current->_errorVal);
    }
    if (current->isResolved() && !current->isPending()) {
        next->handleResolve(fn(current->_val));
    }
}

}
