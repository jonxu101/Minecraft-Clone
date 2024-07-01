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

const int RESOLUTION_X = 1920;
const int RESOLUTION_Y = 1080;

Game::Game() : 
    GameRenderer_(),
    renderDistance_(1),
    Player_(),
    chunkCache_(renderDistance_, std::vector<Chunk>(renderDistance_, Chunk())) 
{
    modelMat_ = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    projectionMat_ = glm::perspective(glm::radians(75.0f), 640.0f / 480.0f, 0.1f, 100.0f);
    
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

void Game::Render() {
    GameRenderer_.RenderBegin();

    for (const auto& row: chunkCache_) {
        for (const auto& chunk: row) {
            chunk.Render(GameRenderer_);
        }
    }
}

using n_time = std::chrono::high_resolution_clock;

struct Vertex {
    float pos[3];
    float texPos[2];
};


int Game::Run(GLFWwindow* window) {
    std::cout << "Running game!" << std::endl;

    // glBlendFuncSeparate(G:+)
    // float positions[] = { //without texture
    //     -0.5f, -0.5f, -0.5f, 1.0, 0.0, 0.0,
    //     -0.5f,  0.5f, -0.5f, 1.0, 0.0, 0.0,
    //      0.5f, -0.5f, -0.5f, 1.0, 0.0, 0.0,
    //      0.5f,  0.5f, -0.5f, 1.0, 0.0, 0.0,
    //     -0.5f, -0.5f,  0.5f, 1.0, 0.0, 0.0,
    //     -0.5f,  0.5f,  0.5f, 1.0, 0.0, 0.0,
    //      0.5f, -0.5f,  0.5f, 1.0, 0.0, 0.0,
    //      0.5f,  0.5f,  0.5f, 1.0, 0.0, 0.0,

    //     -0.5f, -0.5f, -0.5f, 0.0, 1.0, 0.0,
    //     -0.5f,  0.5f, -0.5f, 0.0, 1.0, 0.0,
    //      0.5f, -0.5f, -0.5f, 0.0, 1.0, 0.0,
    //      0.5f,  0.5f, -0.5f, 0.0, 1.0, 0.0,
    //     -0.5f, -0.5f,  0.5f, 0.0, 1.0, 0.0,
    //     -0.5f,  0.5f,  0.5f, 0.0, 1.0, 0.0,
    //      0.5f, -0.5f,  0.5f, 0.0, 1.0, 0.0,
    //      0.5f,  0.5f,  0.5f, 0.0, 1.0, 0.0,

    //     -0.5f, -0.5f, -0.5f, 0.0, 0.0, 1.0,
    //     -0.5f,  0.5f, -0.5f, 0.0, 0.0, 1.0,
    //      0.5f, -0.5f, -0.5f, 0.0, 0.0, 1.0,
    //      0.5f,  0.5f, -0.5f, 0.0, 0.0, 1.0,
    //     -0.5f, -0.5f,  0.5f, 0.0, 0.0, 1.0,
    //     -0.5f,  0.5f,  0.5f, 0.0, 0.0, 1.0,
    //      0.5f, -0.5f,  0.5f, 0.0, 0.0, 1.0,
    //      0.5f,  0.5f,  0.5f, 0.0, 0.0, 1.0,
    // };

    // constexpr unsigned int offset = 8;
    // unsigned int indices[] = {
    //     offset * 2 + 0, offset * 2 + 1, offset * 2 + 3, // bottom
    //     offset * 2 + 3, offset * 2 + 2, offset * 2 + 0,
        
    //     offset * 2 + 4, offset * 2 + 5, offset * 2 + 7, // top
    //     offset * 2 + 7, offset * 2 + 6, offset * 2 + 4,

    //     0, 1, 5,
    //     0, 4, 5,

    //     2, 3, 7,
    //     2, 6, 7,

    //     offset * 1 + 0, offset * 1 + 2, offset * 1 + 6,
    //     offset * 1 + 0, offset * 1 + 4, offset * 1 + 6,

    //     offset * 1 + 1, offset * 1 + 3, offset * 1 + 7,
    //     offset * 1 + 1, offset * 1 + 5, offset * 1 + 7,

    // };

    // {Vertex positions[] = {
    //      {0.0f,  1.0f,  0.0f, 0.0, 0.0}, // 0(0, 2)
    //      {1.0f,  1.0f,  0.0f, 1.0, 0.0},
    //      {0.0f,  1.0f,  1.0f, 0.0, 1.0},
    //      {1.0f,  1.0f,  1.0f, 1.0, 1.0}, // 3

    //      {0.0f,  0.0f,  0.0f, 0.0, 0.0}, // 4 (0, 1)
    //      {0.0f,  1.0f,  0.0f, 0.0, 1.0},
    //      {1.0f,  0.0f,  0.0f, 1.0, 0.0},
    //      {1.0f,  1.0f,  0.0f, 1.0, 1.0},
    //      {0.0f,  0.0f,  1.0f, 0.0, 0.0},
    //      {0.0f,  1.0f,  1.0f, 0.0, 1.0},
    //      {1.0f,  0.0f,  1.0f, 1.0, 0.0},
    //      {1.0f,  1.0f,  1.0f, 1.0, 1.0}, // 11

    //      {0.0f,  0.0f,  0.0f, 0.0, 0.0}, // 12 (1,2)
    //      {0.0f,  1.0f,  0.0f, 0.0, 1.0},
    //      {1.0f,  0.0f,  0.0f, 0.0, 0.0},
    //      {1.0f,  1.0f,  0.0f, 0.0, 1.0},
    //      {0.0f,  0.0f,  1.0f, 1.0, 0.0},
    //      {0.0f,  1.0f,  1.0f, 1.0, 1.0},
    //      {1.0f,  0.0f,  1.0f, 1.0, 0.0},
    //      {1.0f,  1.0f,  1.0f, 1.0, 1.0}, // 19

    //      {0.0f,  0.0f,  0.0f, 0.0, 0.0}, // 20 (0,2)
    //      {1.0f,  0.0f,  0.0f, 1.0, 0.0},
    //      {0.0f,  0.0f,  1.0f, 0.0, 1.0},
    //      {1.0f,  0.0f,  1.0f, 1.0, 1.0}
    // };

    // unsigned int top_indices[] = {
    //     0, 1, 3,
    //     0, 2, 3,
    // };
    
    // unsigned int bottom_indices[] = {
    //     20, 21, 23,
    //     20, 22, 23,
    // };

    // unsigned int side_indices[] = {
    //     4, 5, 7,
    //     4, 6, 7,

    //     8, 9, 11,
    //     8, 10, 11,

    //     12, 13, 17,
    //     12, 16, 17,

    //     14, 15, 19,
    //     14, 18, 19
    // };

// constexpr unsigned int top_indices[] = {
//     0, 1, 3,
//     0, 2, 3,
// };

// constexpr unsigned int bottom_indices[] = {
//     20, 21, 23,
//     20, 22, 23,
// };

// constexpr unsigned int side_indices1[] = {
//     4, 5, 7,
//     4, 6, 7,
// };
// constexpr unsigned int side_indices2[] = {
//     8, 9, 11,
//     8, 10, 11,
// };
// constexpr unsigned int side_indices3[] = {
//     12, 13, 17,
//     12, 16, 17,
// };
// constexpr unsigned int side_indices4[] = {
//     14, 15, 19,
//     14, 18, 19
// };

//     VertexArray va;
//     // VertexBuffer vb(positions, 8 * 6 * 3 * sizeof(float));
//     VertexBuffer vb(positions, 24 * sizeof(Vertex));
//     // vb.Bind();

//     VertexBufferLayout layout;
//     layout.Push<float>(3);
//     layout.Push<float>(2);
//     // layout.Push<unsigned int>(1);
//     // layout.Push<unsigned int>(1);
<<<<<<< HEAD:src/Game.cpp
//     va.AddBuffer(vb, layout);
=======
//     va.AddBuffer(&vb, layout);
>>>>>>> test:src/Game/Game.cpp

//     IndexBuffer ib_top(top_indices, 6);
//     IndexBuffer ib_bottom(bottom_indices, 6);
//     IndexBuffer ib_side1(side_indices1, 6);
//     IndexBuffer ib_side2(side_indices2, 6);
//     IndexBuffer ib_side3(side_indices3, 6);
//     IndexBuffer ib_side4(side_indices4, 6);
//     // ib.Bind();
    
<<<<<<< HEAD:src/Game.cpp
//     Shader shader("../resources/shaders/basic.shader");
//     shader.Bind();
//     shader.Unbind();

//     Shader side_grass_shader("../resources/shaders/side_grass.shader");
//     side_grass_shader.Bind();
//     side_grass_shader.Unbind();
=======
//     // Shader shader("../resources/shaders/basic.shader");
//     // shader.Bind();
//     // shader.Unbind();

//     // Shader side_grass_shader("../resources/shaders/side_grass.shader");
//     // side_grass_shader.Bind();
//     // side_grass_shader.Unbind();
>>>>>>> test:src/Game/Game.cpp
//     // shader.SetUniform4f("u_Color", 0.2f, 0.2f, 0.8f, 1.0f);

//     // va.Unbind();
//     // vb.Unbind();
//     // ib_top.Unbind();
//     // ib_bottom.Unbind();
//     // ib_side.Unbind();
    
//     float r = 0.0f;
//     float incr = 0.0005f;

//     Renderer renderer;

//     float colors[12] = {
//         1.0, 0.0, 0.0, 1.0,
//         0.0, 1.0, 0.0, 1.0,
//         0.0, 0.0, 1.0, 1.0,
//     };

    // Player player;

    // glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
  	// 	   glm::vec3(0.0f, 0.0f, 0.0f), 
  	// 	   glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(75.0f), 640.0f / 480.0f, 0.1f, 100.0f);

    n_time::time_point prev = n_time::now();

    // Texture topTexture("../resources/textures/grass_block_top.png", 123);
    // Texture sideTexture("../resources/textures/grass_block_side.png", 123);
    // Texture sideOverlayTexture("../resources/textures/grass_block_side_overlay.png", 123);
    // Texture bottomTexture("../resources/textures/dirt.png", 123);

    // ColorMap grassColorMap("../resources/textures/colormap/grass.png");

    // topTexture.Bind(0);
    // sideTexture.Bind(1);
    // bottomTexture.Bind(2);
    // sideOverlayTexture.Bind(3);

    // glm::mat4 defaultColor{ 1.0, 0.0, 0.0, 0.0,
    //                         0.0, 1.0, 0.0, 0.0,
    //                         0.0, 0.0, 1.0, 0.0,
    //                         0.0, 0.0, 0.0, 1.0};;
    // float x = 0.8;
    // float y = 0.4;

    glfwSetKeyCallback(window, Input::getKeys);
    glfwSetCursorPosCallback(window, Input::getMouse);

    /* Loop until the user closes the window */
    // while (true)
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Player_.Update(n_time::now());
        Render();
        // model = glm::rotate(model, std::abs(incr), glm::vec3(0.5f, 1.0f, 0.0f));

        // view = Player_.view();
        // int i = 0;
        // int j = 0;
        // int k = 0;
        // for (int k = 0; k < 12; k++){
        // for (int i = 0; i < 16; i++) {
            // for (int j = 0; j < 16; j++) {

        // shader.Bind();
        // // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
  		// //    glm::vec3(0.0f, 0.0f, 0.0f),
  		// //    glm::vec3(0.0f, 1.0f, 0.0f));

        // // shader.SetUniform4fv("facesColor", 3, colors);
        // shader.SetUniform3f("blockOffset", (float) i, (float) k, (float) j);
        // shader.SetUniformMatrix4fv("model", 1, model);
        // shader.SetUniformMatrix4fv("projection", 1, projection);
        // shader.SetUniformMatrix4fv("view", 1, view);
        // shader.SetUniformMatrix4fv("blockOffset", 1, view);

        // // shader.SetUniform4f("u_Color", r, 0.2f, 0.8f, 1.0f);

        // // DRAW TOP
        // shader.SetUniform1i("u_Texture", 0);
        // renderer.Draw(va, ib_top, shader);

        // // DRAW BOTTOM
        // shader.SetUniform1i("u_Texture", 2);
        // renderer.Draw(va, ib_bottom, shader);
        // shader.Unbind();

        // //DRAW SIDE
        // side_grass_shader.Bind();
        // side_grass_shader.SetUniform3f("blockOffset", (float) i, (float) k, (float) j);
        // side_grass_shader.SetUniformMatrix4fv("model", 1, model);
        // side_grass_shader.SetUniformMatrix4fv("projection", 1, projection);
        // side_grass_shader.SetUniformMatrix4fv("view", 1, view);

        // side_grass_shader.SetUniform1i("u_TextureDirt", 2);
        // side_grass_shader.SetUniform1i("u_TextureGrass", 3);
        // side_grass_shader.SetUniformMatrix4fv("u_ColorMatrix", 1, grassColorMap.getPixelMat((float)1.0 - x, (float)1.0 - x * y));

        // renderer.Draw(va, ib_side1, side_grass_shader);
        

        // renderer.Draw(va, ib_side2, side_grass_shader);

        // renderer.Draw(va, ib_side3, side_grass_shader);
        // renderer.Draw(va, ib_side4, side_grass_shader);
        // side_grass_shader.Unbind();
        // vb.Bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        //     }
        // }
        // }
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}