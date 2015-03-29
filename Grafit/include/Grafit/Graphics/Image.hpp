#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <Grafit/Graphics/Image.hpp>
#include <Grafit/Graphics/ImageData.hpp>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/Texture.hpp>
#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Vertex.hpp>
#include <Grafit/Graphics/Transform.hpp>
#include <glm/matrix.hpp>

namespace gf {
class Image {
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
}
#endif // IMAGE_HPP
