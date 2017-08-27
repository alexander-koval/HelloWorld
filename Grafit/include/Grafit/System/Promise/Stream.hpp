#ifndef STREAM_HPP
#define STREAM_HPP

#include <memory>
#include <exception>
#include <functional>
#include <Grafit/System/Promise/AsyncBase.hpp>

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
public:
    using Ptr = StreamPtr<T>;
    explicit Stream();

    StreamPtr<T> then(std::function<T (T)>&& fn);

    StreamPtr<T> then(const std::function<T (T)>& fn);

    template <typename Type>
    bool detachStream(StreamPtr<Type> stream);

    AsyncBasePtr<T> end();

protected:
    virtual AsyncBasePtr<T> thenImpl(std::function<T(T)>&& fn) override;

    virtual AsyncBasePtr<T> thenImpl(const std::function<T(T)>& fn) override;

private:
    void handleEnd();

protected:
    PromisePtr<T> m_promise;
    bool m_paused;
    bool m_end;
};

template<typename T>
Stream<T>::Stream()
    : AsyncBase<T>()
    , m_promise(std::make_shared<Promise<T>>())
    , m_paused(false)
    , m_end(false) {

}

template<typename T>
StreamPtr<T> Stream<T>::then(std::function<T (T)> &&fn) {
    return std::static_pointer_cast<Stream<T>>(thenImpl(std::move(fn)));
}

template<typename T>
StreamPtr<T> Stream<T>::then(const std::function<T (T)> &fn) {
    return std::static_pointer_cast<Stream<T>>(thenImpl(fn));
}

template<typename T>
template<typename Type>
bool Stream<T>::detachStream(StreamPtr<Type> stream) {
//    std::for_each(_update.begin(), _update.end(), [this, &stream](AsyncLink<T>& link) {
//        if (link.async == stream && this->m_promise) {
//            std::vector<AsyncLink<T>>& update = this->m_promise->_update;
//            update.erase(update.begin())
//        }
//    });
    return false;
}

template<typename T>
AsyncBasePtr<T> Stream<T>::thenImpl(std::function<T(T)>&& fn)
{
    StreamPtr<T> ret = std::make_shared<Stream<T>>();
    AsyncBase<T>::link(Stream<T>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<T>>(ret), std::move(fn));
    AsyncLink<T> link = {
        ret->m_promise,
        [ret](T x) {
            std::function<AsyncBasePtr<T>(T)> fn = [ret](T x) {
                return ret->end();
            };
        }
    };
    m_promise->_update.push_back(link);
    return ret;
}

template<typename T>
AsyncBasePtr<T> Stream<T>::thenImpl(const std::function<T(T)>& fn) {
    StreamPtr<T> ret = std::make_shared<Stream<T>>();
    AsyncBase<T>::link(Stream<T>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<T>>(ret), fn);
    return ret;
}

template <typename T>
void Stream<T>::handleEnd() {

}

template <typename T>
AsyncBasePtr<T> Stream<T>::end() {
    EventLoop::enqueue(std::bind(&Stream<T>::handleEnd, this));
    return Stream<T>::shared_from_this();
}

}

#endif // STREAM_HPP
