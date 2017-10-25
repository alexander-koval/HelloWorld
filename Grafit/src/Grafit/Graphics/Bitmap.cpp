#include <Grafit/Graphics/Bitmap.hpp>
#include <Grafit/Graphics/RenderTarget.hpp>
#include <Grafit/Graphics/shaders/shaders.hpp>
#include <Grafit/System/File.hpp>


namespace gf {
Bitmap::Bitmap(const gf::File& file) {
    m_transform = Transform::Identity;
    m_image.create(file);
    m_texture.create(m_image, RectI(0, 0, 512, 512));
    m_shader.loadFromMemory(positionTexture_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(luma_glsl, GL_FRAGMENT_SHADER);
    m_shader.loadFromMemory(dither2x2_glsl, GL_FRAGMENT_SHADER);
    m_shader.loadFromMemory(dither4x4_glsl, GL_FRAGMENT_SHADER);
    m_shader.loadFromMemory(dither8x8_glsl, GL_FRAGMENT_SHADER);
    m_shader.loadFromMemory(positionTexture_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());
    GL_CHECK(m_shader.use());
    GL_CHECK(m_shader.setUniform("MVP"));
    GL_CHECK(m_shader.setUniform("TextureMap", 0));
    GL_CHECK(m_shader.setAttribute("VertexPosition"));
    GL_CHECK(m_shader.setAttribute("VertexTexCoord"));
    GL_CHECK(m_shader.unuse());

    m_vertices[0].value1 = Vector2F(0.0f, 0.0f);
    m_vertices[1].value1 = Vector2F(512.0f, 0.0f);
    m_vertices[2].value1 = Vector2F(512.0f, 512.0f);
    m_vertices[3].value1 = Vector2F(0.0f, 512.0f);

//    m_vertices[0].value2 = Vector2F(0.0f, 0.0f);
//    m_vertices[1].value2 = Vector2F(1.0f, 0.0f);
//    m_vertices[2].value2 = Vector2F(1.0f, 1.0f);
//    m_vertices[3].value2 = Vector2F(0.0f, 1.0f);

    m_vertices[0].value2 = Vector2F(0.0f, 1.0f);
    m_vertices[1].value2 = Vector2F(1.0f, 1.0f);
    m_vertices[2].value2 = Vector2F(1.0f, 0.0f);
    m_vertices[3].value2 = Vector2F(0.0f, 0.0f);

    GLushort* id = &m_indices[0];
    id[0] = 0; id[1] = 1; id[2] = 2;
    id[3] = 0; id[4] = 2; id[5] = 3;

    m_vertexArray.initialize();
    m_vertexArray.create<VertexBuffer>(sizeof(Vertex), 4);
    m_vertexArray.create<IndexBuffer>(sizeof(GLushort), 6);

    m_vertexArray.use();
    m_vertexArray.update<VertexBuffer>(&m_vertices[0], 4, 0);
    m_vertexArray.update<IndexBuffer>(&m_indices[0], 6, 0);
    m_shader.setAttribute("VertexPosition", m_vertexArray.getVertexBuffer(), 2, GL_FLOAT, GL_FALSE, nullptr);
    m_shader.setAttribute("VertexTexCoord", m_vertexArray.getVertexBuffer(), 2, GL_FLOAT, GL_FALSE,
                                             (const GLvoid*)offsetof(Vertex, value2));
    m_vertexArray.unuse();
}

void Bitmap::render(Mat4F mvpView) {
    m_shader.use();
    m_vertexArray.use();
    mvpView = mvpView * getTransform().getMatrix();
    m_shader.setUniform("MVP", mvpView);
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
    m_vertexArray.unuse();
    m_shader.unuse();
}

void Bitmap::draw(const RenderTarget &target, RenderStates states) const {
    states.shader = &m_shader;
    states.texture = &m_texture;
//    rotate(1);
    states.transform = getTransform();
    target.draw(m_vertexArray, PrimitiveType::Triangles, states);
//    target.draw(m_vertices, 4, PrimitiveType::Triangles, states);
//    m_shader.use();
//    m_vertexArray.use();
//    mvpView = mvpView * getTransform().getMatrix();
//    m_shader.setParameter<Shader::Uniform>("MVP", mvpView);
//    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
//    m_vertexArray.unuse();
//    m_shader.unuse();
}

Bitmap::~Bitmap() {

}

}
