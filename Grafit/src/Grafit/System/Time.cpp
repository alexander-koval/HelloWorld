#include <Grafit/System/Time.hpp>

namespace gf {

const Time Time::Zero;


////////////////////////////////////////////////////////////
Time::Time() :
m_microseconds(0)
{
}


////////////////////////////////////////////////////////////
float Time::asSeconds() const
{
    return m_microseconds / 1000000.f;
}


////////////////////////////////////////////////////////////
Int32 Time::asMilliseconds() const
{
    return static_cast<Int32>(m_microseconds / 1000);
}


////////////////////////////////////////////////////////////
Int64 Time::asMicroseconds() const
{
    return m_microseconds;
}


////////////////////////////////////////////////////////////
Time::Time(Int64 microseconds) :
m_microseconds(microseconds)
{
}


////////////////////////////////////////////////////////////
Time seconds(float amount)
{
    return Time(static_cast<Int64>(amount * 1000000));
}


////////////////////////////////////////////////////////////
Time milliseconds(Int32 amount)
{
    return Time(static_cast<Int64>(amount) * 1000);
}


////////////////////////////////////////////////////////////
Time microseconds(Int64 amount)
{
    return Time(amount);
}


////////////////////////////////////////////////////////////
bool operator ==(Time left, Time right)
{
    return left.asMicroseconds() == right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator !=(Time left, Time right)
{
    return left.asMicroseconds() != right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator <(Time left, Time right)
{
    return left.asMicroseconds() < right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator >(Time left, Time right)
{
    return left.asMicroseconds() > right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator <=(Time left, Time right)
{
    return left.asMicroseconds() <= right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator >=(Time left, Time right)
{
    return left.asMicroseconds() >= right.asMicroseconds();
}


////////////////////////////////////////////////////////////
Time operator -(Time right)
{
    return microseconds(-right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time operator +(Time left, Time right)
{
    return microseconds(left.asMicroseconds() + right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator +=(Time& left, Time right)
{
    return left = left + right;
}


////////////////////////////////////////////////////////////
Time operator -(Time left, Time right)
{
    return microseconds(left.asMicroseconds() - right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator -=(Time& left, Time right)
{
    return left = left - right;
}


////////////////////////////////////////////////////////////
Time operator *(Time left, float right)
{
    return seconds(left.asSeconds() * right);
}


////////////////////////////////////////////////////////////
Time operator *(Time left, Int64 right)
{
    return microseconds(left.asMicroseconds() * right);
}


////////////////////////////////////////////////////////////
Time operator *(float left, Time right)
{
    return right * left;
}


////////////////////////////////////////////////////////////
Time operator *(Int64 left, Time right)
{
    return right * left;
}


////////////////////////////////////////////////////////////
Time& operator *=(Time& left, float right)
{
    return left = left * right;
}


////////////////////////////////////////////////////////////
Time& operator *=(Time& left, Int64 right)
{
    return left = left * right;
}


////////////////////////////////////////////////////////////
Time operator /(Time left, float right)
{
    return seconds(left.asSeconds() / right);
}


////////////////////////////////////////////////////////////
Time operator /(Time left, Int64 right)
{
    return microseconds(left.asMicroseconds() / right);
}


////////////////////////////////////////////////////////////
Time& operator /=(Time& left, float right)
{
    return left = left / right;
}


////////////////////////////////////////////////////////////
Time& operator /=(Time& left, Int64 right)
{
    return left = left / right;
}


////////////////////////////////////////////////////////////
float operator /(Time left, Time right)
{
    return left.asSeconds() / right.asSeconds();
}


////////////////////////////////////////////////////////////
Time operator %(Time left, Time right)
{
    return microseconds(left.asMicroseconds() % right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator %=(Time& left, Time right)
{
    return left = left % right;
}

} // namespace gf
