#include <icebird/Graphics/Shaders.hpp>
#include <string>
#include <cstddef>

#define EXTERN_BINARY_SOURCE(source)                                     \
    extern const char _binary_##source##_start, _binary_##source##_end; \
    std::size_t _binary_##source##_len = &_binary_##source##_end - &_binary_##source##_start

EXTERN_BINARY_SOURCE(icebird_src_icebird_Graphics_shaders_v330_positionColor_frag);
unsigned int positionColor_frag_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_frag_len;
const std::string positionColor_frag = std::string(&_binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_frag_start,
                                                   positionColor_frag_len);

EXTERN_BINARY_SOURCE(icebird_src_icebird_Graphics_shaders_v330_positionColor_vert);
unsigned int positionColor_vert_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_vert_len;
const std::string positionColor_vert = std::string(&_binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_vert_start,
                                                   positionColor_vert_len);
