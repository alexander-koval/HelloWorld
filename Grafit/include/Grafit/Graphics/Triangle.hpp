#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
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

    void render(Mat4f mvpView);

    ~Triangle();

private:
//    GLuint m_vaoID;
//    GLuint m_vboID[2];
    GLushort m_indices[3];
    Shader m_shader;
    VertexArray m_vertexArray;
    Vertex2<Vector2F, ColorF> m_vertices[3];

    typedef Vertex2<Vector2F, ColorF> Vertex;
};

}
#endif // TRIANGLE_H
