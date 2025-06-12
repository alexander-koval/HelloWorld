#include <Grafit/Graphics/VertexArray.hpp>
#include <Grafit/Graphics/VBO.hpp>
#include <cassert>
#include <iostream>

namespace gf {

VertexArray::VertexArray(void)
    : m_vaoID(0)
    , m_indexBuffer()
    , m_vertexBuffer() {

}

VertexArray::VertexArray(VertexBuffer& vertexBuffer, IndexBuffer&indexBuffer)
    : m_vaoID(0)
    , m_indexBuffer(indexBuffer)
    , m_vertexBuffer(vertexBuffer) {

}

VertexArray::~VertexArray(void) {
    if (glIsVertexArray(m_vaoID)) {
        GL_CHECK(glDeleteVertexArrays(1, &m_vaoID));
        m_vaoID = 0;
    }
}

void VertexArray::initialize(void) {
    GL_CHECK(glGenVertexArrays(1, &m_vaoID));
    assert(m_vaoID >= 0);
}

bool VertexArray::createVertices(Int32 sizePerVertex, Int32 count, GLenum usage) {
    return m_vertexBuffer.create(sizePerVertex, count, usage);
}

bool VertexArray::createIndices(Int32 sizePerVertex, Int32 count, GLenum usage) {
    return m_indexBuffer.create(sizePerVertex, count, usage);
}

bool VertexArray::updateVertices(const void* data, Int32 count, Int32 begin) {
    return m_vertexBuffer.update(data, count, begin);
}

bool VertexArray::updateIndices(const void* data, Int32 count, Int32 begin) {
    return m_indexBuffer.update(data, count, begin);
}

void VertexArray::use(void) const {
    GL_CHECK(glBindVertexArray(m_vaoID));

}

void VertexArray::unuse(void) const {
    if (glIsVertexArray(m_vaoID)) {
        GL_CHECK(glBindVertexArray(0));
    }
}

const VertexBuffer& VertexArray::getVertexBuffer(void) const {
    return m_vertexBuffer;
}

const IndexBuffer& VertexArray::getIndexBuffer(void) const {
    return m_indexBuffer;
}

}
