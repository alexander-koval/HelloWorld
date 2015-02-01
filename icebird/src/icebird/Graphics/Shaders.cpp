#include <icebird/Graphics/Shaders.hpp>
#include <string>
#include <cstddef>

#define EXTERN_BINARY_SOURCE(source)                                     \
    extern const char _binary_##source##_start, _binary_##source##_end; \
    std::size_t _binary_##source##_len = &_binary_##source##_end - &_binary_##source##_start

EXTERN_BINARY_SOURCE(icebird_src_icebird_Graphics_shaders_v330_positioncolor_frag);
unsigned int positioncolor_frag_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positioncolor_frag_len;
const std::string positionColor_frag = std::string(&_binary_icebird_src_icebird_Graphics_shaders_v330_positioncolor_frag_start,
                                                   positioncolor_frag_len);

EXTERN_BINARY_SOURCE(icebird_src_icebird_Graphics_shaders_v330_positioncolor_vert);
unsigned int positioncolor_vert_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positioncolor_vert_len;
const std::string positionColor_vert = std::string(&_binary_icebird_src_icebird_Graphics_shaders_v330_positioncolor_vert_start,
                                                   positioncolor_vert_len);

EXTERN_BINARY_SOURCE(icebird_src_icebird_Graphics_shaders_v330_positiontexture_frag);
unsigned int positiontexture_frag_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positiontexture_frag_len;
const std::string positionTexture_frag = std::string(&_binary_icebird_src_icebird_Graphics_shaders_v330_positiontexture_frag_start,
                                                     positiontexture_frag_len);

EXTERN_BINARY_SOURCE(icebird_src_icebird_Graphics_shaders_v330_positiontexture_vert);
unsigned int positiontexture_vert_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positiontexture_vert_len;
const std::string positionTexture_vert = std::string(&_binary_icebird_src_icebird_Graphics_shaders_v330_positiontexture_vert_start,
                                                     positiontexture_vert_len);
