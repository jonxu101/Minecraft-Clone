#include "Game/GameRenderer.h"

struct Vertex {
    float pos[3];
    float texPos[2];
    float texInd;
};

const int NUM_VERTICES = 24;

constexpr Vertex positions[NUM_VERTICES] = {
    {0.0f,  1.0f,  0.0f, 0.0, 0.0, 0.0}, // 0(0, 2)
    {1.0f,  1.0f,  0.0f, 1.0, 0.0, 0.0},
    {0.0f,  1.0f,  1.0f, 0.0, 1.0, 0.0},
    {1.0f,  1.0f,  1.0f, 1.0, 1.0, 0.0}, // 3

    {0.0f,  0.0f,  0.0f, 0.0, 0.0, 0.0}, // 4 (0, 1)
    {0.0f,  1.0f,  0.0f, 0.0, 1.0, 0.0},
    {1.0f,  0.0f,  0.0f, 1.0, 0.0, 0.0},
    {1.0f,  1.0f,  0.0f, 1.0, 1.0, 0.0},
    {0.0f,  0.0f,  1.0f, 0.0, 0.0, 0.0},
    {0.0f,  1.0f,  1.0f, 0.0, 1.0, 0.0},
    {1.0f,  0.0f,  1.0f, 1.0, 0.0, 0.0},
    {1.0f,  1.0f,  1.0f, 1.0, 1.0, 0.0}, // 11

    {0.0f,  0.0f,  0.0f, 0.0, 0.0, 0.0}, // 12 (1,2)
    {0.0f,  1.0f,  0.0f, 0.0, 1.0, 0.0},
    {1.0f,  0.0f,  0.0f, 0.0, 0.0, 0.0},
    {1.0f,  1.0f,  0.0f, 0.0, 1.0, 0.0},
    {0.0f,  0.0f,  1.0f, 1.0, 0.0, 0.0},
    {0.0f,  1.0f,  1.0f, 1.0, 1.0, 0.0},
    {1.0f,  0.0f,  1.0f, 1.0, 0.0, 0.0},
    {1.0f,  1.0f,  1.0f, 1.0, 1.0, 0.0}, // 19

    {0.0f,  0.0f,  0.0f, 0.0, 0.0, 0.0}, // 20 (0,2)
    {1.0f,  0.0f,  0.0f, 1.0, 0.0, 0.0},
    {0.0f,  0.0f,  1.0f, 0.0, 1.0, 0.0},
    {1.0f,  0.0f,  1.0f, 1.0, 1.0, 0.0}
};

const unsigned int top_indices[] = {
    0, 1, 3,
    0, 2, 3,
};
const unsigned int bottom_indices[] = {
    20, 21, 23,
    20, 22, 23,
};
const unsigned int side_indices1[] = {
    4, 5, 7,
    4, 6, 7,
};
const unsigned int side_indices2[] = {
    8, 9, 11,
    8, 10, 11,
};
const unsigned int side_indices3[] = {
    12, 13, 17,
    12, 16, 17,
};
const unsigned int side_indices4[] = {
    14, 15, 19,
    14, 18, 19
};

Vertex* cubeVertexBuffer;

class ShaderManager {
    
};

void constructCubeVertexBuffer(int numTextures) {
    cubeVertexBuffer = (Vertex*) malloc(sizeof(Vertex) * NUM_VERTICES * numTextures);

    int vertex = 0;
    for (int tex = 0; tex < numTextures; tex++) {
        for (int i = 0; i < NUM_VERTICES; i++) {
            cubeVertexBuffer[vertex] = positions[i];
            cubeVertexBuffer[vertex].texInd = (float) tex;
            vertex++;
        }
    }
}

GameRenderer::GameRenderer() : 
    numTextures_(0),
    TextureManager_(numTextures_),
    cubeIndexBuffers_{
        new IndexBuffer(top_indices, 6),
        new IndexBuffer(bottom_indices, 6),
        new IndexBuffer(side_indices1, 6),
        new IndexBuffer(side_indices2, 6),
        new IndexBuffer(side_indices3, 6),
        new IndexBuffer(side_indices4, 6) }
{
    constructCubeVertexBuffer(numTextures_);

    cubeVertexBuffer_ = VertexBuffer(positions, numTextures_ * NUM_VERTICES * sizeof(Vertex)),
    std::cout << "GameRenderer: init" << std::endl;
    VertexBufferLayout layout;
    layout.Push<float>(3); // x,y,z
    layout.Push<float>(2); // texture
    layout.Push<float>(1); // texture index

    cubeVertexArray_.AddBuffer(cubeVertexBuffer_, layout);
    cubeVertexArray_.Bind();

    CubeShader::GenShader(numTextures_);
    cubeShader_ = CubeShader();
    cubeShader_.Bind();
}

GameRenderer::~GameRenderer() {
    free(cubeVertexBuffer);
}

void GameRenderer::SetViewMatrices(glm::mat4* model, glm::mat4* view, glm::mat4* projection) {
    model_ = model;
    view_ = view;
    projection_ = projection;
}

#include <glm/gtx/io.hpp>

void GameRenderer::RenderBegin() {
    cubeShader_.Bind();
    cubeShader_.SetUniformMatrix4fv("model", 1, *model_);
    cubeShader_.SetUniformMatrix4fv("projection", 1, *projection_);
    cubeShader_.SetUniformMatrix4fv("view", 1, *view_);
}

// void GameRenderer::BindFace(uint16_t face) {
//     const IndexBuffer& ib = cubeIndexBuffers_[face];
//     ib.Bind();
// }

void GameRenderer::RenderFace(const Block& block, uint16_t face) {
    cubeShader_.Bind();
    
    int texture = TextureManager_.BindBlockTexture(block.type, face);
    cubeShader_.SetUniform1i("u_Texture", texture);
    cubeShader_.SetUniform3f("blockOffset", block.pos.x, block.pos.y, block.pos.z);
    cubeIndexBuffers_[face]->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}