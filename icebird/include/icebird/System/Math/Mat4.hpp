#ifndef MAT4_HPP
#define MAT4_HPP

#include <icebird/System/Math/Vector2.hpp>

class Mat4 {
public:
    Mat4();

    Mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
         float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    Mat4(const float* mat);

    Mat4(const Mat4& copy);

    ~Mat4();

    Mat4& multiply(const Mat4& matrix);

    Mat4& inverse(void);

    Mat4& negate(void);

    Mat4& translate(float x, float y);

    Mat4& translate(const Vector2f& offcet);

    Mat4& rotate(float angle);

    Mat4& rotate(float angle, float centerX, float centerY);

    Mat4& rotate(float angle, const Vector2f& center);

    Mat4& scale(float scaleX, float scaleY);

    Mat4& scale(float scaleX, float scaleY, float centerX, float centerY);

    Mat4& scale(const Vector2f& factors);

    Mat4& scale(const Vector2f& factors, const Vector2f& center);

    Mat4 getInverse(void) const;

    Mat4 getNegate(void) const;

    bool isIdentity(void) const;

private:
    float m_matrix[16];
};

Mat4 operator *(const Mat4& left, const Mat4& right);

Vector2f operator*(const Mat4& left, const Vector2f& right);

Mat4& operator *=(Mat4& left, const Mat4& right);


#endif // MAT4_HPP
