#ifndef DEFERRED
#define DEFERRED

#include <memory>
#include <iostream>
#include <exception>
#include <Grafit/System/Promise/AsyncBase.hpp>
#include <Grafit/System/Promise/Promise.hpp>
#include <Grafit/System/Promise/Stream.hpp>

namespace gf {
template <typename T>
class Deferred;
template <typename T>
using DeferredPtr = std::shared_ptr<Deferred<T>>;

template <typename T>
class Deferred : public AsyncBase<T> {
public:
    using Ptr = std::shared_ptr<Deferred<T>>;
    explicit Deferred() : AsyncBase<T>() { }

    void resolve(T value) {
        AsyncBase<T>::handleResolve(value);
    }

    PromisePtr<T> promise() {
        PromisePtr<T> ret = std::make_shared<Promise<T>>();
        AsyncLink<T> link = {
            ret,
            [ret](T x) {
                std::function<T(T)> fn = [](T x) {
                    return x;
                };
                ret->handleResolve(fn(x));
            }
        };
        this->_update.push_back(link);
        return ret;
    }

    StreamPtr<T> stream() {
        StreamPtr<T> ret = std::make_shared<Stream<T>>();
        AsyncLink<T> link = {
            ret,
            [ret](T x) {
                std::function<T(T)> fn = [](T x) {
                    return x;
                };
                ret->handleResolve(fn(x));
            }
        };
        this->_update.push_back(link);
        return ret;
    }

private:
    static T _resolve(T x) {
        return x;
    }
};

}
#endif
