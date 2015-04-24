#ifndef PRIMITIVETYPE_HPP
#define PRIMITIVETYPE_HPP

namespace gf {

enum PrimitiveType {
    Points,         ///< List of individual points
    Lines,          ///< List of individual lines
    LinesStrip,     ///< List of connected lines, a point uses the previous point to form a line
    Triangles,      ///< List of individual triangles
    TrianglesStrip, ///< List of connected triangles, a point uses the two previous points to form a triangle
    TrianglesFan,   ///< List of connected triangles, a point uses the common center and the previous point to form a triangle
};

} // namespace gf


#endif // PRIMITIVETYPE_HPP
