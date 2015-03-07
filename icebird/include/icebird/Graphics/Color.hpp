#ifndef COLOR
#define COLOR

#include <icebird/System/Types.hpp>

template <typename T>
class  Color {
public:
    static const Color<T> Black;
    static const Color<T> White;
    static const Color<T> Red;
    static const Color<T> Green;
    static const Color<T> Blue;
    static const Color<T> Yellow;
    static const Color<T> Magenta;
    static const Color<T> Cyan;
    static const Color<T> Transparent;

    Color(void);

    Color(T red, T green, T blue, T alpha);

    template <typename U>
    explicit Color(const Color<U>& color);

    T r;
    T g;
    T b;
    T a;
};

template <typename T>
bool operator ==(const Color<T>& left, const Color<T>& right);

template <typename T>
bool operator !=(const Color<T>& left, const Color<T>& right);

template <typename T>
Color<T> operator +(const Color<T>& left, const Color<T>& right);

template <typename T>
Color<T> operator -(const Color<T>& left, const Color<T>& right);

template <typename T>
Color<T> operator *(const Color<T>& left, const Color<T>& right);

template <typename T>
Color<T>& operator +=(Color<T>& left, const Color<T>& right);

template <typename T>
Color<T>& operator -=(Color<T>& left, const Color<T>& right);

template <typename T>
Color<T>& operator *=(Color<T>& left, const Color<T>& right);

#include <icebird/Graphics/Color.inl>

typedef Color<Uint8> ColorU;
typedef Color<float> ColorF;

#endif // COLOR

