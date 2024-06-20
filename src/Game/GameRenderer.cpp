#include "Game/GameRenderer.h"

GameRenderer::GameRenderer() : 
    Shaders_{
        new Shader("../resources/shaders/basic.shader"),
        new Shader("../resources/shaders/side_grass.shader")},
    TextureManager_()
{
    std::cout << "GameRenderer: init" << std::endl;
    
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
    // cubeIndexBuffers_[face]->Bind();
    
    // std::cout << "GameRenderer: binding texture " << texture <<" for type: " << block.type << std::endl;
    // shader.SetUniform1i("u_Texture", texture);

    // std::cout << "GameRenderer: binding va" << std::endl;
    // cubeVertexArray_.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    // std::cout << "GameRenderer: complmete" << std::endl;
}