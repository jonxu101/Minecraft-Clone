#include "Game/ChunkRenderer.h"

#include "Graphics/GLUtil.h"

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

Vertex ChunkRenderer::CHUNK_VERTEX_POSITIONS[Utils::WORLD_HEIGHT*Utils::CHUNK_SIZE*Utils::CHUNK_SIZE*24];

constexpr unsigned int CHUNK_VERTEX_POSITIONS_SIZE = Utils::WORLD_HEIGHT * Utils::CHUNK_SIZE * Utils::CHUNK_SIZE * 24;

void ChunkRenderer::Init() {
    for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
        for (int y = 0; y < Utils::WORLD_HEIGHT; y++) {
            for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
                memcpy(&CHUNK_VERTEX_POSITIONS[GetCubeStartIndex(x,y,z)], positions, 24 * sizeof(Vertex));
                for (int vertex = 0; vertex < 24; vertex++) {
                    CHUNK_VERTEX_POSITIONS[GetCubeStartIndex(x,y,z) + vertex].pos[0] += x;
                    CHUNK_VERTEX_POSITIONS[GetCubeStartIndex(x,y,z) + vertex].pos[1] += y;
                    CHUNK_VERTEX_POSITIONS[GetCubeStartIndex(x,y,z) + vertex].pos[2] += z;
                }
            }
        }
    }
}

ChunkRenderer::ChunkRenderer() : 
    cubeFaceVertexBuffer_(  CHUNK_VERTEX_POSITIONS, 
                            CHUNK_VERTEX_POSITIONS_SIZE * sizeof(Vertex)),
    Shaders_{
        new Shader("../resources/shaders/basic.shader"),
        new Shader("../resources/shaders/side_grass.shader")},
    TextureManager_() {

    VertexBufferLayout layout;
    layout.Push<float>(3); // World coord
    layout.Push<float>(2); // Texture coord
    cubeFaceVertexArray_.AddBuffer(cubeFaceVertexBuffer_, layout);
    cubeFaceVertexArray_.Bind();
}

ChunkRenderer::~ChunkRenderer() {
}

void ChunkRenderer::SetViewMatrices(glm::mat4* model, glm::mat4* view, glm::mat4* projection) {
    model_ = model;
    view_ = view;
    projection_ = projection;
}

void ChunkRenderer::Render(const Chunk* chunk) {
    // std::cout << "ChunkRenderer: Rendering: \n";
    Shader* shader = Shaders_[0]; // TODO: select proper shader
    shader->Bind();
    shader->SetUniformMatrix4fv("model", 1, *model_);
    shader->SetUniformMatrix4fv("projection", 1, *projection_);
    shader->SetUniformMatrix4fv("view", 1, *view_);
    
    int texture = TextureManager_.BindBlockTexture(Utils::STONE, 0);
    std::cout << "ChunkRenderer: " << texture << "\n";
    shader->SetUniform1i("u_Texture", texture);

    cubeFaceVertexArray_.Bind();
    std::cout << chunk->ib.GetCount() << "\n";
    chunk->ib.Bind();
    GL_CHECK (glDrawElements(GL_TRIANGLES, chunk->ib.GetCount(), GL_UNSIGNED_INT, nullptr) );
}