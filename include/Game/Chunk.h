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

class Chunk;
class ChunkIndexBuffer;

class ChunkIndexBuffer {
private:
    Chunk* owner_;
    // unsigned int buffer[Utils::CHUNK_SIZE * Utils::CHUNK_SIZE * Utils::WORLD_HEIGHT * 6 * 6];
    // unsigned int size;
    std::vector<unsigned int> buffer; // TODO: separate by # of textures

    static unsigned int CubeIndices_[6 * 6];

    IndexBuffer ib;

public:
    ChunkIndexBuffer(Chunk* owner);

    static void Init();

    void UpdateChunk();

    void Bind() const;
    unsigned int GetCount() const;
};

class Chunk {

friend class ChunkIndexBuffer;
friend class ChunkRenderer;

private:
    ChunkPos pos;
    std::vector<std::vector<std::vector<Block>>> blocks;
    ChunkIndexBuffer ib;

public:
    Chunk();
    Chunk(int x, int z);
    ~Chunk();

    void GenerateChunk();
    // void Render(ChunkRenderer& renderer) const;
};