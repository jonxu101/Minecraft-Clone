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

void Chunk::setLayer(int y, Utils::BlockType type) {
    for (int x = 0; x < Utils::CHUNK_SIZE; x++) {
        for (int z = 0; z < Utils::CHUNK_SIZE; z++) {
            blocks[y][x][z] = Block(x + Utils::CHUNK_SIZE * pos.x, y, z + Utils::CHUNK_SIZE * pos.z, type);
        }
    }
}
void Chunk::GenerateChunk() {
    std::cout << "Chunkpos x: " << Utils::CHUNK_SIZE * pos.x << std::endl;
    int y = 0;
    for (; y < 11; y++) {
       setLayer(y, Utils::BlockType::STONE);
    }
    for (; y < 15; y++) {
        setLayer(y, Utils::BlockType::DIRT);
    }
    for (; y < 16; y++) {
        setLayer(y, Utils::BlockType::GRASS);
    }
    for (; y < Utils::WORLD_HEIGHT; y++) {
        setLayer(y, Utils::BlockType::AIR);
    }
}

void Chunk::Render(GameRenderer& renderer) const {
    for (const auto& layer: blocks) {
        for (const auto& row: layer) {
            for (const auto& block: row) {
                if (block.type == Utils::BlockType::AIR) {
                    continue;
                }
                renderer.RenderBlock(block);
            }
        }
    }
}

Block* Chunk::GetBlock(int x, int y, int z) {
    if (y < 0 || y >= Utils::WORLD_HEIGHT || 
        x < 0 || x >= Utils::CHUNK_SIZE ||
        z < 0 || z >= Utils::CHUNK_SIZE) {
        return nullptr;
    }
    return &blocks[y][x][z];
}