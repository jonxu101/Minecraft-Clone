#pragma once

#include "Block.h"
#include "Chunk.h"
#include "Player.h"

#include "ChunkRenderer.h"
#include "GameRenderer.h"

#include "Graphics/Texture.h"

#include <string>
#include <vector>

class Game {
private:
    GameRenderer GameRenderer_;
    ChunkRenderer ChunkRenderer_;

    uint16_t renderDistance_;
    std::vector<std::vector<Chunk>> chunkCache_;

    Player Player_;

    glm::mat4 modelMat_;
    glm::mat4 projectionMat_;

public:
    Game();
    ~Game();

    void Render();
    int Run(GLFWwindow* window);
};