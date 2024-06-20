#pragma once

#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

#include "Block.h"
#include "TextureManager.h"

class GameRenderer {
private:
    std::vector<Shader*> Shaders_;
    TextureManager TextureManager_;

    // VertexBuffer cubeVertexBuffer_;
    // std::vector<IndexBuffer*> cubeIndexBuffers_;

    // VertexArray cubeVertexArray_;

    glm::mat4* model_;
    glm::mat4* view_;
    glm::mat4* projection_;

public:
    GameRenderer();
    ~GameRenderer();

    void SetViewMatrices(glm::mat4* model_, glm::mat4* view, glm::mat4* projection);
    
    // void RenderChunk();
    void RenderBegin();
    void BindFace(uint16_t face);
    void RenderFace(const Block& block, uint16_t face);
};