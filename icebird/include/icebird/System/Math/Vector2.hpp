#ifndef VECTOR2_HPP
#define VECTOR2_HPP

template <typename T>
class Vector2 {
public:
    Vector2(void);

    Vector2(T x, T y);

    template <typename U>
    explicit Vector2(const Vector2<U>& vector);

    T x;
    T y;
};

template <typename T>
Vector2<T> operator -(const Vector2<T>& right);

template <typename T>
Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator +(const vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator *(const Vector2<T>& left, T right);

template <typename T>
Vector2<T> operator *(T left, const Vector2<T>& right);

template <typename T>
Vector2<T>& operator *=(Vector2<T>& left, T right);

template <typename T>
Vector2<T> operator /(const Vector2<T>& left, T right);

template <typename T>
Vector2<T>& operator /=(Vector2<T>& left, T right);

template <typename T>
bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

//#include <icebird/System/Math/Vector2.inl>

template <typename T>
inline Vector2<T>::Vector2()
    : x(0)
    , y(0) {

}

template <typename T>
inline Vector2<T>::Vector2(T x, T y)
    : x(x)
    , y(y) {

}

template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U>& vector)
    : x(static_cast<T>(vector.x))
    , y(static_cast<T>(vector.y)) {

}

template <typename T>
inline Vector2<T> operator -(const Vector2<T>& right) {
    return Vector2<T>(-right.x, -right.y);
}

template <typename T>
inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T>
inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right) {
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

template <typename T>
inline Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x + right.y, left.y + right.y);
}

template <typename T>
inline Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x - right.y, left.y - right.y);
}

template <typename T>
inline Vector2<T> operator *(const Vector2<T>& left, T right) {
    return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
inline Vector2<T> operator *(T left, const Vector2<T>& right) {
    return Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
inline Vector2<T>& operator *=(Vector2<T>& left, T right) {
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T>
inline Vector2<T> operator /(const Vector2<T>& left, T right) {
    return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
inline Vector2<T>& operator /=(Vector2<T>& left, T right) {
    left.x /= right;
    left.y /= right;
    return left;
}

template <typename T>
inline bool operator ==(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator !=(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x != right.x) && (left.y != right.y);
}

typedef Vector2<int>            Vector2i;
typedef Vector2<unsigned int>   Vector2u;
typedef Vector2<float>          Vector2f;

#endif // VECTOR2_HPP

