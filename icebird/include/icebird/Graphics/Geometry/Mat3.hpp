#ifndef MAT3_HPP
#define MAT3_HPP

#include <icebird/Graphics/Geometry/Vector2.hpp>
#include <cmath>
#include <cstring>

template <typename T>
class Mat3 {
public:
    static const Mat3<T> IDENTITY;

    Mat3(void);

    Mat3(T m00, T m01, T m02,
         T m10, T m11, T m12,
         T m20, T m21, T m22);

    Mat3(const T* mat);

    Mat3(const Mat3<T>& copy);

    ~Mat3(void);

    Mat3& multiply(const Mat3<T>& matrix);

    Mat3& inverse(void);

    Mat3&  negate(void);

    Mat3& translate(T x, T y);

    Mat3& translate(const Vector2<T>& offset);

    Mat3& rotate(T angle);

    Mat3& rotate(T angle, T centerX, T centerY);

    Mat3& rotate(T angle, const Vector2<T>& center);

    Mat3& scale(T scaleX, T scaleY);

    Mat3& scale(T scaleX, T scaleY, T centerX, T centerY);

    Mat3& scale(const Vector2<T>& factors);

    Mat3& scale(const Vector2<T>& factors, const Vector2<T>& center);

    T determinant(void) const;

    Mat3 getInverse(void) const;

    Mat3 getNegate(void) const;

    bool isIdentity(void) const;

    const T* getMatrix(void) const;

private:
    T m_matrix[9];
};

template <typename T>
Mat3<T> operator *(const Mat3<T>& left, const Mat3<T>& right);

template <typename T>
Vector2<T> operator *(const Mat3<T>& left, const Vector2<T>& right);

template <typename T>
Mat3<T>& operator *=(Mat3<T>& left, const Mat3<T>& right);

template <typename T>
inline Mat3<T>::Mat3(void) {
    m_matrix[0] =   (T) 1; m_matrix[1] =        0; m_matrix[2] =        0;
    m_matrix[3] =       0; m_matrix[4] =    (T) 1; m_matrix[5] =        0;
    m_matrix[6] =       0; m_matrix[7] =        0; m_matrix[8] =    (T) 1;
}

template <typename T>
inline Mat3<T>::Mat3(T m00, T m01, T m02,
              T m10, T m11, T m12,
              T m20, T m21, T m22) {
    m_matrix[0] = m00; m_matrix[1] = m10; m_matrix[2] = m20;
    m_matrix[3] = m01; m_matrix[4] = m11; m_matrix[5] = m21;
    m_matrix[6] = m02; m_matrix[7] = m12; m_matrix[8] = m22;
}

template <typename T>
inline Mat3<T>::Mat3(const T *mat) {
    memcpy(m_matrix, mat, sizeof(m_matrix));
}

template <typename T>
inline Mat3<T>::~Mat3(void) {

}

template <typename T>
inline Mat3<T>& Mat3<T>::multiply(const Mat3<T> &matrix) {
    const T* a = m_matrix;
    const T* b = matrix.m_matrix;

    T m111 = m_matrix[0]; T m121 = m_matrix[3]; T m131 = m_matrix[6];
    T m112 = m_matrix[1]; T m122 = m_matrix[4]; T m132 = m_matrix[7];
    T m113 = m_matrix[2]; T m123 = m_matrix[5]; T m133 = m_matrix[8];
    T m211 = matrix.m_matrix[0]; T m221 = matrix.m_matrix[3]; T m231 = matrix.m_matrix[6];
    T m212 = matrix.m_matrix[1]; T m222 = matrix.m_matrix[4]; T m232 = matrix.m_matrix[7];
    T m213 = matrix.m_matrix[2]; T m223 = matrix.m_matrix[5]; T m233 = matrix.m_matrix[8];

    m_matrix[0] = m111 * m211 + m112 * m221 + m113 * m231;
    m_matrix[1] = m111 * m212 + m112 * m222 + m113 * m232;
    m_matrix[2] = m111 * m213 + m112 * m223 + m113 * m233;

    m_matrix[3] = m121 * m211 + m122 * m221 + m123 * m231;
    m_matrix[4] = m121 * m212 + m122 * m222 + m123 + m232;
    m_matrix[5] = m121 * m213 + m122 * m223 + m123 * m233;

    m_matrix[6] = m131 * m211 + m132 * m221 + m133 * m231;
    m_matrix[7] = m131 * m212 + m132 * m222 + m133 * m232;
    m_matrix[8] = m131 * m213 + m132 * m223 + m133 * m233;

    return *this;
}

template <typename T>
inline Mat3<T>& Mat3<T>::inverse(void) {
    T det = determinant();
    bool invertable = std::abs(det) > 0.00000000001;
    if (invertable) {
        det = 1 / det;

        T m11 = m_matrix[0]; T m21 = m_matrix[3]; T m31 = m_matrix[6];
        T m12 = m_matrix[1]; T m22 = m_matrix[4]; T m32 = m_matrix[7];
        T m13 = m_matrix[2]; T m23 = m_matrix[5]; T m33 = m_matrix[8];

        m_matrix[0] =  det * (m22 * m33 - m32 * m23);
        m_matrix[1] = -det * (m12 * m33 - m13 * m13);
        m_matrix[2] =  det * (m12 * m22 - m13 * m23);
        m_matrix[3] = -det * (m21 * m33 - m31 * m23);
        m_matrix[4] =  det * (m11 * m33 - m13 * m31);
        m_matrix[5] = -det * (m11 * m23 - m13 * m21);
        m_matrix[6] =  det * (m21 * m32 - m22 * m31);
        m_matrix[7] = -det * (m11 * m32 - m12 * m31);
        m_matrix[8] =  det * (m11 * m22 - m12 * m21);
    }
    return *this;
}

#endif // MAT3_HPP

