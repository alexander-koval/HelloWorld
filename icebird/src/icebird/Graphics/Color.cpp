#include <icebird/Graphics/Color.hpp>
#include <algorithm>

template <>
const Color<Uint8> Color<Uint8>::Black((Uint8)0, (Uint8)0, (Uint8)0, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::White((Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::Red((Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::Green((Uint8)0, (Uint8)255, (Uint8)0, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::Blue((Uint8)0, (Uint8)0, (Uint8)255, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::Yellow((Uint8)255, (Uint8)255, (Uint8)0, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::Magenta((Uint8)255, (Uint8)0, (Uint8)255, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::Cyan((Uint8)0, (Uint8)255, (Uint8)255, (Uint8)255);
template <>
const Color<Uint8> Color<Uint8>::Transparent((Uint8)0, (Uint8)0, (Uint8)0, (Uint8)0);

template <>
const Color<float> Color<float>::Black(0.f, 0.f, 0.f, 1.f);
template <>
const Color<float> Color<float>::White(0.f, 0.f, 0.f, 1.f);
template <>
const Color<float> Color<float>::Red(1.f, 0.f, 0.f, 1.f);
template <>
const Color<float> Color<float>::Green(0.f, 1.f, 0.f, 1.f);
template <>
const Color<float> Color<float>::Blue(0.f, 0.f, 1.f, 1.f);
template <>
const Color<float> Color<float>::Yellow(1.f, 1.f, 0.f, 1.f);
template <>
const Color<float> Color<float>::Magenta(1.f, 0.f, 1.f, 1.f);
template <>
const Color<float> Color<float>::Cyan(0.f, 1.f, 1.f, 1.f);
template <>
const Color<float> Color<float>::Transparent(0.f, 0.f, 0.f, 0.f);

template <>
Color<Uint8>::Color(void)
    : r(0)
    , g(0)
    , b(0)
    , a(255) {

}

template <>
template <>
Color<Uint8>::Color(const Color<float>& color)
    : r(color.r * 255)
    , g(color.g * 255)
    , b(color.b * 255)
    , a(color.a * 255) {

}

template <>
Color<Uint8> operator +(const Color<Uint8>& left, const Color<Uint8>& right) {
    return Color<Uint8>(Uint8(std::min(int(left.r) + right.r, 255)),
                        Uint8(std::min(int(left.g) + right.g, 255)),
                        Uint8(std::min(int(left.b) + right.b, 255)),
                        Uint8(std::min(int(left.a) + right.a, 255)));
}

template <>
Color<Uint8> operator -(const Color<Uint8>& left, const Color<Uint8>& right) {
    return Color<Uint8>(Uint8(std::max(int(left.r) - right.r, 0)),
                        Uint8(std::max(int(left.g) - right.g, 0)),
                        Uint8(std::max(int(left.b) - right.b, 0)),
                        Uint8(std::max(int(left.a) - right.a, 0)));
}

template <>
Color<Uint8> operator *(const Color<Uint8>& left, const Color<Uint8>& right) {
    return Color<Uint8>(Uint8(int(left.r) * right.r / 255),
                        Uint8(int(left.g) * right.g / 255),
                        Uint8(int(left.b) * right.b / 255),
                        Uint8(int(left.a) * right.a / 255));
}

template <>
Color<float>::Color(void)
    : r(0.0f)
    , g(0.0f)
    , b(0.0f)
    , a(1.0f) {

}

template <>
template <>
Color<float>::Color(const Color<Uint8>& color)
    : r(color.r / 255.f)
    , g(color.g / 255.f)
    , b(color.b / 255.f)
    , a(color.a / 255.f) {

}

template <>
Color<float> operator +(const Color<float>& left, const Color<float>& right) {
    return Color<float>(std::min(left.r + right.r, 1.0f),
                        std::min(left.g + right.g, 1.0f),
                        std::min(left.b + right.b, 1.0f),
                        std::min(left.a + right.a, 1.0f));
}

template <>
Color<float> operator -(const Color<float>& left, const Color<float>& right) {
    return Color<float>(std::max(left.r - right.r, 0.0f),
                        std::max(left.g - right.g, 0.0f),
                        std::max(left.b - right.b, 0.0f),
                        std::max(left.a - right.a, 0.0f));
}

template <>
Color<float> operator *(const Color<float>& left, const Color<float>& right) {
    return Color<float>(left.r * right.r,
                        left.g * right.g,
                        left.b * right.b,
                        left.a * right.a);
}
