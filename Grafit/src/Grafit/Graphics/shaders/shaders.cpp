#include <Grafit/Graphics/shaders/shaders.hpp>

extern unsigned char Graphics_shaders_v330_positioncolor_frag[];
extern size_t Graphics_shaders_v330_positioncolor_frag_len;

extern unsigned char Graphics_shaders_v330_positioncolor_vert[];
extern size_t Graphics_shaders_v330_positioncolor_vert_len;

extern unsigned char Graphics_shaders_v330_positiontexture_frag[];
extern size_t Graphics_shaders_v330_positiontexture_frag_len;

extern unsigned char Graphics_shaders_v330_positiontexture_vert[];
extern size_t Graphics_shaders_v330_positiontexture_vert_len;

extern unsigned char Graphics_shaders_dither_2x2_glsl[];
extern size_t Graphics_shaders_dither_2x2_glsl_len;

extern unsigned char Graphics_shaders_dither_4x4_glsl[];
extern size_t Graphics_shaders_dither_4x4_glsl_len;

extern unsigned char Graphics_shaders_dither_8x8_glsl[];
extern size_t Graphics_shaders_dither_8x8_glsl_len;

extern unsigned char Graphics_shaders_luma_luma_glsl[];
extern size_t Graphics_shaders_luma_luma_glsl_len;

namespace gf {

std::string positionColor_frag = std::string((char*)&Graphics_shaders_v330_positioncolor_frag[0], Graphics_shaders_v330_positioncolor_frag_len);
std::string positionColor_vert = std::string((char*)&Graphics_shaders_v330_positioncolor_vert[0], Graphics_shaders_v330_positioncolor_vert_len);

std::string positionTexture_frag = std::string((char*)&Graphics_shaders_v330_positiontexture_frag[0], Graphics_shaders_v330_positiontexture_frag_len);
std::string positionTexture_vert = std::string((char*)&Graphics_shaders_v330_positiontexture_vert[0], Graphics_shaders_v330_positiontexture_vert_len);

//std::string luma_glsl = std::string((char*)&Graphics_shaders_luma_luma_glsl[0], Graphics_shaders_luma_luma_glsl_len);
//std::string dither2x2_glsl = std::string((char*)&Graphics_shaders_dither_2x2_glsl[0], Graphics_shaders_dither_2x2_glsl_len);
//std::string dither4x4_glsl = std::string((char*)&Graphics_shaders_dither_4x4_glsl[0], Graphics_shaders_dither_4x4_glsl_len);
//std::string dither8x8_glsl = std::string((char*)&Graphics_shaders_dither_8x8_glsl[0], Graphics_shaders_dither_8x8_glsl_len);

}
