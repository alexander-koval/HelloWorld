#ifndef SHADER_H
#define SHADER_H

#include <icebird/Graphics/GL/OpenGL.hpp>
#include <string>
#include <map>

class Shader
{
public:
    enum Type {
        VERTEX,
        GEOMETRY,
        FRAGMENT
    };

    enum ParameterType {
        ATTRIBUTE,
        UNIFORM
    };

    Shader(void);

    ~Shader(void);

    void loadFromFile(const std::string& filename, Type type);

    void loadFromMemory(const std::string& shader, Type type);

    void createAndLinkProgram(void);

    void use(void);

    void unUse(void);

    void addParameter(const std::string& parameter, ParameterType type);

    void addAttribute(const std::string& attribute);

    void addUniform(const std::string& uniform);

    GLuint getParameter(const std::string& parameter, ParameterType type);

    GLuint operator[] (const std::string& attribute);

    GLuint operator() (const std::string& uniform);

    void deleteShaderProgram(void);

private:
    GLuint m_program;
    int m_totalShaders;
    GLuint m_shaders[3];
    std::map<std::string, GLuint> m_attributes;
    std::map<std::string, GLuint> m_uniforms;
};

#endif // SHADER_H
