#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <Grafit/Graphics/OpenGL.hpp>

namespace gf {

class VertexArray {
public:
    VertexArray(void);

    ~VertexArray(void);

    bool create(void);

    bool update(void);

    void bind(void);

    void unbind(void);

protected:
    GLuint m_vaoID;
};
}
#endif // VERTEXARRAY_HPP
