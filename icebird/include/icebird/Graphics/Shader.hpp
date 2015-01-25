#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <GL/glew.h>
#include <string>

class Shader
{
public:
    enum Type {
        VERTEX,
        GEOMETRY,
        FRAGMENT
    };

    Shader(void);

    bool loadFromFile(const std::string& filename, Type type);

    bool loadFromMemory(const std::string& shader, Type type);

    void createAndLinkProgram(void);

    void use(void);

    void unUse(void);

    void AddAttribute(const std::string& attribute);

    void addUniform(const std::string& uniform);

    GLuint operator[] (const std::string& attribute);

    GLuint operator() (const std::string& uniform);

    void deleteShaderProgram(void);

    ~Shader(void);

private:
    GLuint m_program;
    int m_totalShaders;
    GLuint m_shaders[3];
    std::map<std::string, GLuint> m_attributes;
    std::map<std::string, GLuint> m_uniforms;
};

#endif // SHADER_H
