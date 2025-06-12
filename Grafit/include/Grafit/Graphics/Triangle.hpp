#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Grafit/Graphics/Transformable.hpp>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Vertex.hpp>
#include <Grafit/Graphics/VertexArray.hpp>

namespace gf {

class Triangle : public Transformable
{
public:
    Triangle();

    void render(Mat4F mvpView);

    ~Triangle();

private:
    Shader m_shader;
    VertexArray m_vertexArray;
    Vertex2<Vector2F, ColorF> m_vertices[3];
    GLushort m_indices[3];

    typedef Vertex2<Vector2F, ColorF> Vertex;
};

}
#endif // TRIANGLE_H
