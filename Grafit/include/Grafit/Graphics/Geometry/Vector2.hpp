#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>

namespace gf {
template <typename T>
class Vector2 {
public:
    Vector2(void);

    Vector2(T x, T y);

    template <typename U>
    explicit Vector2(const Vector2<U>& vector);

    float getLength(void) const;

    float getLengthSq(void) const;

    float getDistance(const Vector2<T>& other);

    float getDistanceSq(const Vector2<T>& other);

    float getAngle(void) const;

    float getAngleBetween(const Vector2<T>& other) const;

    float getRangedAngleBetween(const Vector2<T>& other) const;

    float dot(const Vector2<T> other) const;

    float cross(const Vector2<T> other) const;

    Vector2<T> getPerp(void) const;

    Vector2<T> getRPerp(void) const;

    Vector2<T> project(const Vector2<T> other) const;

    Vector2<T> rotate(float angle) const;

    Vector2<T> rotate(float angle, Vector2<T> origin) const;

    Vector2<T> rotate(const Vector2<T> other) const;

    Vector2<T> unrotate(const Vector2<T> other) const;

    Vector2<T> normalize(void) const;

    Vector2<T> lerp(const Vector2<T> other, float alpha) const;

    T x;
    T y;
};

using Vector2I = Vector2<int>;
using Vector2U = Vector2<unsigned int>;
using Vector2F = Vector2<float>;
using Vector2D = Vector2<double>;

}

template <typename T>
gf::Vector2<T> operator -(const gf::Vector2<T>& right);

template <typename T>
gf::Vector2<T>& operator +=(gf::Vector2<T>& left, const gf::Vector2<T>& right);

template <typename T>
gf::Vector2<T>& operator -=(gf::Vector2<T>& left, const gf::Vector2<T>& right);

template <typename T>
gf::Vector2<T> operator +(const gf::Vector2<T>& left, const gf::Vector2<T>& right);

template <typename T>
gf::Vector2<T> operator -(const gf::Vector2<T>& left, const gf::Vector2<T>& right);

template <typename T>
gf::Vector2<T> operator *(const gf::Vector2<T>& left, T right);

template <typename T>
gf::Vector2<T> operator *(T left, const gf::Vector2<T>& right);

template <typename T>
gf::Vector2<T>& operator *=(gf::Vector2<T>& left, T right);

template <typename T>
gf::Vector2<T> operator /(const gf::Vector2<T>& left, T right);

template <typename T>
gf::Vector2<T>& operator /=(gf::Vector2<T>& left, T right);

template <typename T>
bool operator ==(const gf::Vector2<T>& left, const gf::Vector2<T>& right);

template <typename T>
bool operator !=(const gf::Vector2<T>& left, const gf::Vector2<T>& right);

#include <Grafit/Graphics/Geometry/Vector2.inl>

#endif // VECTOR2_HPP

