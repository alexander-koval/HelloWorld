#include <Grafit/Graphics/Vertex.hpp>

using gf::Vertex2;
using gf::Vertex3;
using gf::Vertex4;

template <typename T1, typename T2>
Vertex2<T1, T2>::Vertex2(void)
    : value1()
    , value2() {

}

template <typename T1, typename T2>
Vertex2<T1, T2>::Vertex2(const T1& value1, const T2& value2)
    : value1(value1)
    , value2(value2) {

}

template <typename T1, typename T2, typename T3>
Vertex3<T1, T2, T3>::Vertex3(void)
    : value1()
    , value2()
    , value3() {

}

template <typename T1, typename T2, typename T3>
Vertex3<T1, T2, T3>::Vertex3(const T1& value1, const T2& value2, const T3& value3)
    : value1(value1)
    , value2(value2)
    , value3(value3) {

}

template <typename T1, typename T2, typename T3, typename T4>
Vertex4<T1, T2, T3, T4>::Vertex4(void)
    : value1()
    , value2()
    , value3()
    , value4() {

}

template <typename T1, typename T2, typename T3, typename T4>
Vertex4<T1, T2, T3, T4>::Vertex4(const T1& value1, const T2& value2, const T3& value3, const T3& value4)
    : value1(value1)
    , value2(value2)
    , value3(value3)
    , value4(value4) {

}
