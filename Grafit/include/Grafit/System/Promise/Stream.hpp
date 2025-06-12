#ifndef STREAM_HPP
#define STREAM_HPP

#include <memory>
#include <exception>
#include <functional>
#include <Grafit/System/Promise/AsyncBase.hpp>
#include <Grafit/System/Promise/Optional.hpp>

namespace gf {

template <typename T>
class Promise;
template <typename T>
using PromisePtr = std::shared_ptr<Promise<T>>;

template <typename T>
class Stream;
template <typename T>
using StreamPtr = std::shared_ptr<Stream<T>>;

template <typename T>
class Stream : public AsyncBase<T> {
//friend class Stream;
public:
    explicit Stream();

    template <typename A>
    StreamPtr<A> then(std::function<A(T)>&& fn);

    template <typename A>
    StreamPtr<A> then(const std::function<A(T)>& fn);

    StreamPtr<T> catchError(std::function<void(std::exception)>&& fn);

    StreamPtr<T> catchError(const std::function<void(std::exception)>& fn);

    StreamPtr<T> errorThen(std::function<T(std::exception&)>&& fn);

    StreamPtr<T> errorThen(const std::function<T(std::exception&)>& fn);

    template <typename Type>
    bool detachStream(StreamPtr<Type> stream);

    StreamPtr<T> end();

private:
    void handleEnd();

protected:
    PromisePtr<T> _promise;
    bool _paused;
    bool _end;
};

template<typename T>
Stream<T>::Stream()
    : AsyncBase<T>()
    , _promise(std::make_shared<Promise<T>>())
    , _paused(false)
    , _end(false) {

}

template<typename T>
inline StreamPtr<T> Stream<T>::catchError(std::function<void(std::exception)>&& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::catchErrorImpl(std::move(fn));
    return std::static_pointer_cast<Stream<T>>(promise);
}

template<typename T>
inline StreamPtr<T> Stream<T>::catchError(const std::function<void(std::exception)>& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::catchErrorImpl(fn);
    return std::static_pointer_cast<Stream<T>>(promise);	
}

template<typename T>
inline StreamPtr<T> Stream<T>::errorThen(std::function<T(std::exception&)>&& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::errorThenImpl(std::move(fn));
    return std::static_pointer_cast<Stream<T>>(promise);
}

template<typename T>
inline StreamPtr<T> Stream<T>::errorThen(const std::function<T(std::exception&)>& fn)
{
    AsyncBasePtr<T> promise = AsyncBase<T>::errorThenImpl(fn);
    return std::static_pointer_cast<Stream<T>>(promise);
}

template<typename T>
template<typename A>
StreamPtr<A> Stream<T>::then(std::function<A(T)> &&fn) {
    StreamPtr<A> ret = std::make_shared<Stream<A>>();
    AsyncBase<T>::link(Stream<T>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<A>>(ret), std::move(fn));
    _promise->_update.push_back(AsyncLink<T>({
        ret->_promise,
        [ret](T x) { return ret->end(); }
    }));
	return ret;
}

template<typename T>
template<typename A>
StreamPtr<A> Stream<T>::then(const std::function<A(T)> &fn) {
    StreamPtr<A> ret = std::make_shared<Stream<A>>();
    AsyncBase<T>::link(Stream<T>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<A>>(ret), fn);
    _promise->_update.push_back(AsyncLink<T>({
        ret->_promise,
        [ret](T x) { return ret->end(); }
    }));
    return ret;
}

template<typename T>
template<typename Type>
bool Stream<T>::detachStream(StreamPtr<Type> stream) {
//    std::for_each(_update.begin(), _update.end(), [this, &stream](AsyncLink<T>& link) {
//        if (link.async == stream && this->_promise) {
//            std::vector<AsyncLink<T>>& update = this->_promise->_update;
//            update.erase(update.begin())
//        }
//    });
    return false;
}

template <typename T>
void Stream<T>::handleEnd() {
	if (this->isPending()) {
                EventLoop::enqueue(std::bind(&Stream<T>::handleEnd, this));
	}
	else if (_promise->isResolved()) {
		return;
	}
	else {
		_end = true;
                if (AsyncBase<T>::isResolved()) {
                        _promise->handleResolve(AsyncBase<T>::_val);
		}
		std::vector<AsyncLink<T>> newUpdate;
                std::swap(AsyncBase<T>::_update, newUpdate);
		std::vector<std::function<void(std::exception_ptr)>> newError;
                std::swap(AsyncBase<T>::_error, newError);
	}
}

template <typename T>
StreamPtr<T> Stream<T>::end() {
    EventLoop::enqueue(std::bind(&Stream<T>::handleEnd, this));
    return std::static_pointer_cast<Stream<T>>(Stream<T>::shared_from_this());
}

}

#endif // STREAM_HPP
