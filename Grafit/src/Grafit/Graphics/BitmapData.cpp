#include <Grafit/Graphics/Bitmap.hpp>
#include <Grafit/System/FileStream.hpp>
#include <Grafit/System/InputStream.hpp>
#include <Grafit/System/Assert.hpp>
#include <Grafit/System/File.hpp>
#include <stb_image.h>
#include <iostream>

namespace gf {

Image::Image(void) {

}

Image::~Image(void) {

}

bool Image::load(gf::IInputStream &stream) {
    m_pixels.clear();
    int width, height, channels;
    const Uint8* buffer = static_cast<const Uint8*>(stream.read());
    unsigned char* image_data = stbi_load_from_memory(buffer, static_cast<int>(stream.getSize()),
                                                     &width, &height, &channels, STBI_default);
    GF_ASSERT(width > 0, "Invalid image width", width);
    GF_ASSERT(height > 0, "Invalid image width", height);
    GF_ASSERT(image_data != nullptr, "Wrong image data", "");
    if (image_data && width && height) {
        m_size.x = width;
        m_size.y = height;
        m_channels = channels;
        m_pixels.resize(width * height * channels);
        memcpy(&m_pixels[0], image_data, m_pixels.size());
        free((void*)image_data);
        return true;
    }
    return false;
}

bool Image::loadFromFile(const std::string& filepath) {

    m_pixels.clear();
    int width, height, channels;
    gf::File file(filepath);
    if (file.isExist() && file.isRegularFile()) {
        gf::FileStream stream;
        stream.open(&file);
        const Uint8* buffer = static_cast<const Uint8*>(stream.read());
        unsigned char* image_data = stbi_load_from_memory(buffer, static_cast<int>(file.getSize()),
                                                         &width, &height, &channels, STBI_default);
        if (image_data && width && height) {
            m_size.x = width;
            m_size.y = height;
            m_channels = channels;
            m_pixels.resize(width * height * channels);
            memcpy(&m_pixels[0], image_data, m_pixels.size());
            free((void*)image_data);
            return true;
        } else {
            std::cerr << "Cannot load image: " << filepath.c_str() << std::endl;
            return false;
        }
    } else {
        std::cerr << "Cannot load image: " << filepath.c_str() << std::endl;
        return false;
    }
}

bool Image::loadFromMemory(const void *data, std::size_t size) {
    if (data && size) {
        m_pixels.clear();
        int width, height, channels;
        const unsigned char* buffer = static_cast<const unsigned char*>(data);
        unsigned char* image_data =stbi_load_from_memory(buffer, static_cast<int>(size),
                                                         &width, &height, &channels, STBI_default);
        if (image_data && width && height) {
            m_size.x = width;
            m_size.y = height;
            m_pixels.resize(width * height);
            memcpy(&m_pixels[0], image_data, m_pixels.size());
            free((void*)image_data);
            return true;
        } else {
            std::cerr << "Cannot load image from memory." << std::endl;
            return false;
        }
    } else {
        std::cerr << "Cannot load image from memory. Bad data." << std::endl;
        return false;
    }
}

Vector2U Image::getSize(void) const {
    return m_size;
}

const Uint8* Image::getPixels() const {
    if (!m_pixels.empty()) {
        return &m_pixels[0];
    } else {
        std::cerr << "Trying to access the pixels of an empty image" << std::endl;
        return NULL;
    }
}

Int32 Image::getNumChannels(void) const {
    return m_channels;
}

void Image::flipX(void) {
    if (!m_pixels.empty()) {
       std::size_t rowSize = m_size.x * m_channels;

       for (std::size_t y = 0; y < m_size.y; ++y) {
           std::vector<Uint8>::iterator left = m_pixels.begin() + y * rowSize;
           std::vector<Uint8>::iterator right = m_pixels.begin() + (y + 1) * rowSize - m_channels;

           for (std::size_t x = 0; x < m_size.x / 2; ++x) {
               std::swap_ranges(left, left + m_channels, right);

               left += m_channels;
               right -= m_channels;
           }
       }
    }
}

void Image::flipY(void) {
    if (!m_pixels.empty()) {
        std::size_t rowSize = m_size.x * m_channels;
        std::vector<Uint8>::iterator top = m_pixels.begin();
        std::vector<Uint8>::iterator bottom = m_pixels.end() - rowSize;

        for (std::size_t y = 0; y < m_size.y / 2; ++y) {
            std::swap_ranges(top, top + rowSize, bottom);

            top += rowSize;
            bottom -= rowSize;
        }
    }
}

bool Image::isTransparent(void) const {
    return (m_channels == STBI_grey_alpha || m_channels == STBI_rgb_alpha);
}

}
