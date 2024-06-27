#pragma once

#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

#include "Block.h"
#include "CubeShader.h"
#include "TextureManager.h"

class GameRenderer {
private:
    int numTextures_;

    TextureManager TextureManager_;
    
    CubeShader* cubeShader_;
    VertexBuffer* cubeVertexBuffer_;
    std::vector<IndexBuffer*> cubeIndexBuffers_;

    VertexArray* cubeVertexArray_;

    glm::mat4* model_;
    glm::mat4* view_;
    glm::mat4* projection_;

public:
    GameRenderer();
    ~GameRenderer();

    void SetViewMatrices(glm::mat4* model_, glm::mat4* view, glm::mat4* projection);
    
    void RenderBegin();
    void BindFace(uint16_t face);
    void RenderBlock(const Block& block);
};