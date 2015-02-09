#include <icebird/Graphics/Texture.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>
#include <icebird/Graphics/Image.hpp>
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
    Image image;
    return image.loadFromFile(filename) && loadFromImage(image, area);
}

bool Texture::loadFromMemory(const void *data, std::size_t size, const glm::vec2 &area) {
    Image image;
    return image.loadFromMemory(data, size) && loadFromImage(image, area);
}

bool Texture::loadFromImage(const Image &image, const glm::vec2 &area) {
    int width = static_cast<int>(image.getSize().x);
    int height = static_cast<int>(image.getSize().y);

    if ((area.x == 0) || (area.y == 0)) {

    }
}
