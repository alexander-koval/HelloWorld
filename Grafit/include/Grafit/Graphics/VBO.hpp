#ifndef VBO
#define VBO

#include <Grafit/System/Types.hpp>
#include <Grafit/Graphics/GL/OpenGL.hpp>

class VertexBuffer {
public:
    VertexBuffer(void);

    ~VertexBuffer(void);

    bool initialize(Int32 sizePerVertex, Int32 numVertices, GLenum usage = GL_STATIC_DRAW);

    Int32 getSizePerVertex(void) const;

    Int32 getNumVertices(void) const;

    bool update(const void* vertices, Int32 count, Int32 begin);

    Int32 getSize(void) const;

    GLuint getVBO(void) const;

protected:
    GLenum m_usage;
    Int32 m_numVertices;
    mutable GLuint m_vbo;
    Int32 m_sizePerVertex;
};

class IndexBuffer {
public:
    IndexBuffer(void);

    ~IndexBuffer(void);

    bool initialize(Int32 sizePerIndex, Int32 numIndices, GLenum usage = GL_STATIC_DRAW);

    Int32 getSizePerIndex(void) const;

    Int32 getNumIndices(void) const;

    bool update(const void* indices, Int32 count, Int32 begin);

    Int32 getSize(void) const;

    GLuint getVBO(void) const;

protected:
    GLenum m_usage;
    Int32 m_numIndices;
    mutable GLuint m_vbo;
    Int32 m_sizePerIndex;
};

#endif // VBO

