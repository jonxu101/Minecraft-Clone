#include "Game/Chunk.h"
#include "Game/Utils.h"

Chunk::Chunk() : 
    pos{0,0},
    blocks(std::vector<std::vector<std::vector<Block>>>(Utils::WORLD_HEIGHT, std::vector<std::vector<Block>>(Utils::CHUNK_SIZE, std::vector<Block>(Utils::CHUNK_SIZE))))
{
    // GenerateChunk();
}

Chunk::Chunk(int x, int z) : 
    pos{x,z},
    blocks(std::vector<std::vector<std::vector<Block>>>(Utils::WORLD_HEIGHT, std::vector<std::vector<Block>>(Utils::CHUNK_SIZE, std::vector<Block>(Utils::CHUNK_SIZE))))
{
    GenerateChunk();
}

Chunk::~Chunk() {

}

void Chunk::GenerateChunk() {
    std::cout << "Chunkpos x: " << Utils::CHUNK_SIZE * pos.x << std::endl;
    int y = 0;
    for (y = 0; y < 11; y++) {
        for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
            for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
                blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::STONE);
            }
        }
    }
    for (; y < 15; y++) {
        for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
            for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
                blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::DIRT);
            }
        }
    }
    for (; y < 16; y++) {
        for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
            for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
                blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::GRASS);
            }
        }
    }
    for (; y < Utils::WORLD_HEIGHT; y++) {
        for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
            for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
                blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, Utils::BlockType::AIR);
            }
        }
    }
}

void Chunk::Render(GameRenderer& renderer) const {
    for (const auto& layer: blocks) {
        for (const auto& row: layer) {
            for (const auto& block: row) {
                if (block.type == Utils::BlockType::AIR) {
                    continue;
                }
                for (int face = 0; face < 6; face++) {
                    renderer.RenderFace(block, face);
                }
            }
        }
    }
}