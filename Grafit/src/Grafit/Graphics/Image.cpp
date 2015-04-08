#include <Grafit/Graphics/Image.hpp>
#include <Grafit/Graphics/shaders/shaders.hpp>

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
#else
const std::string filename = "Resources/Lenna.png";
#endif

namespace gf {
Image::Image() {
    m_transform = Transform::Identity;
    m_image.loadFromFile(filename);
//    m_image.flipY();
    m_texture.loadFromImage(m_image, glm::vec2(/*256, 512*/));
//    m_shader.loadFromMemory(luma_glsl, GL_FRAGMENT_SHADER);
//    m_shader.loadFromMemory(dither2x2_glsl, GL_FRAGMENT_SHADER);
    m_shader.loadFromMemory(positionTexture_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(positionTexture_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());
    GL_CHECK(m_shader.use());
    GL_CHECK(m_shader.setParameter<Shader::Attribute>("VertexPosition"));
    GL_CHECK(m_shader.setParameter<Shader::Attribute>("VertexTexCoord"));
    GL_CHECK(m_shader.setParameter<Shader::Uniform>("TextureMap"));
    GL_CHECK(m_shader.setParameter<Shader::Uniform>("MVP"));
    GL_CHECK(m_shader.setParameter<Shader::Uniform>("TextureMap", 0));
    GL_CHECK(m_shader.unuse());

    m_vertices[0].value1 = Vector2F(0.0f, 0.0f);
    m_vertices[1].value1 = Vector2F(1.0f, 0.0f);
    m_vertices[2].value1 = Vector2F(1.0f, 1.0f);
    m_vertices[3].value1 = Vector2F(0.0f, 1.0f);

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
    m_shader.setParameter<Shader::Attribute>("VertexPosition", m_vertexArray.getVertexBuffer(), 2, GL_FLOAT, GL_FALSE, 0);
    m_shader.setParameter<Shader::Attribute>("VertexTexCoord", m_vertexArray.getVertexBuffer(), 2, GL_FLOAT, GL_FALSE,
                                             (const GLvoid*)offsetof(Vertex, value2));
    m_vertexArray.unuse();
}

void Image::render(Mat4f mvpView) {
    m_shader.use();
    m_vertexArray.use();
    mvpView = mvpView * Mat4f(getTransform().getInverse().getMatrix());
    m_shader.setParameter<Shader::Uniform>("MVP", mvpView);
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
    m_vertexArray.unuse();
    m_shader.unuse();
}

Image::~Image() {

}

}
