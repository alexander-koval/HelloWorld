#ifndef DEFERRED
#define DEFERRED

#include <memory>
#include <iostream>
#include <exception>
#include <Grafit/System/Promise/AsyncBase.hpp>
#include <Grafit/System/Promise/Promise.hpp>
#include <Grafit/System/Promise/Stream.hpp>

namespace gf {
template <typename T, typename E = std::exception>
class Deferred : public AsyncBase<T, E> {
public:
    using Ptr = std::shared_ptr<Deferred<T, E>>;
    explicit Deferred() : AsyncBase<T, E>() { }

    void resolve(T value) {
        AsyncBase<T, E>::handleResolve(value);
    }

    virtual PromisePtr<T, E> promise() {
        PromisePtr<T, E> ret = std::make_shared<Promise<T, E>>();
        AsyncLink<T, E> link = {
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

    virtual StreamPtr<T, E> stream() {
        StreamPtr<T, E> ret = std::make_shared<Stream<T, E>>();
        AsyncLink<T, E> link = {
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
