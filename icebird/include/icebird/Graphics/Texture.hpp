#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glm/vec2.hpp>
#include <icebird/System/Types.hpp>

class Image;
class Texture {
public:
    static void bind(const Texture& texture);

    static Uint32 getMaximumSize(void);

    Texture(void);

    Texture(const Texture& copy);

    ~Texture(void);

    bool create(Uint32 width, Uint32 height);

    bool loadFromFile(const std::string filename, const glm::vec2& area = glm::vec2());

    bool loadFromMemory(const void* data, std::size_t size, const glm::vec2& area = glm::vec2());

    bool loadFromImage(const Image& image, const glm::vec2& area);

    void update(const Uint8* pixels);

    void update(const Uint8* pixels, Uint32 width, Uint32 height, Uint32 x, Uint32 y);

    void update(const Image& image);

    void update(const Image& image, Uint32 x, Uint32 y);

    glm::vec2 getSize(void) const;

    void setSmooth(bool smooth);

    bool isSmooth(void) const;

    void setRepeated(bool repeated);

    bool isRepeated(void) const;

    Texture& operator =(const Texture& right);

private:
    static Uint32 getValidSize(unsigned int size);

    glm::vec2 m_size;
    glm::vec2 m_actualSize;
    Uint32 m_texture;
    bool m_isSmooth;
    bool m_isRepeated;
};

#endif // TEXTURE_HPP

