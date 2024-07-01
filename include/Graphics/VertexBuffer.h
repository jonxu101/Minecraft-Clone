#pragma once

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class VertexBuffer {
private:
    unsigned int rendererId_;

public:
    VertexBuffer();
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};