#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <Grafit/Graphics/GL/glad.h>
#include <GLFW/glfw3.h>

namespace gf {
namespace priv {

#define GL_CHECK(x) x; gf::priv::glCheckError(__FILE__, __LINE__);

void glCheckError(const char* file, unsigned int line);

}

}


#endif // OPENGL_HPP

