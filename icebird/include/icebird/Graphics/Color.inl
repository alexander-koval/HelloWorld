#include <icebird/Graphics/Color.hpp>
#include <algorithm>

template <typename T>
Color<T>::Color(T red, T green, T blue, T alpha)
    : r(red)
    , g(green)
    , b(blue)
    , a(alpha) {

}

template <typename T>
bool operator ==(const Color<T>& left, const Color<T>& right) {
    return  (left.r == right.r) &&
            (left.g == right.g) &&
            (left.b == right.b) &&
            (left.a == right.a);
}

template <typename T>
bool operator !=(const Color<T>& left, const Color<T>& right) {
    return !(left == right);
}

template <typename T>
Color<T>& operator +=(Color<T>& left, const Color<T>& right) {
    return left = left + right;
}

template <typename T>
Color<T>& operator -=(Color<T>& left, const Color<T>& right) {
    return left = left - right;
}

template <typename T>
Color<T>& operator *=(Color<T>& left, const Color<T>& right) {
    return left = left * right;
}
