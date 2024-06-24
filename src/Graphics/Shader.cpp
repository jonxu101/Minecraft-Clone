#include "Graphics/Shader.h"
#include "Graphics/Renderer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {

}

Shader::Shader(const std::string& path) : filepath_(path), rendererId_(0) {
    std::cout << "Shader: init" << std::endl;
    ShaderSource source = ParseShaders(path);
    rendererId_ = CreateShader(source.vertex, source.fragment);
    std::cout << "Finished initing Shader" << std::endl;
}

Shader::~Shader() {
    GLCall(glDeleteProgram(rendererId_));
}

ShaderSource Shader::ParseShaders(const std::string& path) {
    std::cout << "Shader: parsing" << std::endl;
    std::ifstream stream(path);
    std::string line;

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            } 
            continue;
        }
        ss[(int)type] << line << '\n';
    }
    std::cout << "Shader: done parsing" << std::endl;
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    std::cout << "Shader: creating" << std::endl;
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    std::cout << "Shader: done creating" << std::endl;

    return program;
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);  // TODO: handle error

    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        int length; // error length
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, NULL, message);

        std::cout << "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader." << std::endl;

        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    std::cout << "Shader: successfully compiled" << std::endl;
    return id;
}

void Shader::Bind() const {
    GLCall(glUseProgram(rendererId_));
}
void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

// Set uniforms
void Shader::SetUniform1i(const std::string& name, int v) {
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniform1f(const std::string& name, float v) {
    GLCall(glUniform1f(GetUniformLocation(name), v));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform4fv(const std::string& name, unsigned int count, const float* data) {
    GLCall(glUniform4fv(GetUniformLocation(name), count, data));
}

void Shader::SetUniformMatrix4fv(const std::string& name, unsigned int count, glm::mat4 matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrix)));
}

int Shader::GetUniformLocation(const std::string& name) {
    auto itr = UniformLocationCache_.find(name);
    if (itr != UniformLocationCache_.end()) {
        return itr->second;
    }
    
    GLCall(int location = glGetUniformLocation(rendererId_, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    }

    UniformLocationCache_.emplace(name, location);

    return location;
}