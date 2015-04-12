#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace gf {
template <typename T>
class Vector3 {
public:
    Vector3(void);

    Vector3(T x, T y, T z);

    template <typename U>
    explicit Vector3(const Vector3<U>& vector);

    T x;
    T y;
    T z;
};
}
using gf::Vector3;
template <typename T>
Vector3<T> operator -(const Vector3<T>& left);

template <typename T>
Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T> operator *(const Vector3<T>& left, T right);

template <typename T>
Vector3<T> operator *(T left, const Vector3<T>& right);

template <typename T>
Vector3<T>& operator *=(Vector3<T>& left, T right);

template <typename T>
Vector3<T> operator /(const Vector3<T>& left, T right);

template <typename T>
Vector3<T>& operator /=(Vector3<T>& left, T right);

template <typename T>
bool operator ==(const Vector3<T>& left, const Vector3<T>& right);

template <typename T>
bool operator !=(const Vector3<T>& left, const Vector3<T>& right);


typedef Vector3<int>   Vector3I;
typedef Vector3<float> Vector3F;

#include <Grafit/Graphics/Geometry/Vector3.inl>

#endif // VECTOR3_HPP

