#include <icebird/Graphics/Shaders.hpp>
#include <string>
#include <cstddef>

#define EXTERN_BINARY_START(source)                                     \
    extern const char _binary_##source##_start, _binary_##source##_end; \
    std::size_t _binary_##source##_len = &_binary_##source##_end - &_binary_##source##_start

#define STRINGIFY(A) #A

EXTERN_BINARY_START(icebird_src_icebird_Graphics_shaders_v330_positionColor_frag);
const char* positionColor_frag = &_binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_frag_start;
unsigned int positionColor_frag_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_frag_len;

EXTERN_BINARY_START(icebird_src_icebird_Graphics_shaders_v330_positionColor_vert);
const char* positionColor_vert = &_binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_vert_start;
unsigned int positionColor_vert_len = _binary_icebird_src_icebird_Graphics_shaders_v330_positionColor_vert_len;
