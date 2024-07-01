#include "Game/GameRenderer.h"

struct Vertex {
    float pos[3];
    float texPos[2];
};

const int NUM_VERTICES = 24;

constexpr Vertex positions[NUM_VERTICES] = {
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

Vertex* vertices_buffer;

unsigned int indices_buffer[Utils::BlockType::SIZE][36];

class ShaderManager {
    
};

void constructCubeVertexBuffer(int numTextures) {
    vertices_buffer = (Vertex*) malloc(sizeof(Vertex) * NUM_VERTICES * numTextures);

    int vertex = 0;
    for (int tex = 0; tex < numTextures; tex++) {
        for (int i = 0; i < NUM_VERTICES; i++) {
            vertices_buffer[vertex] = positions[i];
            vertices_buffer[vertex].texPos[0] = positions[i].texPos[0];
            float newCoord = 1.0 - (positions[i].texPos[1] + (float) tex) / (float) numTextures;
            vertices_buffer[vertex].texPos[1] = newCoord;
            vertex++;
        }
    }
}

void constructIndexBuffer(TextureManager* textureManager) {
    std::cout << "Init cubeindexbuffer" << std::endl;
    for (int type = 1; type < 4; type++) {
        for (int i = 0; i < 6; i++) {
            indices_buffer[type][i] = top_indices[i] + 24 * textureManager->BindBlockTexture(static_cast<Utils::BlockType>(type), 0);
            indices_buffer[type][6 + i] = bottom_indices[i] + 24 * textureManager->BindBlockTexture(static_cast<Utils::BlockType>(type), 1);
            indices_buffer[type][12 + i] = side_indices1[i] + 24 * textureManager->BindBlockTexture(static_cast<Utils::BlockType>(type), 2);
            indices_buffer[type][18 + i] = side_indices2[i] + 24 * textureManager->BindBlockTexture(static_cast<Utils::BlockType>(type), 3);
            indices_buffer[type][24 + i] = side_indices3[i] + 24 * textureManager->BindBlockTexture(static_cast<Utils::BlockType>(type), 4);
            indices_buffer[type][30 + i] = side_indices4[i] + 24 * textureManager->BindBlockTexture(static_cast<Utils::BlockType>(type), 5);
        }
    }
}

GameRenderer::GameRenderer() : 
    numTextures_(0),
    TextureManager_(numTextures_),
    cubeIndexBuffers_(Utils::BlockType::SIZE, nullptr)
{
    
    std::cout << "GameRenderer: init" << std::endl;

    constructCubeVertexBuffer(numTextures_);
    
    for (int i = 0; i < 72; i++) {
        std::cout 
        << vertices_buffer[i].pos[0] << ", "
        << vertices_buffer[i].pos[1] << ", "
        << vertices_buffer[i].pos[2] << ", "
        << vertices_buffer[i].texPos[0] << ", "
        << vertices_buffer[i].texPos[1] << ", "
        << std::endl;
    }

    constructIndexBuffer(&TextureManager_);

    for (int i = 0; i < 36; i++) {
        std::cout 
        << indices_buffer[2][i] <<",";
    }

    for (int type = 1; type < 4; type++) {
        cubeIndexBuffers_[type] = new IndexBuffer(&indices_buffer[type], 36);
    }

    cubeVertexBuffer_ = new VertexBuffer(vertices_buffer, numTextures_ * NUM_VERTICES * sizeof(Vertex));
 
    VertexBufferLayout layout;
    layout.Push<float>(3); // x,y,z
    layout.Push<float>(2); // tex.x, tex.y

    // if (cubeVertexBuffer_ == nullptr) {
    //     std::cout << "wtf\n";
    // }
    cubeVertexArray_.AddBuffer(cubeVertexBuffer_, layout);
    cubeVertexArray_.Bind();

    CubeShader::GenShader(numTextures_);
    cubeShader_ = new CubeShader();
    cubeShader_->Bind();
    TextureManager_.Bind();

}

GameRenderer::~GameRenderer() {
}

void GameRenderer::SetViewMatrices(glm::mat4* model, glm::mat4* view, glm::mat4* projection) {
    model_ = model;
    view_ = view;
    projection_ = projection;
}

#include <glm/gtx/io.hpp>

void GameRenderer::RenderBegin() {
    cubeShader_->Bind();
    cubeShader_->SetUniformMatrix4fv("model", 1, *model_);
    cubeShader_->SetUniformMatrix4fv("projection", 1, *projection_);
    cubeShader_->SetUniformMatrix4fv("view", 1, *view_);
}

// void GameRenderer::BindFace(uint16_t face) {
//     const IndexBuffer& ib = cubeIndexBuffers_[face];
//     ib.Bind();
// }

void GameRenderer::RenderBlock(const Block& block) {
    if (block.type >= 4 || block.type < 1) {
        std::cout << "ERROR IN RENDERBLOCK, INVALID TYPE" << std::endl;
    }

    cubeShader_->Bind();
    
    cubeShader_->SetUniform1i("u_Texture", 1);
    cubeShader_->SetUniform3f("blockOffset", block.pos.x, block.pos.y, block.pos.z);
    cubeVertexArray_.Bind();
    TextureManager_.Bind();
    cubeIndexBuffers_[block.type]->Bind();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}