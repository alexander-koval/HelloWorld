#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>
#include <icebird/System/Types.hpp>

class ImageData {
public:
    ImageData(void);

    void render(glm::mat4 mvpView);

    ~ImageData(void);

    bool loadFromFile(const std::string& filename);

    bool loadFromMemory(const void* data, std::size_t size);

    glm::vec2 getSize(void) const;

    const Uint8* getPixels() const;

    void flipX(void);

    void flipY(void);

    bool isTransparent(void) const { return false; }

private:
    struct Vertex {
        glm::vec2 position;

    };

    GLuint m_vaoID;
    GLuint m_vboID[2];
    GLuint m_textureID;
    Vertex m_vertices[4];
    GLushort m_indices[6];
    Shader m_shader;

    Int32 m_channels;
    glm::vec2 m_size;
    std::vector<Uint8> m_pixels;
};

#endif // IMAGE_HPP
