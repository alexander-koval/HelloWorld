#include <icebird/Graphics/Shader.hpp>
#include <fstream>
#include <iostream>

Shader::Shader(void)
    : m_totalShaders(0) {
    m_shaders[VERTEX] = 0;
    m_shaders[GEOMETRY] = 0;
    m_shaders[FRAGMENT] = 0;
    m_attributes.clear();
    m_uniforms.clear();
}

Shader::~Shader() {
    m_attributes.clear();
    m_uniforms.clear();
}

void Shader::deleteShaderProgram(void) {
    glDeleteProgram(m_program);
}

void Shader::loadFromMemory(const std::string &shader, Type type) {
    GLuint shader_id = 0;
    if (VERTEX == type) shader_id = glCreateShader(GL_VERTEX_SHADER);
    if (FRAGMENT == type) shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    if (GEOMETRY == type) shader_id = glCreateShader(GL_GEOMETRY_SHADER);
    const char* tmp = shader.c_str();
    glShaderSource(shader_id, 1, &tmp, 0);

    GLint status = 0;
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
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
        glAttachShader(m_program, m_shaders[VERTEX]);
    }
    if (m_shaders[FRAGMENT] != 0) {
        glAttachShader(m_program, m_shaders[FRAGMENT]);
    }
    if (m_shaders[GEOMETRY] != 0) {
        glAttachShader(m_program, m_shaders[GEOMETRY]);
    }
    GLint status = 0;
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (GL_FALSE == status) {
        GLint info_log_lenght = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &info_log_lenght);
        GLchar* info_log = new GLchar[info_log_lenght];
        glGetProgramInfoLog(m_program, info_log_lenght, NULL, info_log);
        std::cerr << "Link log: " << info_log << std::endl;
        delete[] info_log;
    }
    glDeleteShader(m_shaders[VERTEX]);
    glDeleteShader(m_shaders[FRAGMENT]);
    glDeleteShader(m_shaders[GEOMETRY]);
}

void Shader::use(void) {
    glUseProgram(m_program);
}

void Shader::unUse(void) {
    glUseProgram(0);
}

void Shader::addAttribute(const std::string &attribute) {
    m_attributes[attribute] = glGetAttribLocation(m_program, attribute.c_str());
}

GLuint Shader::operator [](const std::string& attribute) {
    return m_attributes[attribute];
}

void Shader::addUniform(const std::string &uniform) {
    m_uniforms[uniform] = glGetUniformLocation(m_program, uniform.c_str());
}

GLuint Shader::operator ()(const std::string& uniform) {
    return m_uniforms[uniform];
}
