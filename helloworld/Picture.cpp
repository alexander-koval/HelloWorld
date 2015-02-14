#include "Picture.hpp"
#include <icebird/Graphics/shaders/shaders.hpp>

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
#else
const std::string filename = "Resources/Lenna.png";
#endif

Picture::Picture() {
    m_image.loadFromFile(filename);
    m_image.flipY();
    m_texture.loadFromImage(m_image, glm::vec2(/*256, 512*/));
    m_shader.loadFromMemory(positionTexture_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(positionTexture_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());
    GL_CHECK(m_shader.use());
    GL_CHECK(m_shader.setParameter<Shader::Attribute>("VertexPosition"));
    GL_CHECK(m_shader.setParameter<Shader::Uniform>("TextureMap"));
    GL_CHECK(m_shader.setParameter<Shader::Uniform>("MVP"));
    GL_CHECK(glUniform1i(m_shader.getParameterID<Shader::Uniform>("TextureMap"), 0));
    GL_CHECK(m_shader.unuse());

    m_vertices[0].position = glm::vec2(0.0f, 0.0f);
    m_vertices[1].position = glm::vec2(1.0f, 0.0f);
    m_vertices[2].position = glm::vec2(1.0f, 1.0f);
    m_vertices[3].position = glm::vec2(0.0f, 1.0f);

    GLushort* id = &m_indices[0];
    id[0] = 0; id[1] = 1; id[2] = 2;
    id[3] = 0; id[4] = 2; id[5] = 3;

    GL_CHECK(glGenVertexArrays(1, &m_vaoID));
    GL_CHECK(glGenBuffers(1, &m_vboID[0]));
    GL_CHECK(glGenBuffers(1, &m_vboID[1]));
    GL_CHECK(glBindVertexArray(m_vaoID));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices[0], GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(m_shader.getParameterID<Shader::Attribute>("VertexPosition")));
    GL_CHECK(glVertexAttribPointer(m_shader.getParameterID<Shader::Attribute>("VertexPosition"), 2,  GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboID[1]));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices[0], GL_STATIC_DRAW));

    GL_CHECK(glBindVertexArray(0));
}

void Picture::render(glm::mat4 mvpView) {
    m_shader.use();
    GL_CHECK(glBindVertexArray(m_vaoID));
    m_shader.setParameter<Shader::Uniform>("MVP", mvpView);
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
    GL_CHECK(glBindVertexArray(0));
    m_shader.unuse();
}

Picture::~Picture() {

}

