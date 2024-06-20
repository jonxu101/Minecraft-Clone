#include "Game/Chunk.h"
#include "Game/Utils.h"

#include "Graphics/GLUtil.h"

const unsigned int top_indices[] = {
    0, 1, 3,
    0, 2, 3,
};
const unsigned int bottom_indices[] = {
    20, 21, 23,
    20, 22, 23,
};
const unsigned int side_indices1[] = {
    4, 5, 7,
    4, 6, 7,
};
const unsigned int side_indices2[] = {
    8, 9, 11,
    8, 10, 11,
};
const unsigned int side_indices3[] = {
    12, 13, 17,
    12, 16, 17,
};
const unsigned int side_indices4[] = {
    14, 15, 19,
    14, 18, 19
};

unsigned int ChunkIndexBuffer::CubeIndices_[6 * 6];

ChunkIndexBuffer::ChunkIndexBuffer(Chunk* owner) :
    owner_(owner),
    ib(buffer.data(), Utils::CHUNK_SIZE * Utils::CHUNK_SIZE * Utils::WORLD_HEIGHT * 6 * 6, GL_STREAM_DRAW) {
    // size(0),
}

void ChunkIndexBuffer::Init() {
    memcpy(&CubeIndices_[0], top_indices, sizeof(unsigned int) * 6);
    memcpy(&CubeIndices_[6], bottom_indices, sizeof(unsigned int) * 6);
    memcpy(&CubeIndices_[12], side_indices1, sizeof(unsigned int) * 6);
    memcpy(&CubeIndices_[18], side_indices2, sizeof(unsigned int) * 6);
    memcpy(&CubeIndices_[24], side_indices3, sizeof(unsigned int) * 6);
    memcpy(&CubeIndices_[30], side_indices4, sizeof(unsigned int) * 6);
}

#include "Game/ChunkRenderer.h"

void ChunkIndexBuffer::UpdateChunk() {
    buffer.clear();
    for (int y = 0; y < Utils::WORLD_HEIGHT; y++) {
        for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
            for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
                const Block& block = owner_->blocks[y][x][z];
                if (block.type == Utils::AIR) {
                    continue;
                }
                for (int face = 0; face < 6; face++) { // TODO: optimize to check bitmap
                    for (int vertex = 0; vertex < 6; vertex++) {
                        buffer.push_back(ChunkRenderer::GetCubeStartIndex(x,y,z) + CubeIndices_[6*face + vertex]);
                        // std::cout << "(" << x << ", "<< y <<", " << z <<"):\n";
                        // std::cout << ChunkRenderer::CHUNK_VERTEX_POSITIONS[buffer.back()].pos[0]
                        //             << ", " << ChunkRenderer::CHUNK_VERTEX_POSITIONS[buffer.back()].pos[1]
                        //             << ", " << ChunkRenderer::CHUNK_VERTEX_POSITIONS[buffer.back()].pos[2]
                        //             <<"\n";
                    }
                }
            }
        }
    }

    ib.Bind(); // update indices in gpu
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, buffer.size() * sizeof(unsigned int), buffer.data());
    ib.Unbind();
    // void *vbo;
    // GL_CHECK( vbo = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY) );
    // memcpy(vbo, buffer.data(), buffer.size() * sizeof(unsigned int));
    // GL_CHECK( glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) );
}

void ChunkIndexBuffer::Bind() const {
    ib.Bind();
}

unsigned int ChunkIndexBuffer::GetCount() const {
    return buffer.size();
}

Chunk::Chunk() : 
    pos{0,0},
    blocks(std::vector<std::vector<std::vector<Block>>>(Utils::WORLD_HEIGHT, std::vector<std::vector<Block>>(Utils::CHUNK_SIZE, std::vector<Block>(Utils::CHUNK_SIZE)))),
    ib(this)
{
    // GenerateChunk();
}

Chunk::Chunk(int x, int z) : 
    pos{x,z},
    blocks(std::vector<std::vector<std::vector<Block>>>(Utils::WORLD_HEIGHT, std::vector<std::vector<Block>>(Utils::CHUNK_SIZE, std::vector<Block>(Utils::CHUNK_SIZE)))),
    ib(this)
{
    GenerateChunk();
    ib.UpdateChunk();
}

Chunk::~Chunk() {

}

void Chunk::GenerateChunk() {
    // std::cout << "Chunkpos x: " << Utils::CHUNK_SIZE * pos.x << std::endl;
    int y = 0;
    for (y = 0; y < 1; y++) {
        for (int x = 0; x < 1; x++) {
            for (int z = 0; z < 1; z++) {
                blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::STONE);
            }
        }
    }
    // for (y = 0; y < 11; y++) {
    //     for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
    //         for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
    //             blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::STONE);
    //         }
    //     }
    // }
    // for (; y < 15; y++) {
    //     for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
    //         for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
    //             blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::DIRT);
    //         }
    //     }
    // }
    // for (; y < 16; y++) {
    //     for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
    //         for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
    //             blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::GRASS);
    //         }
    //     }
    // }
    // for (; y < Utils::WORLD_HEIGHT; y++) {
    //     for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
    //         for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
    //             blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::AIR);
    //         }
    //     }
    // }
}

// void Chunk::Render(ChunkRenderer& renderer) const {
//     for (const auto& layer: blocks) {
//         for (const auto& row: layer) {
//             for (const auto& block: row) {
//                 if (block.type == Utils::BlockType::AIR) {
//                     continue;
//                 }
//                 for (int face = 0; face < 6; face++) {
//                     renderer.Render(*this);
//                 }
//             }
//         }
//     }
// }