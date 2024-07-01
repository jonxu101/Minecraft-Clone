#include "Graphics/Renderer.h"
#include "Graphics/VertexArray.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &rendererId_));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &rendererId_));
}

void VertexArray::AddBuffer(VertexBuffer* vb, const VertexBufferLayout& layout) {
    std::cout << "Addbuffer" << std::endl;
    Bind();
    vb->Bind();
    const auto& elements = layout.GetElements();
    unsigned offset = 0;
    
    for (size_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glVertexAttribPointer(i, element.count, element.type, 
            element.normalized, layout.GetStride(), (const void*) offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::GetSizeOf(element.type);
    }
    std::cout << "End Addbuffer" << std::endl;

}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(rendererId_));
}

void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}
