#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/VBO.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <cassert>

namespace gf {

Shader::Shader(void)
: m_programID(0) {
    m_attributes.clear();
    m_uniforms.clear();
}

Shader::~Shader() {
    unuse();
    relese();
    m_attributes.clear();
    m_uniforms.clear();
}

void Shader::relese(void) {
    if (m_programID != 0) {
        GL_CHECK(glDeleteProgram(m_programID));
        m_programID = 0;
    }
}

void Shader::loadFromMemory(const std::string &shader, GLenum type) {
    GLuint shader_id = 0;
    GL_CHECK(shader_id = glCreateShader(type));
    const char* tmp = shader.c_str();
    GL_CHECK(glShaderSource(shader_id, 1, &tmp, 0));

    GLint status = 0;
    GL_CHECK(glCompileShader(shader_id));
    GL_CHECK(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status));
    if (GL_FALSE == status) {
        GLint info_log_lenght;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_lenght);
        GLchar* info_log = new GLchar[info_log_lenght];
        glGetShaderInfoLog(shader_id, info_log_lenght, NULL, info_log);
        std::cerr << "Compile Log: " << info_log << std::endl;
        delete[] info_log;
    }
    GL_CHECK(glAttachShader(getProgramID(), shader_id));
    GL_CHECK(glDeleteShader(shader_id));
}

void Shader::loadFromFile(const std::string &filename, GLenum type) {
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

void Shader::link(void) {
    GLint status = 0;
    GLuint programID = getProgramID();
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glGetProgramiv(programID, GL_LINK_STATUS, &status));
    if (GL_FALSE == status) {
        char log[1024];
        GL_CHECK(glGetProgramInfoLog(programID, sizeof(log), 0, log));
        std::cerr << "Failed to link shader:" << std::endl
              << log << std::endl;
        GL_CHECK(glDeleteShader(programID));
        m_programID = 0;
    }
}

void Shader::use(void) {
    GL_CHECK(glUseProgram(getProgramID()));
}

void Shader::unuse(void) {
    GL_CHECK(glUseProgram(0));
}

const GLuint Shader::getProgramID(void) {
    if (m_programID == 0) {
        m_programID = glCreateProgram();
    }
    return m_programID;
}

GLuint Shader::getAttributeID(const std::string &attribute) const {
    std::map<std::string, Shader::Attribute>::const_iterator it = m_attributes.find(attribute);
    if (it != m_attributes.end())
        return it->second.attributeID;
    return 0;
}

GLuint Shader::getUniformID(const std::string &uniform) const {
    std::map<std::string, Shader::Uniform>::const_iterator it = m_uniforms.find(uniform);
    if (it != m_uniforms.end())
        return it->second.uniformID;
    return 0;
}

Shader::Attribute::Attribute(Shader &shader, const char *name)
    : attributeID(glGetAttribLocation(shader.getProgramID(), name)) {
    GL_CHECK(assert(attributeID >= 0));
}

void Shader::Attribute::set(const VertexBuffer& buffer, GLint size, GLenum type, GLboolean normalize, const GLvoid* offset) const {
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer.getVBO()));
    GL_CHECK(glEnableVertexAttribArray(attributeID);
    GL_CHECK(glVertexAttribPointer(attributeID, size, type, normalize, buffer.getSizePerVertex(), (const GLvoid*)offset)));
}

Shader::Uniform::Uniform(Shader &shader, const char *name)
    : uniformID(glGetUniformLocation(shader.getProgramID(), name)) {
    GL_CHECK(assert(uniformID >= 0));
}

void Shader::Uniform::set(GLint value) const {
    GL_CHECK(glUniform1i(uniformID, value));
}

void Shader::Uniform::set(GLfloat value) const {
    GL_CHECK(glUniform1f(uniformID, value));
}

void Shader::Uniform::set(GLint value1, GLint value2) const {
    GL_CHECK(glUniform2i(uniformID, value1, value2));
}

void Shader::Uniform::set(GLfloat value1, GLfloat value2) const {
    GL_CHECK(glUniform2f(uniformID, value1, value2));
}

void Shader::Uniform::set(GLint value1, GLint value2, GLint value3) const {
    GL_CHECK(glUniform3i(uniformID, value1, value2, value3));
}

void Shader::Uniform::set(GLfloat value1, GLfloat value2, GLfloat value3) const {
    GL_CHECK(glUniform3f(uniformID, value1, value2, value3));
}

void Shader::Uniform::set(GLint value1, GLint value2, GLint value3, GLint value4) const {
    GL_CHECK(glUniform4i(uniformID, value1, value2, value3, value4));
}

void Shader::Uniform::set(GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4) const {
    GL_CHECK(glUniform4f(uniformID, value1, value2, value3, value4));
}

void Shader::Uniform::set(const GLfloat *values, int numValues) const {
    GL_CHECK(glUniform1fv(uniformID, numValues, values));
}

void Shader::Uniform::setMatrix2(const GLfloat *values, GLint count, GLboolean transpose) const {
    GL_CHECK(glUniformMatrix2fv(uniformID, count, transpose, values));
}

void Shader::Uniform::setMatrix3(const GLfloat *values, GLint count, GLboolean transpose) const {
    GL_CHECK(glUniformMatrix3fv(uniformID, count, transpose, values));
}

void Shader::Uniform::setMatrix4(const GLfloat *values, GLint count, GLboolean transpose) const {
    GL_CHECK(glUniformMatrix4fv(uniformID, count, transpose, values));
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string& parameter) {
    getUniform(parameter);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string& parameter, int v1) {
    Uniform& uniform = getUniform(parameter);
    uniform.set(v1);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string& parameter, float v1) {
    Uniform& uniform = getUniform(parameter);
    uniform.set(v1);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string& parameter, float v1, float v2) {
    Uniform& uniform = getUniform(parameter);
    uniform.set(v1, v2);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string& parameter, float v1, float v2, float v3) {
    Uniform& uniform = getUniform(parameter);
    uniform.set(v1, v2, v3);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string& parameter, float v1, float v2, float v3, float v4) {
    Uniform& uniform = getUniform(parameter);
    uniform.set(v1, v2, v3, v3);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string &parameter, const glm::mat2& matrix) {
    Uniform& uniform = getUniform(parameter);
    uniform.setMatrix2(glm::value_ptr(matrix), 1, false);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string &parameter, const glm::mat3& matrix) {
    Uniform& uniform = getUniform(parameter);
    uniform.setMatrix3(glm::value_ptr(matrix), 1, false);
}

template<>
void Shader::setParameter<Shader::Uniform>(const std::string &parameter, const Mat4f& matrix) {
    Uniform& uniform = getUniform(parameter);
    uniform.setMatrix4(matrix.getMatrix(), 1, false);
}

template<>
void Shader::setParameter<Shader::Attribute>(const std::string &parameter) {
    getAttribute(parameter);
}

template<>
void Shader::setParameter<Shader::Attribute>(const std::string& parameter,
                                             const VertexBuffer& buffer,
                                             GLint size,
                                             GLenum type,
                                             GLboolean normalize,
                                             const GLvoid* offset) {
    Attribute& attribute = getAttribute(parameter);
    attribute.set(buffer, size, type, normalize, offset);
}

template<>
GLuint Shader::getParameterID<Shader::Uniform>(const std::string& parameter) {
    return getUniformID(parameter);
}

template<>
GLuint Shader::getParameterID<Shader::Attribute>(const std::string &parameter) {
    return getAttributeID(parameter);
}

Shader::Uniform& Shader::getUniform(const std::string& parameter) {
    std::map<std::string, Shader::Uniform>::iterator it = m_uniforms.find(parameter);
    if (it != m_uniforms.end()) {
        return it->second;
    }
    Uniform uniform = Uniform(*this, parameter.c_str());
    m_uniforms.insert(std::make_pair(parameter, uniform));
    return getUniform(parameter);
}

Shader::Attribute& Shader::getAttribute(const std::string &parameter) {
    std::map<std::string, Shader::Attribute>::iterator it = m_attributes.find(parameter);
    if (it != m_attributes.end()) {
        return it->second;
    }
    Attribute attribute = Attribute(*this, parameter.c_str());
    m_attributes.insert(std::make_pair(parameter, attribute));
    return getAttribute(parameter);
}

}
