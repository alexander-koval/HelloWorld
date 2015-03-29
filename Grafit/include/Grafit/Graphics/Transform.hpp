#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>

namespace gf {

class Transform {
public:
    static const Transform Identity;

    Transform(void);

    Transform(float m00, float m01, float m02,
              float m10, float m11, float m12,
              float m20, float m21, float m22);

    Transform(Mat4<float> matrix);

    const float* getMatrix() const;

    Transform getInverse(void) const;

    Vector2F transformPoint(float x, float y) const;

    Vector2F transformPoint(const Vector2F& point) const;

    Transform& combine(const Transform& transform);

    Transform& translate(float x, float y);

    Transform& translate(const Vector2F& offset);

    Transform& rotate(float angle);

    Transform& rotate(float angle, float centerX, float centerY);

    Transform& scale(float scaleX, float scaleY);

    Transform& scale(float scaleX, float scaleY, float centerX, float centerY);

    Transform& scale(const Vector2F& factors);

    Transform& scale(const Vector2F& factors, const Vector2F& center);

private:
    Mat4<float> m_matrix;
};

}
#endif // TRANSFORM_HPP

