#pragma once

#include "Block.h"
#include "Chunk.h"
#include "Player.h"
#include "GameRenderer.h"

#include "Graphics/Texture.h"

#include <string>
#include <vector>
#include <optional>

class Game {
private:
    GameRenderer GameRenderer_;

    uint16_t renderDistance_;
    std::vector<std::vector<Chunk>> chunkCache_;

    Player Player_;

    glm::mat4 modelMat_;
    glm::mat4 projectionMat_;

public:
    Game();
    ~Game();

    int Run(GLFWwindow* window);

private:
    void render();
    void tick();

    void handlePlayerDestroy(Block* block);
    Block* raytraceClosest();
};