#ifndef STREAM_HPP
#define STREAM_HPP

#include <memory>
#include <exception>
#include <functional>
#include <Grafit/System/Promise/AsyncBase.hpp>

namespace gf {

template <typename T, typename E>
class Promise;
template <typename T, typename E>
using PromisePtr = std::shared_ptr<Promise<T, E>>;

template <typename T, typename E>
class Stream;
template <typename T, typename E>
using StreamPtr = std::shared_ptr<Stream<T, E>>;

template <typename T, typename E = std::exception>
class Stream : public AsyncBase<T, E> {
public:
    using Ptr = StreamPtr<T, E>;
    explicit Stream();

    StreamPtr<T, E> then(std::function<T (T)>&& fn);

    StreamPtr<T, E> then(const std::function<T (T)>& fn);

    template <typename Type, typename Error>
    bool detachStream(StreamPtr<Type, Error> stream);

    AsyncBasePtr<T, E> end();

protected:
    virtual AsyncBasePtr<T, E> thenImpl(std::function<T(T)>&& fn) override;

    virtual AsyncBasePtr<T, E> thenImpl(const std::function<T(T)>& fn) override;

private:
    void handleEnd();

protected:
    PromisePtr<T, E> m_promise;
    bool m_paused;
    bool m_end;
};

template<typename T, typename E>
Stream<T, E>::Stream()
    : AsyncBase<T, E>()
    , m_promise(std::make_shared<Promise<T, E>>())
    , m_paused(false)
    , m_end(false) {

}

template<typename T, typename E>
StreamPtr<T, E> Stream<T, E>::then(std::function<T (T)> &&fn) {
    return std::static_pointer_cast<Stream<T, E>>(thenImpl(std::move(fn)));
}

template<typename T, typename E>
StreamPtr<T, E> Stream<T, E>::then(const std::function<T (T)> &fn) {
    return std::static_pointer_cast<Stream<T, E>>(thenImpl(fn));
}

template<typename T, typename E>
template<typename Type, typename Error>
bool Stream<T, E>::detachStream(StreamPtr<Type, Error> stream) {
//    std::for_each(_update.begin(), _update.end(), [this, &stream](AsyncLink<T, E>& link) {
//        if (link.async == stream && this->m_promise) {
//            std::vector<AsyncLink<T, E>>& update = this->m_promise->_update;
//            update.erase(update.begin())
//        }
//    });
    return false;
}

template<typename T, typename E>
AsyncBasePtr<T, E> Stream<T, E>::thenImpl(std::function<T(T)>&& fn)
{
    StreamPtr<T, E> ret = std::make_shared<Stream<T, E>>();
    AsyncBase<T, E>::link(Stream<T, E>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<T, E>>(ret), std::move(fn));
    AsyncLink<T, E> link = {
        ret->m_promise,
        [ret](T x) {
            std::function<AsyncBasePtr<T, E>(T)> fn = [ret](T x) {
                return ret->end();
            };
        }
    };
    m_promise->_update.push_back(link);
    return ret;
}

template<typename T, typename E>
AsyncBasePtr<T, E> Stream<T, E>::thenImpl(const std::function<T(T)>& fn) {
    StreamPtr<T, E> ret = std::make_shared<Stream<T, E>>();
    AsyncBase<T, E>::link(Stream<T, E>::shared_from_this(),
                          std::static_pointer_cast<AsyncBase<T, E>>(ret), fn);
    return ret;
}

template <typename T, typename E>
void Stream<T, E>::handleEnd() {

}

template <typename T, typename E>
AsyncBasePtr<T, E> Stream<T, E>::end() {
    EventLoop::enqueue(std::bind(&Stream<T, E>::handleEnd, this));
    return Stream<T, E>::shared_from_this();
}

}

#endif // STREAM_HPP
