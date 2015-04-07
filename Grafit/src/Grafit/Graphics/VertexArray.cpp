#include <Grafit/Graphics/VertexArray.hpp>

namespace gf {

VertexArray::VertexArray(void)
    : m_vaoID(0) {

}

VertexArray::~VertexArray(void) {
    if (glIsVertexArray(m_vaoID)) {
        GL_CHECK(glDeleteVertexArrays(1, &m_vaoID));
        m_vaoID = 0;
    }
}

bool VertexArray::create(void) {
    GL_CHECK(glGenVertexArrays(1, &m_vaoID));
}

bool VertexArray::update(void) {

}

void VertexArray::bind(void) {
    glBindVertexArray(m_vaoID);
}

void VertexArray::unbind(void) {
    glBindVertexArray(m_vaoID);
}

}
