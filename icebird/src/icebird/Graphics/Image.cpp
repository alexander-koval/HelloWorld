#include <icebird/Graphics/Image.hpp>
#include <icebird/Graphics/shaders/shaders.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <SOIL.h>

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
#else
const std::string filename = "Resources/Lenna.png";
#endif

Image::Image(void) {
//    int channels = 0;
//    int texture_width = 0;
//    int texture_height = 0;
//    m_shader.loadFromMemory(positionTexture_vert, GL_VERTEX_SHADER);
//    m_shader.loadFromMemory(positionTexture_frag, GL_FRAGMENT_SHADER);
//    GL_CHECK(m_shader.link());
//    GL_CHECK(m_shader.use());
//    GL_CHECK(m_shader.setParameter<Shader::Attribute>("VertexPosition"));
//    GL_CHECK(m_shader.setParameter<Shader::Uniform>("TextureMap"));
//    GL_CHECK(m_shader.setParameter<Shader::Uniform>("MVP"));
//    GL_CHECK(glUniform1i(m_shader.getParameterID<Shader::Uniform>("TextureMap"), 0));
//    GL_CHECK(m_shader.unuse());

//    m_vertices[0].position = glm::vec2(0.0f, 0.0f);
//    m_vertices[1].position = glm::vec2(1.0f, 0.0f);
//    m_vertices[2].position = glm::vec2(1.0f, 1.0f);
//    m_vertices[3].position = glm::vec2(0.0f, 1.0f);

//    GLushort* id = &m_indices[0];
//    id[0] = 0; id[1] = 1; id[2] = 2;
//    id[3] = 0; id[4] = 2; id[5] = 3;

//    GL_CHECK(glGenVertexArrays(1, &m_vaoID));
//    GL_CHECK(glGenBuffers(1, &m_vboID[0]));
//    GL_CHECK(glGenBuffers(1, &m_vboID[1]));
//    GL_CHECK(glBindVertexArray(m_vaoID));

//    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]));
//    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices[0], GL_STATIC_DRAW));
//    GL_CHECK(glEnableVertexAttribArray(m_shader.getParameterID<Shader::Attribute>("VertexPosition")));
//    GL_CHECK(glVertexAttribPointer(m_shader.getParameterID<Shader::Attribute>("VertexPosition"), 2,  GL_FLOAT, GL_FALSE, 0, 0));

//    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboID[1]));
//    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices[0], GL_STATIC_DRAW));

//    GLubyte* data = SOIL_load_image(filename.c_str(), &texture_width, &texture_height, &channels, SOIL_LOAD_AUTO);
//    if (data == NULL) {
//        std::cerr << "Cannot load image: " << filename.c_str() << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    GL_CHECK(glGenTextures(1, &m_textureID));
//    GL_CHECK(glActiveTexture(GL_TEXTURE0));
//    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureID));
//    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
//    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
//    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
//    GL_CHECK(glBindVertexArray(0));

//    SOIL_free_image_data(data);
}

void Image::render(glm::mat4 mvpView) {
//    m_shader.use();
//    GL_CHECK(glBindVertexArray(m_vaoID));
//    m_shader.setParameter<Shader::Uniform>("MVP", mvpView);
////    GL_CHECK(glUniformMatrix4fv(m_shader.getParameterID<Shader::Uniform>("MVP"), 1, GL_FALSE, glm::value_ptr(mvpView)));
//    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
//    GL_CHECK(glBindVertexArray(0));
//    m_shader.unuse();
}

Image::~Image(void) {

}

bool Image::loadFromFile(const std::string& filename) {
    m_pixels.clear();
    int width, height, channels;
    unsigned char* image_data = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    if (image_data && width && height) {
        m_size.x = width;
        m_size.y = height;
        m_pixels.resize(width * height * 4);
        memcpy(&m_pixels[0], image_data, m_pixels.size());
        SOIL_free_image_data(image_data);
        return true;
    } else {
        std::cerr << "Cannot load image: " << filename.c_str() << std::endl;
        return false;
    }
}

bool Image::loadFromMemory(const void *data, std::size_t size) {
    if (data && size) {
        m_pixels.clear();
        int width, height, channels;
        const unsigned char* buffer = static_cast<const unsigned char*>(data);
        unsigned char* image_data = SOIL_load_image_from_memory(buffer, static_cast<int>(size), &width, &height, &channels, SOIL_LOAD_AUTO);
        if (image_data && width && height) {
            m_size.x = width;
            m_size.y = height;
            m_pixels.resize(width * height * 4);
            memcpy(&m_pixels[0], image_data, m_pixels.size());
            SOIL_free_image_data(image_data);
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

glm::vec2 Image::getSize(void) const {
    return m_size;
}

void Image::flipX(void) {
    if (!m_pixels.empty()) {
       std::size_t rowSize = m_size.x * 4;

       for (std::size_t y = 0; y < m_size.y; ++y) {
           std::vector<Uint8>::iterator left = m_pixels.begin() + y * rowSize;
           std::vector<Uint8>::iterator right = m_pixels.begin() + (y + 1) * rowSize - 4;

           for (std::size_t x = 0; x < m_size.x / 2; ++x) {
               std::swap_ranges(left, left + 4, right);

               left += 4;
               right -= 4;
           }
       }
    }
}

void Image::flipY(void) {
    if (!m_pixels.empty()) {
        std::size_t rowSize = m_size.x * 4;
        std::vector<Uint8>::iterator top = m_pixels.begin();
        std::vector<Uint8>::iterator bottom = m_pixels.end() - rowSize;

        for (std::size_t y = 0; y < m_size.y / 2; ++y) {
            std::swap_ranges(top, top + rowSize, bottom);

            top += rowSize;
            bottom -= rowSize;
        }
    }
}


