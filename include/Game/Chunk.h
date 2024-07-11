#pragma once

#include "Block.h"
#include "GameRenderer.h"
#include "Utils.h"

#include "Graphics/Renderer.h"
#include <vector>

struct ChunkPos {
    int x;
    int z;
};

class Chunk {
private:
    ChunkPos pos;
    std::vector<std::vector<std::vector<Block>>> blocks;

public:
    Chunk();
    Chunk(int x, int z);
    ~Chunk();

    void GenerateChunk();
    void Render(GameRenderer& renderer) const;
    Block* GetBlock(int x, int y, int z);

private:
    void setLayer(int y, Utils::BlockType type);
};