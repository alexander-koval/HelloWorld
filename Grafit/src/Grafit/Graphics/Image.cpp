#include <Grafit/Graphics/Bitmap.hpp>
#include <Grafit/System/IO/FileStream.hpp>
#include <Grafit/System/IO/IOStream.hpp>
#include <Grafit/System/Assert.hpp>
#include <Grafit/System/File.hpp>
#include <stb_image.h>
#include <iostream>

namespace gf {

Image::Image(void) {

}

Image::~Image(void) {

}

bool Image::create(const File &file) {
    if (file.isExist() && file.isRegularFile()) {
        gf::FileStream stream;
        stream.open(file);
        return create(stream);
    }
    return false;
}

bool Image::create(gf::IOStream &stream) {
    const Uint8* buffer = reinterpret_cast<const Uint8*>(stream.read());
    return create(buffer, stream.getSize());
}

bool Image::create(const Uint8* buffer, std::size_t size) {
    if (buffer && size) {
        m_pixels.clear();
        int width, height, channels;
        unsigned char* image_data = stbi_load_from_memory(buffer, static_cast<int>(size),
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
}

Vector2U Image::getSize(void) const {
    return m_size;
}

const Uint8* Image::getPixels() const {
    if (!m_pixels.empty()) {
        return &m_pixels[0];
    } else {
        std::cerr << "Trying to access the pixels of an empty image" << std::endl;
        return nullptr;
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
