#include <Grafit/Graphics/shaders/shaders.hpp>
#include <iostream>

extern unsigned char Graphics_shaders_v330_positioncolor_frag[];
extern unsigned int  Graphics_shaders_v330_positioncolor_frag_len;

extern unsigned char Graphics_shaders_v330_positioncolor_vert[];
extern unsigned int  Graphics_shaders_v330_positioncolor_vert_len;

extern unsigned char Graphics_shaders_v330_positiontexture_frag[];
extern unsigned int  Graphics_shaders_v330_positiontexture_frag_len;

extern unsigned char Graphics_shaders_v330_positiontexture_vert[];
extern unsigned int  Graphics_shaders_v330_positiontexture_vert_len;

extern unsigned char Graphics_shaders_v330_dither_2x2_frag[];
extern unsigned int  Graphics_shaders_v330_dither_2x2_frag_len;

extern unsigned char Graphics_shaders_v330_dither_4x4_frag[];
extern unsigned int  Graphics_shaders_v330_dither_4x4_frag_len;

extern unsigned char Graphics_shaders_v330_dither_8x8_frag[];
extern unsigned int  Graphics_shaders_v330_dither_8x8_frag_len;

extern unsigned char Graphics_shaders_v330_luma_luma_frag[];
extern unsigned int  Graphics_shaders_v330_luma_luma_frag_len;

extern unsigned char Graphics_shaders_v330_water_water2d_frag[];
extern unsigned int Graphics_shaders_v330_water_water2d_frag_len;

namespace gf {

std::string positionColor_frag = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_positioncolor_frag[0]), Graphics_shaders_v330_positioncolor_frag_len);
std::string positionColor_vert = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_positioncolor_vert[0]), Graphics_shaders_v330_positioncolor_vert_len);

std::string positionTexture_frag = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_positiontexture_frag[0]), Graphics_shaders_v330_positiontexture_frag_len);
std::string positionTexture_vert = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_positiontexture_vert[0]), Graphics_shaders_v330_positiontexture_vert_len);

std::string luma_frag = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_luma_luma_frag[0]), Graphics_shaders_v330_luma_luma_frag_len);
std::string dither2x2_frag = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_dither_2x2_frag[0]), Graphics_shaders_v330_dither_2x2_frag_len);
std::string dither4x4_frag = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_dither_4x4_frag[0]), Graphics_shaders_v330_dither_4x4_frag_len);
std::string dither8x8_frag = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_dither_8x8_frag[0]), Graphics_shaders_v330_dither_8x8_frag_len);
std::string water2d_frag = std::string(reinterpret_cast<char*>(&Graphics_shaders_v330_water_water2d_frag[0]), Graphics_shaders_v330_water_water2d_frag_len);

void dump() {

}

}
