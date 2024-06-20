#pragma once

#include "Chunk.h"
#include "TextureManager.h"

#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexArray.h"

struct Vertex {
    float pos[3];
    float texPos[2];
};

class ChunkIndexBuffer;

class ChunkRenderer {
private:
    VertexBuffer cubeFaceVertexBuffer_;
    VertexArray cubeFaceVertexArray_;

    std::vector<Shader*> Shaders_;
    TextureManager TextureManager_;

    glm::mat4* model_;
    glm::mat4* view_;
    glm::mat4* projection_;

public:
    static Vertex CHUNK_VERTEX_POSITIONS[Utils::WORLD_HEIGHT*Utils::CHUNK_SIZE*Utils::CHUNK_SIZE*24];

    ChunkRenderer();
    ~ChunkRenderer();

    static void Init();
    static inline unsigned int GetCubeStartIndex(int x, int y, int z) {
        return (((y) * Utils::CHUNK_SIZE + x) * Utils::CHUNK_SIZE + z) * 24;
    }

    void SetViewMatrices(glm::mat4* model, glm::mat4* view, glm::mat4* projection);
    void Render(const Chunk* chunk);
};