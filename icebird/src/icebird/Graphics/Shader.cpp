#include <icebird/Graphics/Shader.hpp>
#include <fstream>
#include <iostream>

Shader::Shader(void)
    : m_totalShaders(0)
    , m_shaders(0)
    , m_attributes(0)
    , m_uniforms(0) {

}

Shader::~Shader() {
    m_attributes.clear();
    m_uniforms.clear();
}

void Shader::deleteShaderProgram(void) {
    glDeleteProgram(m_program);
}

void Shader::loadFromMemory(const std::string &shader, Type type) {
    GLuint shader_id = glCreateShader(type);
    const char* tmp = shader.c_str();
    glShaderSource(shader_id, 1, &tmp, NULL);

    GLint status = 0;
    glCompileShader(shader_id);
    if (GL_FALSE == status) {
        GLint info_log_lenght;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_lenght);
        GLchar* info_log = new GLchar[info_log_lenght];
        glGetShaderInfoLog(shader_id, info_log_lenght, NULL, info_log);
        std::cerr << "Compile Log: " << info_log << std::endl;
        delete[] info_log;
    }
    m_shaders[m_totalShaders++] = shader_id;
}

void Shader::loadFromFile(const std::string &filename, Type type) {
    std::ifstream stream;
    stream.open(filename.c_str(), std::ios_base::in);
    if (stream) {
        std::string line, buffer;
        while(std::getline(stream, line)) {
            buffer.append(line);
            buffer.append("\r\n");
        }
        loadFromMemory(buffer, type);
    } else {
        std::cerr << "Error loading shader: " << filename << std::endl;
    }
}

void Shader::createAndLinkProgram(void) {
    m_program = glCreateProgram();
    if (m_shaders[VERTEX] != 0) {

    }
}
