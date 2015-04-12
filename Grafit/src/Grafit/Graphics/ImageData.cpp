#include <Grafit/Graphics/Image.hpp>
#include <Grafit/Graphics/shaders/shaders.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <iostream>

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
#else
const std::string filename = "Resources/Lenna.png";
#endif

namespace gf {
BitmapData::BitmapData(void) {

}

void BitmapData::render(glm::mat4 mvpView) {
//    m_shader.use();
//    GL_CHECK(glBindVertexArray(m_vaoID));
//    m_shader.setParameter<Shader::Uniform>("MVP", mvpView);
////    GL_CHECK(glUniformMatrix4fv(m_shader.getParameterID<Shader::Uniform>("MVP"), 1, GL_FALSE, glm::value_ptr(mvpView)));
//    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
//    GL_CHECK(glBindVertexArray(0));
//    m_shader.unuse();
}

BitmapData::~BitmapData(void) {

}

bool BitmapData::loadFromFile(const std::string& filename) {
    m_pixels.clear();
    int width, height, channels;
    unsigned char* image_data = stbi_load(filename.c_str(), &width, &height, &channels, STBI_default);
    if (image_data && width && height) {
        m_size.x = width;
        m_size.y = height;
        m_channels = channels;
        m_pixels.resize(width * height * channels);
        memcpy(&m_pixels[0], image_data, m_pixels.size());
        free((void*)image_data);
        return true;
    } else {
        std::cerr << "Cannot load image: " << filename.c_str() << std::endl;
        return false;
    }
}

bool BitmapData::loadFromMemory(const void *data, std::size_t size) {
    if (data && size) {
        m_pixels.clear();
        int width, height, channels;
        const unsigned char* buffer = static_cast<const unsigned char*>(data);
        unsigned char* image_data =stbi_load_from_memory(buffer, static_cast<int>(size), &width, &height, &channels, STBI_default);
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

glm::vec2 BitmapData::getSize(void) const {
    return m_size;
}

const Uint8* BitmapData::getPixels() const {
    if (!m_pixels.empty()) {
        return &m_pixels[0];
    } else {
        std::cerr << "Trying to access the pixels of an empty image" << std::endl;
        return NULL;
    }
}

void BitmapData::flipX(void) {
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

void BitmapData::flipY(void) {
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

}
