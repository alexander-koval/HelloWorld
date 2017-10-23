#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <string>

namespace gf {

extern std::string positionColor_frag;
extern std::string positionColor_vert;

extern std::string positionTexture_frag;
extern std::string positionTexture_vert;

extern std::string luma_glsl;
extern std::string dither2x2_glsl;
extern std::string dither4x4_glsl;
extern std::string dither8x8_glsl;
extern std::string water2d_glsl;

void dump();

}
#endif // SHADERS_HPP

