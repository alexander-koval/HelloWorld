#ifndef RECT_HPP
#define RECT_HPP

#include <Grafit/Graphics/Geometry/Vector2.hpp>
#include <algorithm>


namespace gf {

template <typename T>
class Rect {
public:

    Rect();

    Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);

    Rect(const Vector2<T>& position, const Vector2<T>& size);

    template <typename U>
    explicit Rect(const Rect<U>& rectangle);

    bool contains(T x, T y) const;

    bool contains(const Vector2<T>& point) const;

    bool intersects(const Rect<T>& rectangle) const;

    bool intersects(const Rect<T>& rectangle, Rect<T>& intersection) const;

    T left;   ///< Left coordinate of the rectangle
    T top;    ///< Top coordinate of the rectangle
    T width;  ///< Width of the rectangle
    T height; ///< Height of the rectangle
};

template <typename T>
bool operator ==(const Rect<T>& left, const Rect<T>& right);

template <typename T>
bool operator !=(const Rect<T>& left, const Rect<T>& right);

#include <Grafit/Graphics/Geometry/Rect.inl>

typedef Rect<int>   RectI;
typedef Rect<float> RectF;

} // namespace sf


#endif // RECT_HPP
