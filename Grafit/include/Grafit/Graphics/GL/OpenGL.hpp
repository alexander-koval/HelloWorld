#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <Grafit/Graphics/GL/glad.h>
#include <GLFW/glfw3.h>

#define GL_CHECK(x) x; glCheckError(__FILE__, __LINE__);

void glCheckError(const char* file, unsigned int line);

#endif // OPENGL_HPP
