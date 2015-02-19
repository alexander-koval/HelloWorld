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



#endif // MAT3_HPP

