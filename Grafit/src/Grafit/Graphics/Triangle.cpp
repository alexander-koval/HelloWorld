#include <Grafit/Graphics/Triangle.hpp>
#include <Grafit/Graphics/Shaders.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gf {
Triangle::Triangle() {
    m_shader.loadFromMemory(gf::positionColor_vert, GL_VERTEX_SHADER);
    m_shader.loadFromMemory(positionColor_frag, GL_FRAGMENT_SHADER);
    GL_CHECK(m_shader.link());
    GL_CHECK(m_shader.use());
    m_shader.setUniform("MVP");
    m_shader.setAttribute("VertexPosition");
    m_shader.setAttribute("VertexColor");
    GL_CHECK(m_shader.unuse());

    m_vertices[0].value1 = Vector2F(-1.f, -1.f);
    m_vertices[1].value1 = Vector2F( 0.f,  1.f);
    m_vertices[2].value1 = Vector2F( 1.f, -1.f);

    m_vertices[0].value2 = ColorF::Red;
    m_vertices[1].value2 = ColorF::Green;
    m_vertices[2].value2 = ColorF::Blue;

    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;

    m_vertexArray.initialize();
    m_vertexArray.createVertices(sizeof(Vertex), 3);
    m_vertexArray.createIndices(sizeof(GLushort), 3);

    m_vertexArray.use();
    m_vertexArray.updateVertices(&m_vertices[0], 3, 0);
    m_vertexArray.updateIndices(&m_indices[0], 3, 0);
    m_shader.setAttribute("VertexPosition", m_vertexArray.getVertexBuffer(), 2, GL_FLOAT, GL_FALSE, nullptr);
    m_shader.setAttribute("VertexColor", m_vertexArray.getVertexBuffer(), 3, GL_FLOAT, GL_FALSE,
                                             (const GLvoid*)offsetof(Vertex, value2));
    m_vertexArray.unuse();
}

void Triangle::render(Mat4F mvpView) {
    m_shader.use();
    rotate(-1);
    mvpView = mvpView * getTransform().getMatrix();
    m_shader.setUniform("MVP", mvpView);
    m_vertexArray.use();
//    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0));
    m_vertexArray.unuse();
    m_shader.unuse();
}

Triangle::~Triangle() {

}

}
