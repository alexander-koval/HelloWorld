#ifndef PROMISE_HPP
#define PROMISE_HPP

#include <exception>
#include <Grafit/System/Promise/AsyncBase.hpp>

namespace gf {
template <typename T, typename E = std::exception>
class Promise : public AsyncBase<T, E> {
public:
	explicit Promise(AsyncBase<T, E>* d = nullptr);

	bool isRejected() const;

	void reject();

	virtual Promise<T, E>* then(const std::function<T(T)>& fn) override;

	virtual void handleResolve(T value) override;

	virtual void unlink(AsyncBase<T, E>* to) override;

	template <typename Type>
	static Promise<Type, E>* promise(Type value);
protected:
	bool _rejected;
};

template<typename T, typename E>
inline Promise<T, E>::Promise(AsyncBase<T, E>* d)
	: AsyncBase<T, E>(d)
	, _rejected(false)
{

}

template<typename T, typename E>
inline bool Promise<T, E>::isRejected() const
{
	return _rejected;
}

template<typename T, typename E>
inline void Promise<T, E>::reject()
{
	_rejected = true;
	//handleError()
}

template<typename T, typename E>
inline Promise<T, E>* Promise<T, E>::then(const std::function<T(T)>& fn)
{
	Promise<T, E>* ret = new Promise<T, E>(nullptr);// _pimpl.then<T>(fn);
    AsyncBase<T, E>::link(this, ret, fn);
	return ret;
}

template<typename T, typename E>
inline void Promise<T, E>::handleResolve(T value)
{
    if (!this->_resolved) {
        this->resolve(value);
	}
}

template<typename T, typename E>
inline void Promise<T, E>::unlink(AsyncBase<T, E>* to)
{
    EventLoop::enqueue([this, &to]() {
        if (this->isFulfilled()) {
            this->_update.erase(std::remove_if(this->_update.begin(), this->_update.end(),
				[&to](AsyncLink<T, E>& link) {
				return link.async == to;
            }), this->_update.end());
		}
		else {
			//handleError();
		};
	});
}

template<typename T, typename E>
template<typename Type>
inline Promise<Type, E>* Promise<T, E>::promise(Type value)
{
	Promise<Type, E>* ret = new Promise<Type, E>();
	ret->handleResolve(value);
	return ret;
}
}
#endif // PROMISE_HPP
