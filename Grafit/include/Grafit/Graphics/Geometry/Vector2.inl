#include <Grafit/Graphics/Geometry/Vector2.hpp>

template <typename T>
inline gf::Vector2<T>::Vector2()
    : x(0)
    , y(0) {

}

template <typename T>
inline gf::Vector2<T>::Vector2(T x, T y)
    : x(x)
    , y(y) {

}

template <typename T>
template <typename U>
inline gf::Vector2<T>::Vector2(const gf::Vector2<U>& vector)
    : x(static_cast<T>(vector.x))
    , y(static_cast<T>(vector.y)) {

}

template <typename T>
inline float gf::Vector2<T>::getLength(void) const {
    return std::sqrt(x * x + y * y);
}

template <typename T>
inline float gf::Vector2<T>::getLengthSq(void) const {
    return x * x + y * y;
}

template <typename T>
inline float gf::Vector2<T>::getDistance(const gf::Vector2<T>& other) {
    return (*this - other).getLength();
}

template <typename T>
inline float gf::Vector2<T>::getDistanceSq(const gf::Vector2<T>& other) {
    return (*this - other).getLengthSq();
}

template <typename T>
inline float gf::Vector2<T>::getAngle(void) const {
    float angle = std::atan2(y, x);
    if (angle < 0) angle += M_PI * 2;
    return angle;
}

template <typename T>
inline float gf::Vector2<T>::getAngleBetween(const gf::Vector2<T>& other) const {
    return std::acos(dot(other) / getLength() * other.getLength());
}

template <typename T>
inline float gf::Vector2<T>::getRangedAngleBetween(const gf::Vector2<T>& other) const {
    float angle = std::atan2(x, y) - std::atan2(other.y, other.x);
    while (angle >  M_PI) angle -= M_PI * 2;
    while (angle < -M_PI) angle += M_PI * 2;
    return angle;
}

template <typename T>
inline float gf::Vector2<T>::dot(const gf::Vector2<T> other) const {
    return x * other.x + y * other.y;
}

template <typename T>
inline float gf::Vector2<T>::cross(const gf::Vector2<T> other) const {
    return x * other.y - y * other.x;
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::getPerp(void) const {
    return gf::Vector2<T>(-y, x);
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::getRPerp(void) const {
    return gf::Vector2<T>(y, -x);
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::project(const gf::Vector2<T> other) const {
    return other * (dot(other) / other.dot(other));
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::rotate(float angle) const {
    return gf::Vector2<T>(x * std::cosf(angle) - y * std::sinf(angle),
                      x * std::sinf(angle) + y * std::cosf(angle));
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::rotate(float angle, Vector2<T> origin) const {
    return origin + (*this - origin).rotate(Vector2<T>(std::cosf(angle), std::sinf(angle)));
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::rotate(const gf::Vector2<T> other) const {
    return gf::Vector2<T>(x * other.x - y * other.y, x * other.y + y * other.x);
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::unrotate(const gf::Vector2<T> other) const {
    return gf::Vector2<T>(x * other.x + y * other.y, y * other.x - x * other.y);
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::normalize(void) const {
    T length = getLength();
    if (length == 0.) return gf::Vector2<T>(1, 0);
    return *this / getLength();
}

template <typename T>
inline gf::Vector2<T> gf::Vector2<T>::lerp(const gf::Vector2<T> other, float alpha) const {
    return *this * (1.f - alpha) + other * alpha;
}

template <typename T>
inline gf::Vector2<T> operator -(const gf::Vector2<T>& right) {
    return gf::Vector2<T>(-right.x, -right.y);
}

template <typename T>
inline gf::Vector2<T>& operator +=(gf::Vector2<T>& left, const gf::Vector2<T>& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T>
inline gf::Vector2<T>& operator -=(gf::Vector2<T>& left, const gf::Vector2<T>& right) {
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

template <typename T>
inline gf::Vector2<T> operator +(const gf::Vector2<T>& left, const gf::Vector2<T>& right) {
    return gf::Vector2<T>(left.x + right.y, left.y + right.y);
}

template <typename T>
inline gf::Vector2<T> operator -(const gf::Vector2<T>& left, const gf::Vector2<T>& right) {
    return gf::Vector2<T>(left.x - right.y, left.y - right.y);
}

template <typename T>
inline gf::Vector2<T> operator *(const gf::Vector2<T>& left, T right) {
    return gf::Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
inline gf::Vector2<T> operator *(T left, const gf::Vector2<T>& right) {
    return gf::Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
inline gf::Vector2<T>& operator *=(gf::Vector2<T>& left, T right) {
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T>
inline gf::Vector2<T> operator /(const gf::Vector2<T>& left, T right) {
    return gf::Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
inline gf::Vector2<T>& operator /=(gf::Vector2<T>& left, T right) {
    left.x /= right;
    left.y /= right;
    return left;
}

template <typename T>
inline bool operator ==(const gf::Vector2<T>& left, const gf::Vector2<T>& right) {
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator !=(const gf::Vector2<T>& left, const gf::Vector2<T>& right) {
    return (left.x != right.x) || (left.y != right.y);
}
