#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <Grafit/Graphics/Color.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>

namespace gf {

template <typename T1, typename T2>
class Vertex2 {
public:
    Vertex2(void);

    Vertex2(const T1& value1, const T2& value2);

    T1 value1;
    T2 value2;
};

template <typename T1, typename T2, typename T3>
class Vertex3 {
public:
    Vertex3(void);

    Vertex3(const T1& value1, const T2& value2, const T3& value3);

    T1& value1;
    T2& value2;
    T3& value3;
};

template <typename T1, typename T2, typename T3, typename T4>
class Vertex4 {
public:
    Vertex4(void);

    Vertex4(const T1& value1, const T2& value2, const T3& value3, const T3& value4);

    T1& value1;
    T2& value2;
    T3& value3;
    T4& value4;
};

#include <Grafit/Graphics/Vertex.inl>

}
#endif // VERTEX_HPP

