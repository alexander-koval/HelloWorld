#include <icebird/Graphics/Image.hpp>
#include <icebird/Graphics/shaders/shaders.hpp>

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
#else
const std::string filename = "Resources/Lenna.png";
#endif
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
    GL_CHECK(glUniform1i(m_shader.getParameterID<Shader::Uniform>("TextureMap"), 0));
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

    GL_CHECK(glGenVertexArrays(1, &m_vaoID));
    GL_CHECK(glGenBuffers(1, &m_vboID[0]));
    GL_CHECK(glGenBuffers(1, &m_vboID[1]));

    GLsizei stride = sizeof(Vertex);
    long unsigned int offset = offsetof(Vertex, value2);

    GL_CHECK(glBindVertexArray(m_vaoID));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices[0], GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(m_shader.getParameterID<Shader::Attribute>("VertexPosition")));
    GL_CHECK(glVertexAttribPointer(m_shader.getParameterID<Shader::Attribute>("VertexPosition"), 4,  GL_FLOAT, GL_FALSE, stride, 0));

    GL_CHECK(glEnableVertexAttribArray(m_shader.getParameterID<Shader::Attribute>("VertexTexCoord")));
    GL_CHECK(glVertexAttribPointer(m_shader.getParameterID<Shader::Attribute>("VertexTexCoord"), 4, GL_FLOAT, GL_FALSE, stride,
                                   (const GLvoid*)offset))

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboID[1]));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices[0], GL_STATIC_DRAW));

    GL_CHECK(glBindVertexArray(0));
}

void Image::render(Mat4f mvpView) {
    m_shader.use();
    GL_CHECK(glBindVertexArray(m_vaoID));
    m_shader.setParameter<Shader::Uniform>("MVP", mvpView);
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
    GL_CHECK(glBindVertexArray(0));
    m_shader.unuse();
}

Image::~Image() {

}

