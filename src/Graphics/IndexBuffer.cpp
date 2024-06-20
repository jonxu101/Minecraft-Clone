#include "Graphics/Renderer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/GLUtil.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count, GLenum usage)
    : count_(count) {
    std::cout << "IndexBuffer: init" << std::endl;
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    
    GL_CHECK(glGenBuffers(1, &rendererId_));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage));
    std::cout << "IndexBuffer: init done " << rendererId_ << std::endl;
}

IndexBuffer::~IndexBuffer(){
    GL_CHECK(glDeleteBuffers(1, &rendererId_));
}

void IndexBuffer::Bind() const {
    std::cout << "Binding Index Buffer: " << rendererId_ << std::endl;
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_));
}

void IndexBuffer::Unbind() const {
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetCount() const {
    return count_;
}