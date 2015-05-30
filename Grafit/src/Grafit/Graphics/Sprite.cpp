#include <Grafit/Graphics/Sprite.hpp>
#include <Grafit/Graphics/Texture.hpp>
#include <Grafit/Graphics/RenderTarget.hpp>
#include <Grafit/Graphics/shaders/shaders.hpp>
#include <cstdlib>

namespace gf {

Sprite::Sprite(void)
    : m_shader()
    , m_indices()
    , m_vertices()
    , m_texture(NULL)
    , m_textureRect()
    , m_vertexArray() {
    GLushort* id = &m_indices[0];
    id[0] = 0; id[1] = 1; id[2] = 2;
    id[3] = 0; id[4] = 2; id[5] = 3;

    m_vertexArray.initialize();
    m_vertexArray.create<VertexBuffer>(sizeof(Vertex), 4);
    m_vertexArray.create<IndexBuffer>(sizeof(GLushort), 6);

    m_shader.loadFromMemory(positionTexture_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(positionTexture_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());
}

Sprite::Sprite(const Texture& texture)
    : m_shader()
    , m_indices()
    , m_vertices()
    , m_texture(NULL)
    , m_textureRect()
    , m_vertexArray() {
    GLushort* id = &m_indices[0];
    id[0] = 0; id[1] = 1; id[2] = 2;
    id[3] = 0; id[4] = 2; id[5] = 3;

    m_vertexArray.initialize();
    m_vertexArray.create<VertexBuffer>(sizeof(Vertex), 4);
    m_vertexArray.create<IndexBuffer>(sizeof(GLushort), 6);

    m_shader.loadFromMemory(positionTexture_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(positionTexture_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());

    setTexture(texture);
}

Sprite::Sprite(const Texture& texture, const RectI& rect)
    : m_shader()
    , m_indices()
    , m_vertices()
    , m_texture(NULL)
    , m_textureRect()
    , m_vertexArray() {
    GLushort* id = &m_indices[0];
    id[0] = 0; id[1] = 1; id[2] = 2;
    id[3] = 0; id[4] = 2; id[5] = 3;

    m_vertexArray.initialize();
    m_vertexArray.create<VertexBuffer>(sizeof(Vertex), 4);
    m_vertexArray.create<IndexBuffer>(sizeof(GLushort), 6);

    m_shader.loadFromMemory(positionTexture_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(positionTexture_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());

    setTexture(texture);
    setTextureRect(rect);
}

void Sprite::setTexture(const Texture& texture, bool resetRect) {
    if (resetRect || (!m_texture && (m_textureRect == RectI()))) {
        setTextureRect(RectI(0, 0, texture.getSize().x, texture.getSize().y));
    }
    m_texture = &texture;
}

void Sprite::setTextureRect(const RectI& rect) {
    if (rect != m_textureRect) {
        m_textureRect = rect;
        updatePositions();
        updateTexCoords();
    }
}

const Texture* Sprite::getTexture(void) const {
    return m_texture;
}

const RectI& Sprite::getTextureRect(void) const {
    return m_textureRect;
}

RectF Sprite::getLocalBounds(void) const {
    float width = static_cast<float>(std::abs(m_textureRect.width));
    float height = static_cast<float>(std::abs(m_textureRect.height));

    return RectF(0.f, 0.f, width, height);
}

RectF Sprite::getGlobalBounds(void) const {
    return getTransform().transformRect(getLocalBounds());
}

void Sprite::draw(RenderTarget& target, RenderStates states) {
    if (m_texture) {
        Transform transform = getTransform();
        states.transform = transform;
        states.texture = m_texture;
        states.shader = &m_shader;
        target.draw(m_vertexArray, PrimitiveType::Triangles, states);
    }
}

void Sprite::updatePositions(void) {
    RectF bounds = getLocalBounds();
    m_vertices[0].value1 = Vector2F(0.f, 0.f);
    m_vertices[3].value1 = Vector2F(0.f, bounds.height);
    m_vertices[1].value1 = Vector2F(bounds.width, 0.f);
    m_vertices[2].value1 = Vector2F(bounds.width, bounds.height);

    m_vertexArray.use();
    m_vertexArray.update<VertexBuffer>(&m_vertices[0], 4, 0);
    m_vertexArray.update<IndexBuffer>(&m_indices[0], 6, 0);
    m_shader.setParameter<Shader::Attribute>("VertexPosition", m_vertexArray.getVertexBuffer(), 2, GL_FLOAT, GL_FALSE, 0);
    m_vertexArray.unuse();
}

void Sprite::updateTexCoords(void) {
    float left   = static_cast<float>(m_textureRect.left);
    float right  = left + m_textureRect.width;
    float top    = static_cast<float>(m_textureRect.top);
    float bottom = top + m_textureRect.height;

    m_vertices[0].value2 = Vector2F(left  / m_textureRect.width, top    / m_textureRect.height);
    m_vertices[3].value2 = Vector2F(left  / m_textureRect.width, bottom / m_textureRect.height);
    m_vertices[1].value2 = Vector2F(right / m_textureRect.width, top    / m_textureRect.height);
    m_vertices[2].value2 = Vector2F(right / m_textureRect.width, bottom / m_textureRect.height);

    m_vertexArray.use();
    m_vertexArray.update<VertexBuffer>(&m_vertices[0], 4, 0);
    m_vertexArray.update<IndexBuffer>(&m_indices[0], 6, 0);
        m_shader.setParameter<Shader::Attribute>("VertexTexCoord", m_vertexArray.getVertexBuffer(), 2, GL_FLOAT, GL_FALSE,
                                             (const GLvoid*)offsetof(Vertex, value2));
    m_vertexArray.unuse();
}

}
