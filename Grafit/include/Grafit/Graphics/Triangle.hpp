#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/GL/OpenGL.hpp>
#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Vertex.hpp>


class Triangle
{
public:
    Triangle();

    void render(Mat4f mvpView);

    ~Triangle();

private:
    GLuint m_vaoID;
    GLuint m_vboID[2];
    GLushort m_indices[3];
    Shader m_shader;
    Vertex2<Vector2F, ColorF> m_vertices[3];

    typedef Vertex2<Vector2F, ColorF> Vertex;
};

#endif // TRIANGLE_H
