#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/Graphics/VBO.hpp>

namespace gf {

class VertexArray {
public:
    VertexArray(void);

    VertexArray(VertexBuffer& indexBuffer, IndexBuffer& vertexBuffer);

    ~VertexArray(void);

    void initialize(void);

    template <typename Type>
    bool create(Int32 sizePerVertex, Int32 count, GLenum usage = GL_STATIC_DRAW);

    template <typename Type>
    bool update(const void* data, Int32 count, Int32 begin);

    void use(void) const;

    void unuse(void) const;

    const VertexBuffer& getVertexBuffer(void) const;

    const IndexBuffer& getIndexBuffer(void) const;

protected:
    GLuint m_vaoID;
    IndexBuffer m_indexBuffer;
    VertexBuffer m_vertexBuffer;
};
}
#endif // VERTEXARRAY_HPP
