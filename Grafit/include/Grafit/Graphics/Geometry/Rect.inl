#include <Grafit/Graphics/Geometry/Rect.hpp>

template <typename T>
Rect<T>::Rect() :
left  (0),
top   (0),
width (0),
height(0) {

}

template <typename T>
Rect<T>::Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) :
left  (rectLeft),
top   (rectTop),
width (rectWidth),
height(rectHeight) {

}

template <typename T>
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) :
left  (position.x),
top   (position.y),
width (size.x),
height(size.y) {

}

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& rectangle) :
left  (static_cast<T>(rectangle.left)),
top   (static_cast<T>(rectangle.top)),
width (static_cast<T>(rectangle.width)),
height(static_cast<T>(rectangle.height))
{
}

template <typename T>
bool Rect<T>::contains(T x, T y) const {
    T minX = std::min(left, static_cast<T>(left + width));
    T maxX = std::max(left, static_cast<T>(left + width));
    T minY = std::min(top, static_cast<T>(top + height));
    T maxY = std::max(top, static_cast<T>(top + height));

    return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
}

template <typename T>
bool Rect<T>::contains(const Vector2<T>& point) const {
    return contains(point.x, point.y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rectangle) const {
    Rect<T> intersection;
    return intersects(rectangle, intersection);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rectangle, Rect<T>& intersection) const {
    T r1MinX = std::min(left, static_cast<T>(left + width));
    T r1MaxX = std::max(left, static_cast<T>(left + width));
    T r1MinY = std::min(top, static_cast<T>(top + height));
    T r1MaxY = std::max(top, static_cast<T>(top + height));

    // Compute the min and max of the second rectangle on both axes
    T r2MinX = std::min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    T r2MaxX = std::max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    T r2MinY = std::min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
    T r2MaxY = std::max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

    // Compute the intersection boundaries
    T interLeft   = std::max(r1MinX, r2MinX);
    T interTop    = std::max(r1MinY, r2MinY);
    T interRight  = std::min(r1MaxX, r2MaxX);
    T interBottom = std::min(r1MaxY, r2MaxY);

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom)) {
        intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
        return true;
    } else {
        intersection = Rect<T>(0, 0, 0, 0);
        return false;
    }
}

template <typename T>
inline bool operator ==(const Rect<T>& left, const Rect<T>& right) {
    return (left.left == right.left) && (left.width == right.width) &&
           (left.top == right.top) && (left.height == right.height);
}

template <typename T>
inline bool operator !=(const Rect<T>& left, const Rect<T>& right) {
    return !(left == right);
}
