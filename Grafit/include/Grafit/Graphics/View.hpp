#ifndef VIEW_HPP
#define VIEW_HPP

#include <Grafit/Graphics/Geometry/Rect.hpp>
#include <Grafit/Graphics/Transform.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>


namespace gf {

class View {
public:

    View();

    explicit View(const FloatRect& rectangle);

    View(const Vector2F& center, const Vector2F& size);

    void setCenter(float x, float y);

    void setCenter(const Vector2F& center);

    void setSize(float width, float height);

    void setSize(const Vector2F& size);

    void setRotation(float angle);

    void setViewport(const FloatRect& viewport);

    void reset(const FloatRect& rectangle);

    const Vector2F& getCenter() const;

    const Vector2F& getSize() const;

    float getRotation() const;

    const FloatRect& getViewport() const;

    void move(float offsetX, float offsetY);

    void move(const Vector2F& offset);

    void rotate(float angle);

    void zoom(float factor);

    const Transform& getTransform() const;

    const Transform& getInverseTransform() const;

private:

    Vector2F          m_center;              ///< Center of the view, in scene coordinates
    Vector2F          m_size;                ///< Size of the view, in scene coordinates
    float             m_rotation;            ///< Angle of rotation of the view rectangle, in degrees
    FloatRect         m_viewport;            ///< Viewport rectangle, expressed as a factor of the render-target's size
    mutable Transform m_transform;           ///< Precomputed projection transform corresponding to the view
    mutable Transform m_inverseTransform;    ///< Precomputed inverse projection transform corresponding to the view
    mutable bool      m_transformUpdated;    ///< Internal state telling if the transform needs to be updated
    mutable bool      m_invTransformUpdated; ///< Internal state telling if the inverse transform needs to be updated
};

} // namespace sf


#endif // VIEW_HPP
