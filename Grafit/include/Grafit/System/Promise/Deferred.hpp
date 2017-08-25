#ifndef DEFERRED
#define DEFERRED

#include <memory>
#include <exception>
#include <Grafit/System/Promise/AsyncBase.hpp>

namespace gf {
template <typename T, typename E>
class Promise;
template <typename T, typename E>
using PromisePtr = std::shared_ptr<Promise<T, E>>;

template <typename T, typename E = std::exception>
class Deferred : public AsyncBase<T, E> {
public:
    using Ptr = std::shared_ptr<Deferred<T, E>>;
    explicit Deferred() : AsyncBase<T, E>() { }

	void resolve(T value) {
        AsyncBase<T, E>::handleResolve(value);
	}

    virtual PromisePtr<T, E> promise() {
        AsyncBasePtr<T, E> this_ptr = Deferred<T, E>::shared_from_this();
        PromisePtr<T, E> ret = std::make_shared<Promise<T, E>>();
        AsyncLink<T, E> link = {
            ret,
            [ret](T x) {
                std::function<T(T)> fn = [](T x) { return x; };
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
