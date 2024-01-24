#pragma once
#define GLEW_STATIC

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __debugbreak()
// #define GLCall(x) GLClearError();\
//     x;\
//     ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define GLCall(x) x;

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

namespace RendererUtils {

struct BlockVertex {
    float pos[3];
    float texPos[2];
};

const BlockVertex BLOCK_CUBE_POSITIONS[] = {
    {0.0f,  1.0f,  0.0f, 0.0, 0.0}, // 0(0, 2)
    {1.0f,  1.0f,  0.0f, 1.0, 0.0},
    {0.0f,  1.0f,  1.0f, 0.0, 1.0},
    {1.0f,  1.0f,  1.0f, 1.0, 1.0}, // 3

    {0.0f,  0.0f,  0.0f, 0.0, 0.0}, // 4 (0, 1)
    {0.0f,  1.0f,  0.0f, 0.0, 1.0},
    {1.0f,  0.0f,  0.0f, 1.0, 0.0},
    {1.0f,  1.0f,  0.0f, 1.0, 1.0},
    {0.0f,  0.0f,  1.0f, 0.0, 0.0},
    {0.0f,  1.0f,  1.0f, 0.0, 1.0},
    {1.0f,  0.0f,  1.0f, 1.0, 0.0},
    {1.0f,  1.0f,  1.0f, 1.0, 1.0}, // 11

    {0.0f,  0.0f,  0.0f, 0.0, 0.0}, // 12 (1,2)
    {0.0f,  1.0f,  0.0f, 0.0, 1.0},
    {1.0f,  0.0f,  0.0f, 0.0, 0.0},
    {1.0f,  1.0f,  0.0f, 0.0, 1.0},
    {0.0f,  0.0f,  1.0f, 1.0, 0.0},
    {0.0f,  1.0f,  1.0f, 1.0, 1.0},
    {1.0f,  0.0f,  1.0f, 1.0, 0.0},
    {1.0f,  1.0f,  1.0f, 1.0, 1.0}, // 19

    {0.0f,  0.0f,  0.0f, 0.0, 0.0}, // 20 (0,2)
    {1.0f,  0.0f,  0.0f, 1.0, 0.0},
    {0.0f,  0.0f,  1.0f, 0.0, 1.0},
    {1.0f,  0.0f,  1.0f, 1.0, 1.0}
};

const unsigned int BLOCK_CUBE_TOP_INDICES[] = {
    0, 1, 3,
    0, 2, 3,
};

const unsigned int BLOCK_CUBE_BOTTOM_INDICES[] = {
    20, 21, 23,
    20, 22, 23,
};

const unsigned int BLOCK_CUBE_SIDE_INDICES[] = {
    4, 5, 7,
    4, 6, 7,

    8, 9, 11,
    8, 10, 11,

    12, 13, 17,
    12, 16, 17,

    14, 15, 19,
    14, 18, 19
};

}

class Renderer {
private:

public:
    void Draw(const IndexBuffer& ib) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, Texture& texture) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, Texture& texture, const ColorMap& colorMap, float x, float y) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, Texture& texture, Texture& overlay, const ColorMap& colorMap) const;
};