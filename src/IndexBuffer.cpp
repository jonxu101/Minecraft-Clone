#include "Graphics/Renderer.h"
#include "Graphics/IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
    : count_(count) {
    std::cout << "IndexBuffer: init" << std::endl;
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    
    GLCall(glGenBuffers(1, &rendererId_));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    std::cout << "IndexBuffer: init done" << std::endl;
}

IndexBuffer::~IndexBuffer(){
    GLCall(glDeleteBuffers(1, &rendererId_));
}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_));
}

void IndexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetCount() const {
    return count_;
}