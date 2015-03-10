#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <icebird/Graphics/Image.hpp>
#include <icebird/Graphics/ImageData.hpp>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/Texture.hpp>
#include <icebird/Graphics/Geometry/Mat4.hpp>
#include <icebird/Graphics/Vertex.hpp>
#include <icebird/Graphics/Transform.hpp>
#include <glm/matrix.hpp>

class Image
{
public:
    Image();

    void render(Mat4f mvpView);

    ~Image();

private:
    ImageData m_image;
    Shader m_shader;
    Texture m_texture;
    GLuint m_vaoID;
    GLuint m_vboID[2];
    GLushort m_indices[6];
    Transform m_transform;
    Vertex2<Vector2F, Vector2F> m_vertices[4];

    typedef Vertex2<Vector2F, Vector2F> Vertex;
};

#endif // PICTURE_HPP
