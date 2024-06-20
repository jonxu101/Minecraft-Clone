#include "Graphics/Renderer.h"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " "
            << file << ": " << line << std::endl;
            return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, Texture& texture) const {
    texture.Bind(); // default 0
    shader.Bind();
    shader.SetUniform1i("u_Texture", 0);
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, Texture& texture, const ColorMap& colorMap, float x, float y) const {
    texture.Bind();
    shader.Bind();
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniformMatrix4fv("u_ColorMatrix", 1, colorMap.getPixelMat(x, y));
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, Texture& texture, Texture& overlay, const ColorMap& colorMap) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const IndexBuffer& ib) const {
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}