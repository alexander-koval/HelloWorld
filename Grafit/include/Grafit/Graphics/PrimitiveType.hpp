#ifndef PRIMITIVETYPE_HPP
#define PRIMITIVETYPE_HPP

#include <Grafit/Graphics/OpenGL.hpp>

namespace gf {

enum PrimitiveType {
    Points          = GL_POINTS,         ///< List of individual points
    Lines           = GL_LINES,          ///< List of individual lines
    LinesStrip      = GL_LINE_STRIP,     ///< List of connected lines, a point uses the previous point to form a line
    LinesLoop       = GL_LINE_LOOP,
    Triangles       = GL_TRIANGLES,      ///< List of individual triangles
    TrianglesStrip  = GL_TRIANGLE_STRIP, ///< List of connected triangles, a point uses the two previous points to form a triangle
    TrianglesFan    = GL_TRIANGLE_FAN,   ///< List of connected triangles, a point uses the common center and the previous point to form a triangle
};

} // namespace gf


#endif // PRIMITIVETYPE_HPP
