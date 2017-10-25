#ifndef SHADER_H
#define SHADER_H

#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>
#include <Grafit/Graphics/Geometry/Vector3.hpp>
#include <Grafit/Graphics/Color.hpp>
#include <glm/matrix.hpp>
#include <string>
#include <map>

namespace gf {

class Texture;
class VertexBuffer;


class Shader {
public:
    static void bind(const Shader* shader);

    Shader(void);

    ~Shader(void);

    void loadFromFile(const std::string& filename, GLenum type);

    void loadFromMemory(const std::string& shader, GLenum type);

    void link(void);

    void use(void);

    void unuse(void);

    void bindTextures(void) const;

//    template<typename Type>
    void setUniform(const std::string& parameter) const;

    void setUniform(const std::string& parameter, int v1) const;

    void setUniform(const std::string& parameter, float v1) const;

    void setUniform(const std::string& parameter, float v1, float v2) const;

    void setUniform(const std::string& parameter, float v1, float v2, float v3) const;

    void setUniform(const std::string& parameter, float v1, float v2, float v3, float v4) const;

    void setUniform(const std::string& parameter, const Vector2F& vector) const;

    void setUniform(const std::string& parameter, const Vector3F& vector) const;

    void setUniform(const std::string& parameter, const ColorF& color) const;

    void setUniform(const std::string& parameter, const glm::mat2& matrix) const;

    void setUniform(const std::string& parameter, const glm::mat3& matrix) const;

    void setUniform(const std::string& parameter, const Mat4F& matrix) const;

    void setUniform(const std::string& parameter, const Texture& texture) const;

    void setAttribute(const std::string& parameter) const;

    void setAttribute(const std::string& parameter,
                      const VertexBuffer& buffer,
                      GLint size,
                      GLenum type,
                      GLboolean normalize,
                      const GLvoid* offset) const;

    template<typename ParameterType>
    GLuint getParameterID(const std::string& parameter) const;

    GLuint getProgramID(void) const;

    GLuint getUniformID(const std::string& uniform) const;

    GLuint getAttributeID(const std::string& attribute) const;

    void relese(void);

    struct Attribute {
        Attribute(const Shader& shader, const char* name);

        void set(const VertexBuffer& buffer, GLint size, GLenum type, GLboolean normalize, const GLvoid* offset) const;

        const GLuint attributeID;
    };

    struct Uniform {
        Uniform(const Shader& shader, const char* name);

        void set(GLint value) const;

        void set(GLfloat value) const;

        void set(GLint value1, GLint value2) const;

        void set(GLfloat value1, GLfloat value2) const;

        void set(GLint value1, GLint value2, GLint value3) const;

        void set(GLfloat value1, GLfloat value2, GLfloat value3) const;

        void set(GLint value1, GLint value2, GLint value3, GLint value4) const;

        void set(GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4) const;

        void set(const GLfloat* values, int numValues) const;

        void setMatrix2(const GLfloat* values, GLint count, GLboolean transpose) const;

        void setMatrix3(const GLfloat* values, GLint count, GLboolean transpose) const;

        void setMatrix4(const GLfloat* values, GLint count, GLboolean transpose) const;

        const GLint uniformID;
    };

private:
    const Uniform& getUniform(const std::string& parameter) const;
    const Attribute& getAttribute(const std::string& parameter) const;

    mutable GLuint m_programID;
    mutable std::map<const Shader::Uniform*, const Texture*> m_textures;
    mutable std::map<std::string, Shader::Uniform> m_uniforms;
    mutable std::map<std::string, Shader::Attribute> m_attributes;
};

}

#endif // SHADER_H
