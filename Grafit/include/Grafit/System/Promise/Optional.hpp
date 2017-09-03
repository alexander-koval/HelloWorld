#ifndef __BOT_OPTIONAL__
#define __BOT_OPTIONAL__

#include <algorithm>
#include <exception>

namespace bot {

template <typename T>
class Optional
{
public:
	Optional() :
		_value(),
		_isSpecified(false)
	{
	}

	Optional(const T& value)
		: _value(value)
		, _isSpecified(true)
	{
	}

	Optional(const Optional& other)
		:_value(other._value)
		, _isSpecified(other._isSpecified)
	{
	}

	~Optional()
	{
	}

	Optional& assign(const T& value)
	{
		_value = value;
		_isSpecified = true;
		return *this;
	}

	Optional& assign(const Optional& other)
	{
		Optional tmp(other);
		swap(tmp);
		return *this;
	}

	Optional& operator = (const T& value)
	{
		return assign(value);
	}

	Optional& operator = (const Optional& other)
	{
		return assign(other);
	}

	void swap(Optional& other)
	{
		std::swap(_value, other._value);
		std::swap(_isSpecified, other._isSpecified);
	}

	const T& value() const
	{
		if (_isSpecified)
			return _value;
		else
			throw std::bad_exception();
	}

	const T& value(const T& deflt) const
	{
		return _isSpecified ? _value : deflt;
	}

	bool isSpecified() const
	{
		return _isSpecified;
	}

	void clear()
	{
		_isSpecified = false;
	}

private:
	T _value;
	bool _isSpecified;
};


template <typename T>
inline void swap(Optional<T>& n1, Optional<T>& n2)
{
	n1.swap(n2);
}

}
#endif // !__BOT_OPTIONAL__
