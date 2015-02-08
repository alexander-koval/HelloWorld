#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glm/vec2.hpp>

class Texture {
public:
    static void bind(const Texture& texture);

    static unsigned int getMaximumSize(void);

    Texture(void);

    Texture(const Texture& copy);

    ~Texture(void);

    bool loadFromFile(const std::string filename, const glm::vec2& area = glm::vec2());

    bool loadFromMemory(const void* data, std::size_t size, const glm::vec2& area = glm::vec2());

    glm::vec2 getSize(void) const;

    void setSmooth(bool smooth);

    bool isSmooth(void) const;

    void setRepeated(bool repeated);

    bool isRepeated(void) const;

    Texture& operator =(const Texture& right);

private:
    static unsigned int getValidSize(unsigned int size);

    glm::vec2 m_size;
    glm::vec2 m_actualSize;
    unsigned int m_texture;
    bool m_isSmooth;
    bool m_isRepeated;
};

#endif // TEXTURE_HPP

