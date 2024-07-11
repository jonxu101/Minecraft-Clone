#pragma once

#include "Block.h"
#include "Chunk.h"
#include "Player.h"
#include "GameRenderer.h"

#include "Graphics/Texture.h"

#include <algorithm>
#include <string>
#include <vector>

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

    void handlePlayerDestroy();
    void handlePlayerInteract();

    inline float getNext(float curr, float dir) {
        return (std::ceil(curr - 0.5) + 0.5) + (dir - 1.0) / 2;
    }

    template<int dir>
    Block* raytraceClosest() {
        glm::vec3 start = Player_.GetViewPos();
        glm::vec3 p_Ray = start;
        glm::vec3 d_Ray = Player_.GetViewDiff();
        glm::vec3 p_Block = p_Ray;

        float unit_dx = math::normal(d_Ray.x);
        float unit_dy = math::normal(d_Ray.y);
        float unit_dz = math::normal(d_Ray.z);

        while (p_Ray.y >= 0.0 && p_Ray.y <= static_cast<float>(Utils::WORLD_HEIGHT) && glm::distance(start, p_Ray) <= Utils::PLAYER_INTERACT_RANGE) {
            float jump = std::max(0.001f, 
                                    std::min({ (getNext(p_Ray.x, unit_dx) - p_Ray.x) / d_Ray.x,
                                    (getNext(p_Ray.y, unit_dy) - p_Ray.y) / d_Ray.y,
                                    (getNext(p_Ray.z, unit_dz) - p_Ray.z) / d_Ray.z}));

            p_Block = p_Ray + static_cast<float>(jump * (1.0f + 0.001f * static_cast<float>(dir))) * d_Ray;
            p_Ray = p_Ray + static_cast<float>(jump * 1.001f) * d_Ray;

            int int_x = round(p_Ray.x);
            int int_z = round(p_Ray.z);
            int int_y = round(p_Ray.y);

            int chunk_x = int_x / Utils::CHUNK_SIZE % Utils::DEFAULT_RENDER_DISTANCE;
            int chunk_z = int_z / Utils::CHUNK_SIZE % Utils::DEFAULT_RENDER_DISTANCE;

            Block* collisionBlock = chunkCache_[chunk_x][chunk_z].GetBlock(int_x % Utils::CHUNK_SIZE, int_y, int_z % Utils::CHUNK_SIZE);
            if (collisionBlock->type != Utils::BlockType::AIR) { // TODO: add collision param in block
                int_x = round(p_Block.x);
                int_z = round(p_Block.z);
                int_y = round(p_Block.y);

                chunk_x = int_x / Utils::CHUNK_SIZE % Utils::DEFAULT_RENDER_DISTANCE;
                chunk_z = int_z / Utils::CHUNK_SIZE % Utils::DEFAULT_RENDER_DISTANCE;
                return chunkCache_[chunk_x][chunk_z].GetBlock(int_x % Utils::CHUNK_SIZE, int_y, int_z % Utils::CHUNK_SIZE);
            }
        }
        return nullptr;
    }
};