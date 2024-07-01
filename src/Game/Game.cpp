#include "Game/Game.h"

#include <string>
#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <chrono>
#include <algorithm>

#include "Graphics/IndexBuffer.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"

#include "Game/Input.h"
#include "Game/Player.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using n_time = std::chrono::high_resolution_clock;

Game::Game() : 
    GameRenderer_(),
    renderDistance_(2),
    Player_(),
    chunkCache_(renderDistance_, std::vector<Chunk>(renderDistance_, Chunk())) 
{
    modelMat_ = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    projectionMat_ = glm::perspective(glm::radians(75.0f), (float) Utils::RESOLUTION_X / Utils::RESOLUTION_Y, 0.1f, 100.0f);
    
    GameRenderer_.SetViewMatrices(&modelMat_, Player_.GetViewPtr(), &projectionMat_);
    
    for (int x = 0; x < renderDistance_; x++) {
        for (int z = 0; z < renderDistance_; z++) {
            chunkCache_[x][z] = Chunk(x,z);
        }
    }
}

Game::~Game() {

}

inline int getChunkIndex(const ChunkPos& pos, const int renderDistance) {
    return (pos.z % (2*renderDistance)) * 2 * renderDistance + pos.x % (2 * renderDistance);
}

void Game::render() {
    GameRenderer_.RenderBegin();

    for (const auto& row: chunkCache_) {
        for (const auto& chunk: row) {
            chunk.Render(GameRenderer_);
        }
    }
}

void Game::tick() {
    if (Input::left_click == 1) {
        handlePlayerDestroy(raytraceClosest());
    }
}

void Game::handlePlayerDestroy(Block* block) {
    if (!block) {
        std::cout << "What? " << std::endl;
        return;
    }
    block->type = Utils::BlockType::AIR;
}

inline float normal(float x) {
    return (x > 0) - (x < 0);
}

Block* Game::raytraceClosest() {
    glm::vec3 start = Player_.GetViewPos();
    glm::vec3 p_Ray = start;
    glm::vec3 d_Ray = Player_.GetViewDiff();

    float unit_dx = normal(d_Ray.x);
    float unit_dy = normal(d_Ray.y);
    float unit_dz = normal(d_Ray.z);

    while (p_Ray.y >= 0.0 && p_Ray.y <= static_cast<float>(Utils::WORLD_HEIGHT) && glm::distance(start, p_Ray) <= Utils::PLAYER_INTERACT_RANGE) {
        std::cout << p_Ray.x << "," << p_Ray.y << "," << p_Ray.z << std::endl;
        float jump = std::min({ ((p_Ray.x - std::ceil(p_Ray.x - unit_dx * 0.5) + unit_dx * 0.5)) / d_Ray.x,
                                ((p_Ray.y - std::ceil(p_Ray.y - unit_dy * 0.5) + unit_dy * 0.5)) / d_Ray.y,
                                ((p_Ray.z - std::ceil(p_Ray.z - unit_dz * 0.5) + unit_dz * 0.5)) / d_Ray.z});

        jump += normal(jump) * 0.001f;

        p_Ray = p_Ray + jump * d_Ray;

        std::cout << p_Ray.x << "," << p_Ray.y << "," << p_Ray.z << std::endl;

        int int_x = round(p_Ray.x);
        int int_z = round(p_Ray.z);

        int chunk_x = int_x / Utils::CHUNK_SIZE % Utils::DEFAULT_RENDER_DISTANCE;
        int chunk_z = int_z / Utils::CHUNK_SIZE % Utils::DEFAULT_RENDER_DISTANCE;
        std::cout << "Eliminating block at " << chunk_x << ", " << chunk_z << std::endl;
        std::cout << "exact coords: " << (int_x % Utils::CHUNK_SIZE) << ", " << round(p_Ray.y) << "," << (int_z % Utils::CHUNK_SIZE) << std::endl;
        Block* block = chunkCache_[chunk_x][chunk_z].GetBlock(int_x % Utils::CHUNK_SIZE, round(p_Ray.y), int_z % Utils::CHUNK_SIZE);
        if (block->type != Utils::BlockType::AIR) {
            std::cout << "return" <<std::endl;
            return block;
        }
    }
    return nullptr;
}

int Game::Run(GLFWwindow* window) {
    std::cout << "Running game!" << std::endl;
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(75.0f), 640.0f / 480.0f, 0.1f, 100.0f);

    auto prev = n_time::now();

    glfwSetKeyCallback(window, Input::GetKeys);
    glfwSetCursorPosCallback(window, Input::GetMousePos);
    glfwSetMouseButtonCallback(window, Input::GetMouseClick);

    /* Loop until the user closes the window */
    // while (true)
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto current_time = n_time::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count() 
            - std::chrono::duration_cast<std::chrono::milliseconds>(prev.time_since_epoch()).count() 
            >= Utils::MILLIS_BETWEEN_TICKS) {
                tick();
                prev = current_time;
        }

        Player_.Update(current_time);
        render();
        
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}