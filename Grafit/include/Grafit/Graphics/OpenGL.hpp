#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <Grafit/Graphics/GL/glad.h>
#include <GLFW/glfw3.h>

namespace priv {

#define GL_CHECK(x) x; priv::glCheckError(__FILE__, __LINE__)

void glCheckError(const char* file, unsigned int line);

}


#endif // OPENGL_HPP

