#include <icebird/Graphics/Transform.hpp>

const Transform Transform::Identity;


Transform::Transform(void)
    : m_matrix() {

}

Transform::Transform(float m00, float m01, float m02,
                     float m10, float m11, float m12,
                     float m20, float m21, float m22)
    : m_matrix(m00, m01, 0, m02,
               m10, m11, 0, m12,
                 0,   0, 1,   0,
               m20, m21, 0, m21) {
}

const float* Transform::getMatrix(void) const {
    return m_matrix.getMatrix();
}

Transform Transform::getInverse(void) const {
//    Mat4<float> matrix = m_matrix.getInverse();
    Transform transform = Transform();
    return transform;
}

Vector2F Transform::transformPoint(float x, float y) const {
    const float* matrix = m_matrix.getMatrix();
    return Vector2F(matrix[0] * x + matrix[4] * y + matrix[12],
                    matrix[1] * x + matrix[5] * y + matrix[13]);
}

Vector2F Transform::transformPoint(const Vector2F &point) const {
    return transformPoint(point.x, point.y);
}

Transform& Transform::combine(const Transform &transform) {
    m_matrix.multiply(transform.m_matrix);
}

Transform& Transform::translate(float x, float y) {
    m_matrix.translate(x, y, 0);
    return *this;
}

Transform& Transform::translate(const Vector2F &offset) {
    return translate(offset.x, offset.y);
}

Transform& Transform::rotate(float angle) {
    m_matrix.rotate(angle);
    return *this;
}

Transform& Transform::rotate(float angle, float centerX, float centerY) {
    m_matrix.rotate(angle, centerX, centerY);
    return *this;
}

Transform& Transform::scale(float scaleX, float scaleY) {
    m_matrix.scale(scaleX, scaleY, 0);
    return *this;
}

Transform& Transform::scale(float scaleX, float scaleY, float centerX, float centerY) {
    m_matrix.scale(scaleX, scaleY, 0, centerX, centerY, 0);
    return *this;
}

Transform& Transform::scale(const Vector2F &factors) {
    return scale(factors.x, factors.y);
}

Transform& Transform::scale(const Vector2F &factors, const Vector2F &center) {
    return scale(factors.x, factors.y, center.x, center.y);
}
