#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <string>

extern unsigned char shaders_v330_positioncolor_frag[];
extern int shaders_v330_positioncolor_frag_len;

extern unsigned char shaders_v330_positioncolor_vert[];
extern int shaders_v330_positioncolor_vert_len;

extern unsigned char shaders_v330_positiontexture_frag[];
extern int shaders_v330_positiontexture_frag_len;

extern unsigned char shaders_v330_positiontexture_vert[];
extern int shaders_v330_positiontexture_vert_len;

std::string positionColor_frag = std::string((char*)&shaders_v330_positioncolor_frag[0], shaders_v330_positioncolor_frag_len);
std::string positionColor_vert = std::string((char*)&shaders_v330_positioncolor_vert[0], shaders_v330_positioncolor_vert_len);

std::string positionTexture_frag = std::string((char*)&shaders_v330_positiontexture_frag[0], shaders_v330_positiontexture_frag_len);
std::string positionTexture_vert = std::string((char*)&shaders_v330_positiontexture_vert[0], shaders_v330_positiontexture_vert_len);


#endif // SHADERS_HPP

