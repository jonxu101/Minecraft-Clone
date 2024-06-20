#include "Graphics/Renderer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/GLUtil.h"

VertexArray::VertexArray() {
    std::cout << "VertexArray: init" << std::endl;
    GL_CHECK(glGenVertexArrays(1, &rendererId_));
}

VertexArray::~VertexArray() {
    GL_CHECK(glDeleteVertexArrays(1, &rendererId_));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned offset = 0;
    
    for (size_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GL_CHECK(glVertexAttribPointer(i, element.count, element.type, 
            element.normalized, layout.GetStride(), (const void*) offset));
        GL_CHECK(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::GetSizeOf(element.type);
    }
    

}

void VertexArray::Bind() const {
    std::cout << "Binding : " << rendererId_ << std::endl;
    GL_CHECK(glBindVertexArray(rendererId_));
}

void VertexArray::Unbind() const {
    GL_CHECK(glBindVertexArray(0));
}
