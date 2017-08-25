#ifndef DEFERRED
#define DEFERRED

#include <exception>
#include <Grafit/System/Promise/AsyncBase.hpp>

namespace gf {
template <typename T, typename E>
class Promise;

template <typename T, typename E = std::exception>
class Deferred : public AsyncBase<T, E> {
public:
    explicit Deferred() : AsyncBase<T, E>() { }

	void resolve(T value) {
        AsyncBase<T, E>::handleResolve(value);
	}

	virtual Promise<T, E>* promise() {
		return new Promise<T, E>(this);
	}
};

}
#endif
