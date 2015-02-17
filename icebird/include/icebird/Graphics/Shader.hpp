#ifndef SHADER_H
#define SHADER_H

#include <icebird/Graphics/GL/OpenGL.hpp>
#include <icebird/System/Math/Mat4.hpp>
#include <glm/matrix.hpp>
#include <string>
#include <map>

class Shader {
public:
    Shader(void);

    ~Shader(void);

    void loadFromFile(const std::string& filename, GLenum type);

    void loadFromMemory(const std::string& shader, GLenum type);

    void link(void);

    void use(void);

    void unuse(void);

    template<typename Type>
    void setParameter(const std::string& parameter);

    template<typename Type>
    void setParameter(const std::string& parameter, float v1);

    template<typename Type>
    void setParameter(const std::string& parameter, float v1, float v2);

    template<typename Type>
    void setParameter(const std::string& parameter, float v1, float v2, float v3);

    template<typename Type>
    void setParameter(const std::string& parameter, float v1, float v2, float v3, float v4);

    template<typename Type>
    void setParameter(const std::string& parameter, const glm::mat2& matrix);

    template<typename Type>
    void setParameter(const std::string& parameter, const glm::mat3& matrix);

    template<typename Type>
    void setParameter(const std::string& parameter, const Mat4f& matrix);

    template<typename ParameterType>
    GLuint getParameterID(const std::string& parameter);

    const GLuint getProgramID(void);

    GLuint getUniformID(const std::string& uniform) const;

    GLuint getAttributeID(const std::string& attribute) const;

    void relese(void);

    struct Attribute {
        Attribute(Shader& shader, const char* name);

        GLint attributeID;
    };

    struct Uniform {
        Uniform(Shader& shader, const char* name);

        void set(GLint value) const;

        void set(GLfloat value) const;

        void set(GLint value1, GLint value2) const;

        void set(GLfloat value1, GLfloat value2) const;

        void set(GLint value1, GLint value2, GLint value3) const;

        void set(GLfloat value1, GLfloat value2, GLfloat value3) const;

        void set(GLint value1, GLint value2, GLint value3, GLint value4) const;

        void set(GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4) const;

        void set(const GLfloat* values, int numValues) const;

        void setMatrix2 (const GLfloat* values, GLint count, GLboolean transpose) const;

        void setMatrix3 (const GLfloat* values, GLint count, GLboolean transpose) const;

        void setMatrix4 (const GLfloat* values, GLint count, GLboolean transpose) const;

        GLint uniformID;
    };

private:
    Uniform& getUniform(const std::string& parameter);
    Attribute& getAttribute(const std::string& parameter);

    GLuint m_programID;
    std::map<std::string, Shader::Uniform> m_uniforms;
    std::map<std::string, Shader::Attribute> m_attributes;
};

#endif // SHADER_H
