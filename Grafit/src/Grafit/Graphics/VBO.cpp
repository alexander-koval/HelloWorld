#include <Grafit/Graphics/VBO.hpp>
#include <iostream>

namespace gf {

VertexBuffer::VertexBuffer(void)
    : m_usage(GL_STATIC_DRAW)
    , m_numVertices(0)
    , m_vbo(0)
    , m_sizePerVertex(0) {

}

VertexBuffer::~VertexBuffer(void) {
    if (glIsBuffer(m_vbo)) {
        GL_CHECK(glDeleteBuffers(1, &m_vbo));
        m_vbo = 0;
    }
}

bool VertexBuffer::create(Int32 sizePerVertex, Int32 numVertices, GLenum usage/* = GL_STATIC_DRAW*/) {
    if (0 == sizePerVertex || 0 == numVertices) {
        return false;
    }
    m_sizePerVertex = sizePerVertex;
    m_numVertices = numVertices;
    m_usage = usage;

    GL_CHECK(glGenBuffers(1, &m_vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, getSize(), NULL, m_usage));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    return true;
}

Int32 VertexBuffer::getSizePerVertex(void) const {
    return m_sizePerVertex;
}

Int32 VertexBuffer::getNumVertices(void) const {
    return m_numVertices;
}

bool VertexBuffer::update(const void *vertices, Int32 count, Int32 begin) {
    if (count <= 0 || NULL == vertices) {
        return false;
    }
    if (begin < 0) {
        std::cerr << "Update vertices with begin = " << begin
                  << ", will set begin to 0" << std::endl;
        begin = 0;
    }
    if (count + begin > m_numVertices) {
        std::cerr << "Updated vertices exceed the max size of vertex buffer, will set count to m_numVertices - begin" << std::endl;
        count = m_numVertices - begin;
    }
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, begin * m_sizePerVertex, count * m_sizePerVertex, vertices));

//    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    return true;
}

GLuint VertexBuffer::getVBO(void) const {
    return m_vbo;
}

Int32 VertexBuffer::getSize(void) const {
    return m_sizePerVertex * m_numVertices;
}

IndexBuffer::IndexBuffer(void)
    : m_usage(GL_STATIC_DRAW)
    , m_numIndices(0)
    , m_vbo(0)
    , m_sizePerIndex(0) {

}

IndexBuffer::~IndexBuffer(void) {
    if (glIsBuffer(m_vbo)) {
        GL_CHECK(glDeleteBuffers(1, &m_vbo));
        m_vbo = 0;
    }
}

bool IndexBuffer::create(Int32 sizePerIndex, Int32 numIndices, GLenum usage/* = GL_STATIC_DRAW*/) {
    if (numIndices <= 0) {
        return false;
    }
    m_sizePerIndex = sizePerIndex;
    m_numIndices = numIndices;
    m_usage = usage;

    GL_CHECK(glGenBuffers(1, &m_vbo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, getSize(), NULL, m_usage));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    return true;
}

Int32 IndexBuffer::getSizePerIndex(void) const {
    return m_sizePerIndex;
}

Int32 IndexBuffer::getNumIndices(void) const {
    return m_numIndices;
}

bool IndexBuffer::update(const void *indices, Int32 count, Int32 begin) {
    if (count <= 0 || NULL == indices) {
        return false;
    }
    if (begin < 0) {
        std::cerr << "Update indices with begin = " << begin
                  << ", will set begin to 0" << std::endl;
        begin = 0;
    }
    if (count + begin > m_numIndices) {
        std::cerr << "Updated indices exceed the max size of vertex buffer, will set to m_numIndices - begin" << std::endl;
        count = m_numIndices - begin;
    }
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, begin * getSizePerIndex(), count * getSizePerIndex(), indices));

//    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    return true;
}

Int32 IndexBuffer::getSize(void) const {
    return getSizePerIndex() * m_numIndices;
}

GLuint IndexBuffer::getVBO(void) const {
    return m_vbo;
}

}
