#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <Grafit/Graphics/Transformable.hpp>
#include <Grafit/Graphics/Drawable.hpp>
#include <Grafit/Graphics/ImageData.hpp>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/Texture.hpp>
#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Vertex.hpp>
#include <Grafit/Graphics/Transform.hpp>
#include <Grafit/Graphics/VBO.hpp>
#include <Grafit/Graphics/VertexArray.hpp>

namespace gf {
class Bitmap : public Drawable, public Transformable {
public:
    Bitmap();

    void render(Mat4f mvpView);

    ~Bitmap();

protected:
    virtual void draw(RenderTarget &target, RenderStates states) const;

private:
    BitmapData m_image;
    Shader m_shader;
    Texture m_texture;
    GLushort m_indices[6];
    Transform m_transform;
    VertexArray m_vertexArray;
    Vertex2<Vector2F, Vector2F> m_vertices[4];

    typedef Vertex2<Vector2F, Vector2F> Vertex;
};
}
#endif // IMAGE_HPP
