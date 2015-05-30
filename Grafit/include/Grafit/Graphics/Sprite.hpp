#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <Grafit/Graphics/Drawable.hpp>
#include <Grafit/Graphics/Transformable.hpp>
#include <Grafit/Graphics/Vertex.hpp>
#include <Grafit/Graphics/Geometry/Rect.hpp>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/Graphics/VertexArray.hpp>

namespace gf {
class Texture;

class Sprite : public Drawable, public Transformable {
public:
    Sprite();

    explicit Sprite(const Texture& texture);

    Sprite(const Texture& texture, const RectI& rect);

    void setTexture(const Texture& texture, bool resetRect = false);

    void setTextureRect(const RectI& rect);

    const Texture* getTexture(void) const;

    const RectI& getTextureRect(void) const;

    RectF getLocalBounds(void) const;

    RectF getGlobalBounds(void) const;

private:
    virtual void draw(RenderTarget& target, RenderStates states);

    void updatePositions(void);

    void updateTexCoords();

    Shader m_shader;
    GLushort m_indices[6];
    Vertex2<Vector2F, Vector2F> m_vertices[4];
    const Texture*              m_texture;
    RectI                       m_textureRect;
    VertexArray m_vertexArray;

    typedef VertexP2F_T2F Vertex;
};

}

#endif // SPRITE_HPP

