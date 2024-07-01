#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderSource {
    std::string vertex;
    std::string fragment;
};


class Shader {
private:
    std::string filepath_;
    unsigned int rendererId_;
    std::unordered_map<std::string, int> UniformLocationCache_;

public:
    Shader();
    Shader(const std::string& path);

    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1i(const std::string& name, int v);
    
    void SetUniform1f(const std::string& name, float v);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform4fv(const std::string& name, unsigned int count, const float* data);
    void SetUniformMatrix4fv(const std::string& name, unsigned int count, glm::mat4 matrix);

private:
    ShaderSource ParseShaders(const std::string& path);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(const std::string& source, unsigned int type);
    
    int GetUniformLocation(const std::string& name);
};