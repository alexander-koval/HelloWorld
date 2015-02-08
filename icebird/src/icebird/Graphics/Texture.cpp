#include <icebird/Graphics/Texture.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>
#include <SOIL.h>

Texture::Texture(void)
    : m_size(0, 0)
    , m_actualSize(0, 0)
    , m_texture(0)
    , m_isSmooth(false)
    , m_isRepeated(false) {

}

Texture::Texture(const Texture &copy)
    : m_size(0, 0)
    , m_actualSize(0, 0)
    , m_texture(0)
    , m_isSmooth(copy.isSmooth())
    , m_isRepeated(copy.isRepeated()) {
    if (copy.m_texture) {

    }
}

Texture::~Texture(void) {
    if (m_texture) {
        GL_CHECK(glDeleteTextures(1, &m_texture));
    }
}

bool Texture::loadFromFile(const std::string filename, const glm::vec2 &area) {
    GLuint texture = SOIL_load_OGL_texture(
                filename.c_str(),
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS |
                SOIL_FLAG_INVERT_Y |
                SOIL_FLAG_NTSC_SAFE_RGB |
                SOIL_FLAG_COMPRESS_TO_DXT);

}
