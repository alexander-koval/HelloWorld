#ifndef SHADERS_H
#define SHADERS_H

#include <string>

namespace gf {

extern const std::string positionColor_frag;

extern const std::string positionColor_vert;

extern const std::string positionTexture_frag;

extern const std::string positionTexture_vert;

extern std::string luma_glsl;

extern std::string dither2x2_glsl;

extern std::string dither4x4_glsl;

extern std::string dither8x8_glsl;

}
#endif // SHADERS_H
