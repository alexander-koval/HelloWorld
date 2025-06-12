#ifndef GRAFIT_ANY
#define GRAFIT_ANY

#include <exception>
#include <memory>
#include <typeinfo>
#include <type_traits>

namespace gf {
class Any;

template<class Type> Type castAny(Any&);
template<class Type> Type castAny(const Any&);
template<class Type> Type* castAny(Any*);
template<class Type> const Type* castAny(const Any*);

struct bad_any_cast : public std::bad_cast {};

class Any {
public:

	template<class Type> friend
		Type castAny(Any&);

	template<class Type>
	friend Type castAny(const Any&);

	template<class Type>
	friend Type* castAny(Any*);

	template<class Type>
	friend const Type* castAny(const Any*);

	Any()
		: ptr(nullptr)
	{}

	Any(Any&& x)
		: ptr(std::move(x.ptr))
	{}

	Any(const Any& x) {
		if (x.ptr)
			ptr = x.ptr->clone();
	}

	template<class Type> Any(const Type& x)
		: ptr(new Concrete<typename std::decay<const Type>::type>(x))
	{}

	Any& operator=(Any&& rhs) {
		ptr = std::move(rhs.ptr);
		return (*this);
	}

	Any& operator=(const Any& rhs) {
		ptr = std::move(Any(rhs).ptr);
		return (*this);
	}

	template<class T> Any& operator=(T&& x) {
		ptr.reset(new Concrete<typename std::decay<T>::type>(typename std::decay<T>::type(x)));
		return (*this);
	}

	template<class T> Any& operator=(const T& x) {
		ptr.reset(new Concrete<typename std::decay<T>::type>(typename std::decay<T>::type(x)));
		return (*this);
	}

	void clear() {
		ptr.reset(nullptr);
	}

	bool empty() const {
		return ptr == nullptr;
	}

	const std::type_info& type() const {
		return (!empty())
			? ptr->type()
			: typeid(void);
	}

private:

	struct Placeholder {

		virtual std::unique_ptr<Placeholder> clone() const = 0;
		virtual const std::type_info& type() const = 0;
		virtual ~Placeholder() {}

	};

	template<class T>
	struct Concrete : public Placeholder {

		Concrete(T&& x)
			: value(std::move(x))
		{}

		Concrete(const T& x)
			: value(x)
		{}

		virtual std::unique_ptr<Placeholder> clone() const override {
			return std::unique_ptr<Placeholder>(new Concrete<T>(value));
		}

		virtual const std::type_info& type() const override {
			return typeid(T);
		}

		T value;

	};

	std::unique_ptr<Placeholder> ptr;

};

template<class Type>
Type castAny(Any& val) {
	if (val.ptr->type() != typeid(Type))
		throw bad_any_cast();
	return static_cast<Any::Concrete<Type>*>(val.ptr.get())->value;
}

template<class Type>
Type castAny(const Any& val) {
	return castAny<Type>(Any(val));
}

template<class Type>
Type* castAny(Any* ptr) {
	return dynamic_cast<Type*>(ptr->ptr.get());
}

template<class Type>
const Type* castAny(const Any* ptr) {
	return dynamic_cast<const Type*>(ptr->ptr.get());
}

}

#endif // __BOT_ANY__
