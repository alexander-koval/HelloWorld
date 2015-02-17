#ifndef MAT4_HPP
#define MAT4_HPP

#include <icebird/System/Math/Vector2.hpp>
#include <cmath>

template <typename T>
class Mat4 {
public:
    static const Mat4<T> IDENTITY;
    Mat4();

    Mat4(T m00, T m01, T m02, T m03,
         T m10, T m11, T m12, T m13,
         T m20, T m21, T m22, T m23,
         T m30, T m31, T m32, T m33);

    Mat4(const T* mat);

    Mat4(const Mat4<T>& copy);

    ~Mat4(void);

    Mat4& multiply(const Mat4<T>& matrix);

    Mat4& inverse(void);

    Mat4& negate(void);

    Mat4& translate(T x, T y);

    Mat4& translate(const Vector2<T>& offset);

    Mat4& rotate(T angle);

    Mat4& rotate(T angle, T centerX, T centerY);

    Mat4& rotate(T angle, const Vector2<T>& center);

    Mat4& scale(T scaleX, T scaleY);

    Mat4& scale(T scaleX, T scaleY, T centerX, T centerY);

    Mat4& scale(const Vector2<T>& factors);

    Mat4& scale(const Vector2<T>& factors, const Vector2<T>& center);

    T determinant(void) const;

    Mat4 getInverse(void) const;

    Mat4 getNegate(void) const;

    bool isIdentity(void) const;

    const T* getMatrix(void) const;

private:
    T m_matrix[16];
};

template <typename T>
Mat4<T> operator *(const Mat4<T>& left, const Mat4<T>& right);

template <typename T>
Vector2<T> operator*(const Mat4<T>& left, const Vector2<T>& right);

template <typename T>
Mat4<T>& operator *=(Mat4<T>& left, const Mat4<T>& right);

template <typename T>
inline Mat4<T>::Mat4(void) {
    m_matrix[0] = (T) 1;    m_matrix[1] = 0;        m_matrix[2] = 0;    m_matrix[3] = 0;
    m_matrix[4] = 0;        m_matrix[5] = (T) 1;    m_matrix[6] = 0;    m_matrix[7] = 0;
    m_matrix[8] = 0;        m_matrix[9] = 0;        m_matrix[10] = (T) 1; m_matrix[11] = 0;
    m_matrix[12] = 0;       m_matrix[13] = 0;       m_matrix[14] = 0;   m_matrix[15] = (T) 1;
}

template <typename T>
inline Mat4<T>::Mat4(T m00, T m01, T m02, T m03,
                     T m10, T m11, T m12, T m13,
                     T m20, T m21, T m22, T m23,
                     T m30, T m31, T m32, T m33) {
    m_matrix[0] = m00;    m_matrix[1] = m01;    m_matrix[2] = m02;    m_matrix[3] = m03;
    m_matrix[4] = m10;    m_matrix[5] = m11;    m_matrix[6] = m12;    m_matrix[7] = m13;
    m_matrix[8] = m20;    m_matrix[9] = m21;    m_matrix[10] = m22;   m_matrix[11] = m23;
    m_matrix[12] = m30;   m_matrix[13] = m31;   m_matrix[14] = m32;   m_matrix[15] = m33;
}

template <typename T>
inline Mat4<T>::Mat4(const T *mat) {
    memcpy(m_matrix, mat, sizeof(m_matrix));
}

template <typename T>
inline Mat4<T>::Mat4(const Mat4<T> &copy) {
    memcpy(m_matrix, copy.m_matrix, sizeof(m_matrix));
}

template <typename T>
inline Mat4<T>::~Mat4(void) {

}

template <typename T>
inline Mat4<T>& Mat4<T>::multiply(const Mat4<T> &matrix) {
    const T* a = m_matrix;
    const T* b = matrix.m_matrix;

    *this = Mat4<T>(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                    a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                    a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                    a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                    a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                    a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                    a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                    a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                    a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::inverse(void) {
    T det = determinant();
    if (det != (T)0) {
        *this = Mat4<T>( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
                        -(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
                         (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
                        -(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
                         (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
                        -(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
                         (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
                        -(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
                         (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
    }
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::negate(void) {

}

template <typename T>
inline Mat4<T>& Mat4<T>::translate(T x, T y) {
    Mat4<T> translation(1, 0, x, 0,
                        0, 1, y, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
    return multiply(translation);
}

template <typename T>
inline Mat4<T>& Mat4<T>::translate(const Vector2<T> &offset) {
    return translate(offset.x, offset.y);
}

template <typename T>
inline Mat4<T>& Mat4<T>::rotate(T angle) {
    float radian = angle * 3.14592654f / 180.f;
    float cos = std::cos(radian);
    float sin = std::sin(radian);

    Mat4<T> rotation(cos, -sin, 0, 0,
                     sin,  cos, 0, 0,
                     0  ,    0, 1, 0,
                     0  ,    0, 0, 1);
    return multiply(rotation);
}

template <typename T>
inline Mat4<T>& Mat4<T>::rotate(T angle, T centerX, T centerY) {
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Mat4<T> rotation(cos, -sin, centerX * (1 - cos) + centerY * sin, 0,
                       sin,  cos, centerY * (1 - cos) - centerX * sin, 0,
                       0,    0,     1,      0,
                       0,    0,     0,      1);
    return multiply(rotation);
}

template <typename T>
inline Mat4<T>& Mat4<T>::rotate(T angle, const Vector2<T> &center) {
    return rotate(angle, center.x, center.y);
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(T scaleX, T scaleY) {
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(T scaleX, T scaleY, T centerX, T centerY) {
    return * this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(const Vector2<T> &factors) {
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(const Vector2<T> &factors, const Vector2<T> &center) {
    return *this;
}

template <typename T>
inline T Mat4<T>::determinant() const {
    T det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
            m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
            m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);
    return det;
}

template <typename T>
inline Mat4<T> Mat4<T>::getInverse(void) const {
    T det = determinant();
    if (det != (T)0) {
        return Mat4<T>( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
                       -(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
                        (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
                       -(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
                        (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
                       -(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
                        (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
                       -(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
                        (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
    } else {
        return Mat4<T>();
    }
}


#endif // MAT4_HPP
