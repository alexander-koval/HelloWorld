#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <icebird/Graphics/Image.hpp>
#include <icebird/Graphics/ImageData.hpp>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/Texture.hpp>
#include <icebird/Graphics/Geometry/Mat4.hpp>
#include <glm/matrix.hpp>

class Image
{
public:
    Image();

    void render(Mat4f mvpView);

    ~Image();

private:
    struct Vertex {
        glm::vec2 position;

    };

    ImageData m_image;
    Shader m_shader;
    Texture m_texture;
    GLuint m_vaoID;
    GLuint m_vboID[2];
    Vertex m_vertices[4];
    GLushort m_indices[6];
};

#endif // PICTURE_HPP
