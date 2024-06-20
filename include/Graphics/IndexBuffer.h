#pragma once

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class IndexBuffer {
private:
    unsigned int rendererId_;
    unsigned int count_;

public:
    IndexBuffer(const void* data, unsigned int count, GLenum usage = GL_STATIC_DRAW);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const;
};