#include <icebird/Graphics/Texture.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>
#include <icebird/Graphics/Image.hpp>
#include <iostream>
#include <SOIL.h>

Uint32 Texture::getMaximumSize(void) {
    GLint size;
    GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size));
    return static_cast<Uint32>(size);
}

Texture::Texture(void)
    : m_size(0, 0)
    , m_actualSize(0, 0)
    , m_textureID(0)
    , m_isSmooth(false)
    , m_isRepeated(false) {

}

Texture::Texture(const Texture &copy)
    : m_size(0, 0)
    , m_actualSize(0, 0)
    , m_textureID(0)
    , m_isSmooth(copy.isSmooth())
    , m_isRepeated(copy.isRepeated()) {
    if (copy.m_textureID) {

    }
}

Texture::~Texture(void) {
    if (m_textureID) {
        GLuint texture = static_cast<GLuint>(m_textureID);
        GL_CHECK(glDeleteTextures(1, &texture));
    }
}

bool Texture::initialize(Uint32 width, Uint32 height) {
    if ((width == 0) || (height == 0)) {
        std::cerr << "Failed to create texture, invalid size (" << width << "x" << height << ")" << std::endl;
        return false;
    }
    glm::vec2 actual_size(getValidSize(width), getValidSize(height));
    Uint32 max_size = getMaximumSize();
    if ((actual_size.x > max_size) || actual_size.y > max_size) {
        std::cerr << "Failed to create texture, its internal size is too high "
                  << "(" /*<< actual_size.x << "x" < actual_size.y << */", "
                  << "maximum size is " << max_size << "x" << max_size << ")"
                  << std::endl;
        return false;
    }
    m_size.x = width;
    m_size.y = height;
    m_actualSize = actual_size;

    if (!m_textureID) {
        GLuint texture;
        GL_CHECK(glGenTextures(1, &texture));
        GL_CHECK(glActiveTexture(GL_TEXTURE0));
        m_textureID = texture;
    }
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureID));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_actualSize.x, m_actualSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));

    GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    return true;
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
        if (initialize(image.getSize().x, image.getSize().y)) {
            update(image);
            return true;
        } else {
            return false;
        }
    } else {
        if (initialize(area.x, area.y)) {
            const Uint8* pixels = image.getPixels() /*+ 3 * (width * 0)*/;
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureID));
//            for (int index = 0; index < area.y; ++index) {
            GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                          width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
            GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, area.x, area.y,
                                     GL_RGB, GL_UNSIGNED_BYTE, pixels));

//                GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, index, area.x, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels));
//                pixels += 3 * width;
//            }
            return true;
        } else {

        }
    }
}

void Texture::update(const Uint8 *pixels) {
    update(pixels, m_size.x, m_size.y, 0, 0);
}

void Texture::update(const Uint8 *pixels, Uint32 width, Uint32 height, Uint32 x, Uint32 y) {
    assert(x + width <= m_size.x);
    assert(y + height <= m_size.y);
    if (pixels && m_textureID) {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureID));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels));
    }
}

void Texture::update(const Image &image) {
    update(image.getPixels(), image.getSize().x, image.getSize().y, 0, 0);
}

void Texture::update(const Image &image, Uint32 x, Uint32 y) {
    update(image.getPixels(), image.getSize().x, image.getSize().y, x, y);
}

void Texture::setSmooth(bool smooth) {
    if (smooth != m_isSmooth) {
        m_isSmooth = smooth;
        if (m_textureID) {
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureID));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));
        }
    }
}

bool Texture::isSmooth() const {
    return m_isSmooth;
}

void Texture::setRepeated(bool repeated) {
    if (repeated != m_isRepeated) {
        m_isRepeated = repeated;
        if (m_textureID) {
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureID));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
        }
    }
}

bool Texture::isRepeated() const {
    return m_isRepeated;
}

Int32 Texture::getValidSize(Int32 size) {
    if (isPowerOfTwo(size)) {
        return size;
    }
    return getPowerOfTwo(size);
}

bool Texture::isPowerOfTwo(Int32 size) {
    return (size & (size - 1)) == 0;
}

Int32 Texture::getPowerOfTwo(Int32 size) {
    --size;
    size |= (size >> 1);
    size |= (size >> 2);
    size |= (size >> 4);
    size |= (size >> 8);
    size |= (size >> 16);
    return size + 1;
}
