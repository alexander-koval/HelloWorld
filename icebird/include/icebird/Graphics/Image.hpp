#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>

class Image {
public:
    Image(void);

    void render(glm::mat4 mvpView);

    ~Image(void);

private:
    struct Vertex {
        glm::vec2 position;

    };

    GLuint m_vaoID;
    GLuint m_vboID[2];
    GLuint m_textureID;
    Vertex m_vertices[4];
    GLushort m_indices[6];
    Shader m_shader;
};

#endif // IMAGE_HPP
