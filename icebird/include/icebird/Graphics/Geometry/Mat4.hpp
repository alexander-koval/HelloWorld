#ifndef MAT4_HPP
#define MAT4_HPP

#include <icebird/Graphics/Geometry/Vector3.hpp>
#include <cmath>
#include <cstring>

template <typename T>
class Mat4 {
public:
    static const Mat4<T> IDENTITY;

    Mat4(void);

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

    Mat4& translate(T x, T y, T z);

    Mat4& translate(const Vector3<T>& offset);

    Mat4& rotate(T angle);

    Mat4& rotate(T angle, T centerX, T centerY);

    Mat4& rotate(T angle, const Vector3<T>& center);

    Mat4& scale(T scaleX, T scaleY, T scaleZ);

    Mat4& scale(T scaleX, T scaleY, T scaleZ, T centerX, T centerY, T centerZ);

    Mat4& scale(const Vector3<T>& factors);

    Mat4& scale(const Vector3<T>& factors, const Vector3<T>& center);

    T determinant(void) const;

    Mat4 getInverse(void) const;

    Mat4 getNegate(void) const;

    bool isIdentity(void) const;

    const T* getMatrix(void) const;

    T& operator [](int index) const;

    T& operator [](int index);

private:
    T m_matrix[16];
};

template <typename T>
Mat4<T> operator *(const Mat4<T>& left, const Mat4<T>& right);

template <typename T>
Vector3<T> operator *(const Mat4<T>& left, const Vector3<T>& right);

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
    m_matrix[0]  = m00;  m_matrix[1]  = m10;  m_matrix[2]  = m20;  m_matrix[3]  = m30;
    m_matrix[4]  = m01;  m_matrix[5]  = m11;  m_matrix[6]  = m21;  m_matrix[7]  = m31;
    m_matrix[8]  = m02;  m_matrix[9]  = m12;  m_matrix[10] = m22;  m_matrix[11] = m32;
    m_matrix[12] = m03;  m_matrix[13] = m13;  m_matrix[14] = m23;  m_matrix[15] = m33;
}

template <typename T>
inline Mat4<T>::Mat4(const T *mat) {
    memcpy(m_matrix, mat, sizeof(m_matrix));
}

template <typename T>
inline Mat4<T>::Mat4(const Mat4<T> &copy) {
    std::memcpy(m_matrix, copy.m_matrix, sizeof(m_matrix));
}

template <typename T>
inline Mat4<T>::~Mat4(void) {

}

template <typename T>
inline Mat4<T>& Mat4<T>::multiply(const Mat4<T> &matrix) {
    const T* a = m_matrix;
    const T* b = matrix.m_matrix;

    T m111 = m_matrix[0]; T m121 = m_matrix[4]; T m131 = m_matrix[8]; T m141 = m_matrix[12];
    T m112 = m_matrix[1]; T m122 = m_matrix[5]; T m132 = m_matrix[9]; T m142 = m_matrix[13];
    T m113 = m_matrix[2]; T m123 = m_matrix[6]; T m133 = m_matrix[10]; T m143 = m_matrix[14];
    T m114 = m_matrix[3]; T m124 = m_matrix[7]; T m134 = m_matrix[11]; T m144 = m_matrix[15];
    T m211 = matrix.m_matrix[0]; T m221 = matrix.m_matrix[4]; T m231 = matrix.m_matrix[8]; T m241 = matrix.m_matrix[12];
    T m212 = matrix.m_matrix[1]; T m222 = matrix.m_matrix[5]; T m232 = matrix.m_matrix[9]; T m242 = matrix.m_matrix[13];
    T m213 = matrix.m_matrix[2]; T m223 = matrix.m_matrix[6]; T m233 = matrix.m_matrix[10]; T m243 = matrix.m_matrix[14];
    T m214 = matrix.m_matrix[3]; T m224 = matrix.m_matrix[7]; T m234 = matrix.m_matrix[11]; T m244 = matrix.m_matrix[15];

    m_matrix[0] = m111 * m211 + m112 * m221 + m113 * m231 + m114 * m241;
    m_matrix[1] = m111 * m212 + m112 * m222 + m113 * m232 + m114 * m242;
    m_matrix[2] = m111 * m213 + m112 * m223 + m113 * m233 + m114 * m243;
    m_matrix[3] = m111 * m214 + m112 * m224 + m113 * m234 + m114 * m244;

    m_matrix[4] = m121 * m211 + m122 * m221 + m123 * m231 + m124 * m241;
    m_matrix[5] = m121 * m212 + m122 * m222 + m123 * m232 + m124 * m242;
    m_matrix[6] = m121 * m213 + m122 * m223 + m123 * m233 + m124 * m243;
    m_matrix[7] = m121 * m214 + m122 * m224 + m123 * m234 + m124 * m244;

    m_matrix[8] = m131 * m211 + m132 * m221 + m133 * m231 + m134 * m241;
    m_matrix[9] = m131 * m212 + m132 * m222 + m133 * m232 + m134 * m242;
    m_matrix[10] = m131 * m213 + m132 * m223 + m133 * m233 + m134 * m243;
    m_matrix[11] = m131 * m214 + m132 * m224 + m133 * m234 + m134 * m244;

    m_matrix[12] = m141 * m211 + m142 * m221 + m143 * m231 + m144 * m241;
    m_matrix[13] = m141 * m212 + m142 * m222 + m143 * m232 + m144 * m242;
    m_matrix[14] = m141 * m213 + m142 * m223 + m143 * m233 + m144 * m243;
    m_matrix[15] = m141 * m214 + m142 * m224 + m143 * m234 + m144 * m244;

    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::inverse(void) {
    T det = determinant();
    bool invertable = std::abs(det) > 0.00000000001;
    if (invertable) {
        det = 1 / det;

        T m11 = m_matrix[0]; T m21 = m_matrix[4]; T m31 = m_matrix[8]; T m41 = m_matrix[12];
        T m12 = m_matrix[1]; T m22 = m_matrix[5]; T m32 = m_matrix[9]; T m42 = m_matrix[13];
        T m13 = m_matrix[2]; T m23 = m_matrix[6]; T m33 = m_matrix[10]; T m43 = m_matrix[14];
        T m14 = m_matrix[3]; T m24 = m_matrix[7]; T m34 = m_matrix[11]; T m44 = m_matrix[15];

        m_matrix[0] = det * (m22 * (m33 * m44 - m43 * m34) - m32 * (m23 * m44 - m43 * m24) + m42 * (m23 * m34 - m33 * m24));
        m_matrix[1] = -det * (m12 * (m33 * m44 - m43 * m34) - m32 * (m13 * m44 - m43 * m14) + m42 * (m13 * m34 - m33 * m14));
        m_matrix[2] = det * (m12 * (m23 * m44 - m43 * m24) - m22 * (m13 * m44 - m43 * m14) + m42 * (m13 * m24 - m23 * m14));
        m_matrix[3] = -det * (m12 * (m23 * m34 - m33 * m24) - m22 * (m13 * m34 - m33 * m14) + m32 * (m13 * m24 - m23 * m14));
        m_matrix[4] = -det * (m21 * (m33 * m44 - m43 * m34) - m31 * (m23 * m44 - m43 * m24) + m41 * (m23 * m34 - m33 * m24));
        m_matrix[5] = det * (m11 * (m33 * m44 - m43 * m34) - m31 * (m13 * m44 - m43 * m14) + m41 * (m13 * m34 - m33 * m14));
        m_matrix[6] = -det * (m11 * (m23 * m44 - m43 * m24) - m21 * (m13 * m44 - m43 * m14) + m41 * (m13 * m24 - m23 * m14));
        m_matrix[7] = det * (m11 * (m23 * m34 - m33 * m24) - m21 * (m13 * m34 - m33 * m14) + m31 * (m13 * m24 - m23 * m14));
        m_matrix[8] = det * (m21 * (m32 * m44 - m42 * m34) - m31 * (m22 * m44 - m42 * m24) + m41 * (m22 * m34 - m32 * m24));
        m_matrix[9] = -det * (m11 * (m32 * m44 - m42 * m34) - m31 * (m12 * m44 - m42 * m14) + m41 * (m12 * m34 - m32 * m14));
        m_matrix[10] = det * (m11 * (m22 * m44 - m42 * m24) - m21 * (m12 * m44 - m42 * m14) + m41 * (m12 * m24 - m22 * m14));
        m_matrix[11] = -det * (m11 * (m22 * m34 - m32 * m24) - m21 * (m12 * m34 - m32 * m14) + m31 * (m12 * m24 - m22 * m14));
        m_matrix[12] = -det * (m21 * (m32 * m43 - m42 * m33) - m31 * (m22 * m43 - m42 * m23) + m41 * (m22 * m33 - m32 * m23));
        m_matrix[13] = det * (m11 * (m32 * m43 - m42 * m33) - m31 * (m12 * m43 - m42 * m13) + m41 * (m12 * m33 - m32 * m13));
        m_matrix[14] = -det * (m11 * (m22 * m43 - m42 * m23) - m21 * (m12 * m43 - m42 * m13) + m41 * (m12 * m23 - m22 * m13));
        m_matrix[15] = det * (m11 * (m22 * m33 - m32 * m23) - m21 * (m12 * m33 - m32 * m13) + m31 * (m12 * m23 - m22 * m13));
    }
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::negate(void) {

}

template <typename T>
inline Mat4<T>& Mat4<T>::translate(T x, T y, T z) {
    m_matrix[12] += x;
    m_matrix[13] += y;
    m_matrix[14] += z;
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::translate(const Vector3<T> &offset) {
    return translate(offset.x, offset.y, offset.z);
}

template <typename T>
inline Mat4<T>& Mat4<T>::rotate(T angle) {
    float radian = angle * M_PI / 180.f;
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
    float rad = angle * M_PI / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Mat4<T> rotation(cos, -sin, centerX * (1 - cos) + centerY * sin, 0,
                     sin,  cos, centerY * (1 - cos) - centerX * sin, 0,
                     0,    0,     1,      0,
                     0,    0,     0,      1);
    return multiply(rotation);
}

template <typename T>
inline Mat4<T>& Mat4<T>::rotate(T angle, const Vector3<T> &center) {
    return rotate(angle, center.x, center.y);
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(T scaleX, T scaleY, T scaleZ) {
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(T scaleX, T scaleY, T scaleZ, T centerX, T centerY, T centerZ) {
    return * this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(const Vector3<T> &factors) {
    return *this;
}

template <typename T>
inline Mat4<T>& Mat4<T>::scale(const Vector3<T> &factors, const Vector3<T> &center) {
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
    Mat4<T> matrix = Mat4<T>();
    T det = determinant();
    bool invertable = std::abs(det) > 0.00000000001;
    if (invertable) {
        det = 1 / det;
        T m11 = m_matrix[0]; T m21 = m_matrix[4]; T m31 = m_matrix[8]; T m41 = m_matrix[12];
        T m12 = m_matrix[1]; T m22 = m_matrix[5]; T m32 = m_matrix[9]; T m42 = m_matrix[13];
        T m13 = m_matrix[2]; T m23 = m_matrix[6]; T m33 = m_matrix[10]; T m43 = m_matrix[14];
        T m14 = m_matrix[3]; T m24 = m_matrix[7]; T m34 = m_matrix[11]; T m44 = m_matrix[15];
        matrix[0] = det * (m22 * (m33 * m44 - m43 * m34) - m32 * (m23 * m44 - m43 * m24) + m42 * (m23 * m34 - m33 * m24));
        matrix[1] = -det * (m12 * (m33 * m44 - m43 * m34) - m32 * (m13 * m44 - m43 * m14) + m42 * (m13 * m34 - m33 * m14));
        matrix[2] = det * (m12 * (m23 * m44 - m43 * m24) - m22 * (m13 * m44 - m43 * m14) + m42 * (m13 * m24 - m23 * m14));
        matrix[3] = -det * (m12 * (m23 * m34 - m33 * m24) - m22 * (m13 * m34 - m33 * m14) + m32 * (m13 * m24 - m23 * m14));
        matrix[4] = -det * (m21 * (m33 * m44 - m43 * m34) - m31 * (m23 * m44 - m43 * m24) + m41 * (m23 * m34 - m33 * m24));
        matrix[5] = det * (m11 * (m33 * m44 - m43 * m34) - m31 * (m13 * m44 - m43 * m14) + m41 * (m13 * m34 - m33 * m14));
        matrix[6] = -det * (m11 * (m23 * m44 - m43 * m24) - m21 * (m13 * m44 - m43 * m14) + m41 * (m13 * m24 - m23 * m14));
        matrix[7] = det * (m11 * (m23 * m34 - m33 * m24) - m21 * (m13 * m34 - m33 * m14) + m31 * (m13 * m24 - m23 * m14));
        matrix[8] = det * (m21 * (m32 * m44 - m42 * m34) - m31 * (m22 * m44 - m42 * m24) + m41 * (m22 * m34 - m32 * m24));
        matrix[9] = -det * (m11 * (m32 * m44 - m42 * m34) - m31 * (m12 * m44 - m42 * m14) + m41 * (m12 * m34 - m32 * m14));
        matrix[10] = det * (m11 * (m22 * m44 - m42 * m24) - m21 * (m12 * m44 - m42 * m14) + m41 * (m12 * m24 - m22 * m14));
        matrix[11] = -det * (m11 * (m22 * m34 - m32 * m24) - m21 * (m12 * m34 - m32 * m14) + m31 * (m12 * m24 - m22 * m14));
        matrix[12] = -det * (m21 * (m32 * m43 - m42 * m33) - m31 * (m22 * m43 - m42 * m23) + m41 * (m22 * m33 - m32 * m23));
        matrix[13] = det * (m11 * (m32 * m43 - m42 * m33) - m31 * (m12 * m43 - m42 * m13) + m41 * (m12 * m33 - m32 * m13));
        matrix[14] = -det * (m11 * (m22 * m43 - m42 * m23) - m21 * (m12 * m43 - m42 * m13) + m41 * (m12 * m23 - m22 * m13));
        matrix[15] = det * (m11 * (m22 * m33 - m32 * m23) - m21 * (m12 * m33 - m32 * m13) + m31 * (m12 * m23 - m22 * m13));
    }
    return matrix;
}

template <typename T>
const T* Mat4<T>::getMatrix(void) const {
    return &m_matrix[0];
}

template <typename T>
T& Mat4<T>::operator [](int index) const {
    return m_matrix[index];
}

template <typename T>
T& Mat4<T>::operator [](int index) {
    return m_matrix[index];
}

template <typename T>
Mat4<T> operator *(const Mat4<T>& left, const Mat4<T>& right) {
    return Mat4<T>(left).multiply(right);
}

template <typename T>
Vector3<T> operator*(const Mat4<T>& left, const Vector3<T>& right) {

}

template <typename T>
Mat4<T>& operator *=(Mat4<T>& left, const Mat4<T>& right) {
    return left.multiply(right);
}

typedef Mat4<float> Mat4f;

#endif // MAT4_HPP
