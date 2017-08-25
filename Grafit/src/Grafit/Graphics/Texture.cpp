#include <Grafit/Graphics/Texture.hpp>
#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/Graphics/Bitmap.hpp>
#include <Grafit/System/File.hpp>
#include <Grafit/System/InputStream.hpp>
#include <Grafit/System/Assert.hpp>
#include <iostream>

namespace {

enum PixelFormat {
    Gray      = GL_RED,
    GrayAlpha = GL_RG,
    RGB       = GL_RGB,
    RGBA      = GL_RGBA
};

}

namespace gf {
void Texture::bind(const Texture* texture) {
    if (texture && texture->m_textureID) {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture->m_textureID));
    } else {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    }
}

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

bool Texture::create(Uint32 width, Uint32 height) {
    if ((width == 0) || (height == 0)) {
        std::cerr << "Failed to create texture, invalid size (" << width << "x" << height << ")" << std::endl;
        return false;
    }
    Vector2U actual_size(getValidSize(width), getValidSize(height));
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
        GLuint texture = 0;
        GL_CHECK(glGenTextures(1, &texture));
        m_textureID = texture;
    }
    Texture::bind(this);
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_actualSize.x, m_actualSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));

    GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    Texture::bind(nullptr);

    return true;
}

bool Texture::create(const File& file) {
    gf::Image image;
    if (image.create(file)) {
        return create(image);
    }
    return false;

}

bool Texture::create(const Image &image, const RectI& area) {
    int width = static_cast<int>(image.getSize().x);
    int height = static_cast<int>(image.getSize().y);

    if ((area.width == 0) || (area.height == 0)) {
        if (create(image.getSize().x, image.getSize().y)) {
            update(image);
            GL_CHECK(glFlush());
            return true;
        } else {
            return false;
        }
    } else {
        RectI rect = area;
        if (rect.left < 0) rect.left = 0;
        if (rect.top <  0) rect.top  = 0;
        if (rect.left + rect.width > width) rect.width = width - rect.left;
        if (rect.top + rect.height > height) rect.height = height - rect.top;
        if (create(rect.width, rect.height)) {
            const Uint8* pixels = image.getPixels();
            Texture::bind(this);
            GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                          width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
            GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rect.width, rect.height,
                                     GL_RGB, GL_UNSIGNED_BYTE, pixels));
            GL_CHECK(glFlush());
            Texture::bind(nullptr);
            return true;
        } else {
            return false;
        }
    }
}



bool Texture::create(const Uint8* buffer, std::size_t size, const RectI& area) {
    Image image;
    return image.create(buffer, size) && create(image, area);
}

void Texture::update(const Uint8 *pixels) {
    update(pixels, m_size.x, m_size.y, 0, 0);
}

void Texture::update(const Uint8 *pixels, Uint32 width, Uint32 height, Uint32 x, Uint32 y) {
    assert(x + width <= m_size.x);
    assert(y + height <= m_size.y);
    if (pixels && m_textureID) {
        Texture::bind(this);
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels));
        Texture::bind(nullptr);
    }
}

void Texture::update(const Image &image) {
    update(image.getPixels(), image.getSize().x, image.getSize().y, 0, 0);
}

void Texture::update(const Image &image, Uint32 x, Uint32 y) {
    update(image.getPixels(), image.getSize().x, image.getSize().y, x, y);
}

Vector2U Texture::getSize(void) const {
    return m_size;
}

void Texture::setSmooth(bool smooth) {
    if (smooth != m_isSmooth) {
        m_isSmooth = smooth;
        if (m_textureID) {
            Texture::bind(this);
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_isSmooth ? GL_LINEAR : GL_NEAREST));
            Texture::bind(nullptr);
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
            Texture::bind(this);
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_isRepeated ? GL_REPEAT : GL_CLAMP_TO_EDGE));
            Texture::bind(nullptr);
        }
    }
}

bool Texture::isRepeated() const {
    return m_isRepeated;
}

Uint32 Texture::getValidSize(Uint32 size) {
    if (isPowerOfTwo(size)) {
        return size;
    }
    if (GL_ARB_texture_non_power_of_two) {
        return size;
    }
    return getPowerOfTwo(size);
}

bool Texture::isPowerOfTwo(Uint32 size) {
    return (size & (size - 1)) == 0;
}

Uint32 Texture::getPowerOfTwo(Uint32 size) {
    --size;
    size |= (size >> 1);
    size |= (size >> 2);
    size |= (size >> 4);
    size |= (size >> 8);
    size |= (size >> 16);
    return size + 1;
}
}
