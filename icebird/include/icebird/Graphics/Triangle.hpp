#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <icebird/Graphics/glm/glm.hpp>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>

class Triangle
{
public:
    Triangle();

    void render(glm::mat4 mvpView);

    ~Triangle();

private:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };

    GLuint m_vaoID;
    GLuint m_vboID[2];
    Vertex m_vertices[3];
    GLushort m_indices[3];
    Shader m_shader;
};

#endif // TRIANGLE_H
