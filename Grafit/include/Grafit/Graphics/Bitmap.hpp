#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <Grafit/Graphics/Transformable.hpp>
#include <Grafit/Graphics/Drawable.hpp>
#include <Grafit/Graphics/Image.hpp>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/Texture.hpp>
#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Vertex.hpp>
#include <Grafit/Graphics/Transform.hpp>
#include <Grafit/Graphics/VBO.hpp>
#include <Grafit/Graphics/VertexArray.hpp>
#include <Grafit/System/PlatformMacros.hpp>

namespace gf {
class Bitmap : public Drawable, public Transformable {
public:
    Bitmap(const std::string& filename);

    void render(Mat4F mvpView);

    ~Bitmap();

protected:
    virtual void draw(const RenderTarget &target, RenderStates states) const;

private:
    Image m_image;
    mutable Shader m_shader;
    Texture m_texture;
    GLushort m_indices[6];
    Transform m_transform;
    VertexArray m_vertexArray;
    Vertex2<Vector2F, Vector2F> m_vertices[4];

    typedef VertexP2F_T2F Vertex;
};
}
#endif // IMAGE_HPP
