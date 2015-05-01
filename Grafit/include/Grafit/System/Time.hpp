#ifndef TIME_HPP
#define TIME_HPP

#include <Grafit/System/Types.hpp>

namespace gf {

class Time {
public:

    Time();

    float asSeconds() const;

    Int32 asMilliseconds() const;

    Int64 asMicroseconds() const;

    static const Time Zero; ///< Predefined "zero" time value

private:

    friend Time seconds(float);
    friend Time milliseconds(Int32);
    friend Time microseconds(Int64);

    explicit Time(Int64 microseconds);

private:

    Int64 m_microseconds; ///< Time value stored as microseconds
};

Time seconds(float amount);

Time milliseconds(Int32 amount);

Time microseconds(Int64 amount);

bool operator ==(Time left, Time right);

bool operator !=(Time left, Time right);

bool operator <(Time left, Time right);

bool operator >(Time left, Time right);

bool operator <=(Time left, Time right);

bool operator >=(Time left, Time right);

Time operator -(Time right);

Time operator +(Time left, Time right);

Time& operator +=(Time& left, Time right);

Time operator -(Time left, Time right);

Time& operator -=(Time& left, Time right);

Time operator *(Time left, float right);

Time operator *(Time left, Int64 right);

Time operator *(float left, Time right);

Time operator *(Int64 left, Time right);

Time& operator *=(Time& left, float right);

Time& operator *=(Time& left, Int64 right);

Time operator /(Time left, float right);

Time operator /(Time left, Int64 right);

Time& operator /=(Time& left, float right);

Time& operator /=(Time& left, Int64 right);

float operator /(Time left, Time right);

Time operator %(Time left, Time right);

Time& operator %=(Time& left, Time right);

} // namespace gf

#endif // TIME_HPP

