#include <icebird/Graphics/Triangle.hpp>
#include <icebird/Graphics/Shaders.hpp>
#include <glm/gtc/type_ptr.hpp>

Triangle::Triangle() {
    m_shader.loadFromMemory(positionColor_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(positionColor_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());
    GL_CHECK(m_shader.use());
    m_shader.setParameter<Shader::Uniform>("MVP");
    m_shader.setParameter<Shader::Attribute>("VertexPosition");
    m_shader.setParameter<Shader::Attribute>("VertexColor");
    GL_CHECK(m_shader.unuse());

    m_vertices[0].color = glm::vec3(1, 0, 0);
    m_vertices[1].color = glm::vec3(0, 1, 0);
    m_vertices[2].color = glm::vec3(0, 0, 1);

    m_vertices[0].position = glm::vec3(-1, -1, 0);
    m_vertices[1].position = glm::vec3( 0,  1, 0);
    m_vertices[2].position = glm::vec3( 1, -1, 0);

    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;

    GL_CHECK(glGenVertexArrays(1, &m_vaoID));
    GL_CHECK(glGenBuffers(1, &m_vboID[0]));
    GL_CHECK(glGenBuffers(1, &m_vboID[1]));
    GLsizei stride = sizeof(Vertex);

    GL_CHECK(glBindVertexArray(m_vaoID));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices[0], GL_STATIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(m_shader.getParameterID<Shader::Uniform>("VertexPosition")));
    GL_CHECK(glVertexAttribPointer(m_shader.getParameterID<Shader::Attribute>("VertexPosition"), 3, GL_FLOAT, GL_FALSE, stride, 0));

    GL_CHECK(glEnableVertexAttribArray(m_shader.getParameterID<Shader::Attribute>("VertexColor")));
    GL_CHECK(glVertexAttribPointer(m_shader.getParameterID<Shader::Attribute>("VertexColor"), 3, GL_FLOAT, GL_FALSE, stride,
             (const GLvoid*)offsetof(Vertex, color)));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboID[1]));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices[0], GL_STATIC_DRAW));

    GL_CHECK(glBindVertexArray(0));
}

void Triangle::render(glm::mat4 mvpView) {
    m_shader.use();
    GL_CHECK(glBindVertexArray(m_vaoID));
    m_shader.setParameter<Shader::Uniform>("MVP", mvpView);
//    GL_CHECK(glUniformMatrix4fv(m_shader.getUniformID("MVP"), 1, GL_FALSE, glm::value_ptr(mvpView)));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0));
    GL_CHECK(glBindVertexArray(0));
    m_shader.unuse();
}

Triangle::~Triangle() {

}

