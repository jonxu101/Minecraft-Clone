#include "Graphics/Renderer.h"
#include "Graphics/VertexBuffer.h"

VertexBuffer::VertexBuffer() {

}

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    std::cout << "VertexBuffer: begin initing" << std::endl;
    GLCall(glGenBuffers(1, &rendererId_));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId_));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    std::cout << "VertexBuffer: Done initing" << std::endl;
}

VertexBuffer::~VertexBuffer(){
    GLCall(glDeleteBuffers(1, &rendererId_));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId_));
}

void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
