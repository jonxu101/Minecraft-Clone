#include "Game/GameRenderer.h"

struct Vertex {
    float pos[3];
    float texPos[2];
};

constexpr Vertex positions[] = {
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

class ShaderManager {
    
};

GameRenderer::GameRenderer() : 
    cubeVertexBuffer_(positions, 24 * sizeof(Vertex)),
    cubeIndexBuffers_{
        new IndexBuffer(top_indices, 6),
        new IndexBuffer(bottom_indices, 6),
        new IndexBuffer(side_indices1, 6),
        new IndexBuffer(side_indices2, 6),
        new IndexBuffer(side_indices3, 6),
        new IndexBuffer(side_indices4, 6) },
    Shaders_{
        new Shader("../resources/shaders/basic.shader"),
        new Shader("../resources/shaders/side_grass.shader")},
    TextureManager_()
{
    std::cout << "GameRenderer: init" << std::endl;
    VertexBufferLayout layout;
    layout.Push<float>(3); // x,y,z
    layout.Push<float>(2); // texture
    // layout.Push<float>(1); // texture index
    cubeVertexArray_.AddBuffer(cubeVertexBuffer_, layout);
    cubeVertexArray_.Bind();
    Shaders_[0]->Bind();
}

GameRenderer::~GameRenderer() {

}

void GameRenderer::SetViewMatrices(glm::mat4* model, glm::mat4* view, glm::mat4* projection) {
    model_ = model;
    view_ = view;
    projection_ = projection;
}

void GameRenderer::RenderBegin() {
    Shader* shader = Shaders_[0];
    shader->Bind();
    shader->SetUniformMatrix4fv("model", 1, *model_);
    shader->SetUniformMatrix4fv("projection", 1, *projection_);
    shader->SetUniformMatrix4fv("view", 1, *view_);
}

// void GameRenderer::BindFace(uint16_t face) {
//     const IndexBuffer& ib = cubeIndexBuffers_[face];
//     ib.Bind();
// }

void GameRenderer::RenderFace(const Block& block, uint16_t face) {
    // std::cout << "GameRenderer: binding shader" << std::endl;
    // if (block.type == Utils::BlockType::GRASS) {
    //     Shaders_[1].Bind();
    // } else {
    //     Shaders_[0].Bind();
    // }
    Shader* shader = Shaders_[0];
    // shader->Bind();
    int texture = TextureManager_.BindBlockTexture(block.type, face);
    shader->SetUniform1i("u_Texture", texture);
    shader->SetUniform3f("blockOffset", block.pos.x, block.pos.y, block.pos.z);
    // cubeVertexArray_.Bind();
    cubeIndexBuffers_[face]->Bind();
    
    // std::cout << "GameRenderer: binding texture " << texture <<" for type: " << block.type << std::endl;
    // shader.SetUniform1i("u_Texture", texture);

    // std::cout << "GameRenderer: binding va" << std::endl;
    // cubeVertexArray_.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    // std::cout << "GameRenderer: complmete" << std::endl;
}