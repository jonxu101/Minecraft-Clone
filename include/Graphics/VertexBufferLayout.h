#pragma once

#define GLEW_STATIC

#include <iostream>

#include <vector>
#include <cassert>
#include "GL/glew.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOf(unsigned int type) {
        // std::cout << "Type: " << type << std::endl;
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        // std::cout << "Type: " << type << std::endl;
        assert(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements_;
    unsigned int stride_;

public:
    VertexBufferLayout() : stride_(0) {

    }

    template<typename T>
    void Push(unsigned int count) {
        static_assert(false);
    }

    inline const std::vector<VertexBufferElement>& GetElements() const {
        return elements_;
    }

    inline unsigned int GetStride() const {
        return stride_;
    }
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
    elements_.push_back(VertexBufferElement{GL_FLOAT, count, GL_FALSE});
    stride_ += count * VertexBufferElement::GetSizeOf(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    elements_.push_back(VertexBufferElement{GL_UNSIGNED_INT, count, GL_FALSE});
    stride_ += count * VertexBufferElement::GetSizeOf(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    elements_.push_back(VertexBufferElement{GL_UNSIGNED_BYTE, count, GL_TRUE});
    stride_ += count * VertexBufferElement::GetSizeOf(GL_UNSIGNED_BYTE);
}